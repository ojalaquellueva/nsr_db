<?php

/////////////////////////////////////////////////////////
// Extract all unique values of area_name, scrub using
// GNRS API and re-import results
/////////////////////////////////////////////////////////

echo "Scrubbing regions:\r\n";

echo "  Creating temp table `temp_regions_raw`...";
$sql="
DROP TABLE IF EXISTS temp_regions_raw;
CREATE TABLE temp_regions_raw (
user_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
country VARCHAR(250) DEFAULT NULL,
state_province VARCHAR(250) DEFAULT NULL,
county_parish VARCHAR(250) DEFAULT NULL,
PRIMARY KEY (user_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// The before/after delimiters are to assist with converting tab-delimited
// to CSV
echo "  Extracting region names...";
$sql="
INSERT INTO temp_regions_raw (country)
SELECT DISTINCT 
CONCAT('DBLQUOTE', area_name, 'DBLQUOTE') AS area_name
FROM powo_raw
WHERE area_name IS NOT NULL
ORDER BY area_name
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Dumping to file...";
$regions_raw_file = $data_dir . "nsr_regions.csv";

//$cmd="export MYSQL_PWD=$PWD; mysql -u $USER -e 'SELECT \"before\" AS user_id, area_name  AS country, \"after\" AS state_province, NULL AS county_parish FROM temp_regions' $DB > $regions_raw_file ";
$cmd="export MYSQL_PWD=$PWD; mysql -u $USER -e 'SELECT * FROM temp_regions_raw' $DB > $regions_raw_file ";
//echo "\n\$cmd:\n$cmd\n";
exec($cmd, $output, $status);
if ($status) die("ERROR: dump-to-file command non-zero exit status (" . 		basename(__FILE__) . ")\r\n");
echo $done;

# Convert to CSV
# Not a generic solution, but works in this particular case
echo "  Converting from tab-delimitted to CSV...";
$cmd="sed -i 's/,/@@@/g' $regions_raw_file";	// Transform literal commas
exec($cmd, $output, $status);
if ($status) die("ERROR: Comma-transform non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/\t/,/g' $regions_raw_file";	// Convert tabs to comma delimitters
exec($cmd, $output, $status);
if ($status) die("ERROR: Tab-to-comma non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/@@@/,/g' $regions_raw_file";		// Restore literal commas
exec($cmd, $output, $status);
if ($status) die("ERROR: Comma-restore non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/DBLQUOTE/\"/g' $regions_raw_file"; // Restore opening quote
exec($cmd, $output, $status);
if ($status) die("ERROR: Restore-quotes non-zero exit status (" . 		basename(__FILE__) . ")\r\n");
echo $done;

// Reimport the file as array & convert to json 
$csv = $regions_raw_file;
$csv_arr = array_map('str_getcsv', file($csv));
$json_data = json_encode($csv_arr);

// Set curl options
$ch = curl_init($gnrs_url);	
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_FAILONERROR, true);
curl_setopt($ch, CURLOPT_POST, 1);	
curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json')); 
curl_setopt($ch, CURLOPT_POSTFIELDS, $json_data);	

// Send the API call
$response_json = curl_exec($ch);
$status = curl_getinfo($ch, CURLINFO_HTTP_CODE);
if ( $status != 201 && $status != 200 ) {
    die("Error: call to URL $url failed with status $status, response $response, curl_error " . curl_error($ch) . ", curl_errno " . curl_errno($ch) . "\r\n");
}
curl_close($ch);

// Process the response and load to database
$response =  json_decode($response_json);

// echo "\nStatus:\n";
// var_dump($status);
// echo "\nJSON response:\n";
// var_dump($response_json);
// echo "\\nResponse:\\n";
// var_dump($response);

// Set format
$mask = "%-12s %-25s %-15s %-25s %-25s %-20s %-15s \n";

// Print header
echo sprintf($mask, "user_id", "country_verbatim", "country_id", "country", "match_method_country", "match_score_country", "match_status");

foreach ($response as $idx => $obs) {
	// Output row
	echo sprintf($mask, 
		$obs->user_id, 
		$obs->country_verbatim, 
		$obs->country_id, 
		$obs->country, 
		$obs->match_method_country, 
		$obs->match_score_country, 
		$obs->match_status
	);
}

echo "\r\n";

die("\nSTOPPING\n");





?>