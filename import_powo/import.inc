<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  `$tbl_raw`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw' 
INTO TABLE $tbl_raw 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Setting empty strings to NULL...";
if (!(empty_string_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;
echo "    Setting NA to NULL...";
if (!(NA_to_null($dbh, $tbl_raw))) die("Error\r\n.");
echo $done;

echo "  `$tbl_region_codes`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_codes' 
INTO TABLE $tbl_region_codes 
FIELDS TERMINATED BY ',' 
OPTIONALLY ENCLOSED BY '\"'
LINES TERMINATED BY '\r\n' 
IGNORE 1 LINES
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Setting empty strings to NULL...";
if (!(empty_string_to_null($dbh,$tbl_region_codes))) die("Error\r\n.");
echo $done;
echo "    Setting NA to NULL...";
if (!(NA_to_null($dbh, $tbl_region_codes))) die("Error\r\n.");
echo $done;

?>
