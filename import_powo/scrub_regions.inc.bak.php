<?php

/////////////////////////////////////////////////////////
// Extract all unique values of area_name, scrub using
// GNRS API and re-import results
/////////////////////////////////////////////////////////

echo "Scrubbing regions:\r\n";

echo "  Extracting region names...";
$sql="
DROP TABLE IF EXISTS temp_regions;
CREATE TABLE temp_regions
SELECT DISTINCT area_name
FROM powo_raw
WHERE area_name IS NOT NULL
ORDER BY area_name
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Dumping to file...";
$regions_raw_file = $data_dir . "nsr_regions.csv";

$cmd="export MYSQL_PWD=$PWD; mysql -u $USER -e 'SELECT \"before\" AS user_id, area_name  AS country, \"after\" AS state_province, NULL AS county_parish FROM temp_regions' $DB > $regions_raw_file ";
//echo "\n\$cmd:\n$cmd\n";
exec($cmd, $output, $status);
if ($status) die("ERROR: dump-to-file command non-zero exit status (" . 		basename(__FILE__) . ")\r\n");
echo $done;

# Convert to CSV
# Not a generic solution, but works in this particular case
echo "  Converting from tab-delimitted to CSV...";
$cmd="sed -i 's/,/@@@/g' $regions_raw_file";	// Transform literal commas
exec($cmd, $output, $status);
if ($status) die("ERROR: sed comma-transform non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/\t/,/g' $regions_raw_file";	// Convert tabs to comma delimitters
exec($cmd, $output, $status);
if ($status) die("ERROR: sed tab-to-comma non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/@@@/,/g' $regions_raw_file";		// Restore literal commas
exec($cmd, $output, $status);
if ($status) die("ERROR: sed comma-restore non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/before,/NULL,\"/g' $regions_raw_file";	// Opening quote
exec($cmd, $output, $status);
if ($status) die("ERROR: sed opening-quote non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/,after/\",NULL/g' $regions_raw_file";	// Closing quote
exec($cmd, $output, $status);
if ($status) die("ERROR: sed closing-quote non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

echo $done;



?>