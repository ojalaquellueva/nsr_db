<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
country VARCHAR(100) DEFAULT NULL,
state VARCHAR(100) DEFAULT NULL,
continent VARCHAR(100) DEFAULT NULL,
island VARCHAR(100) DEFAULT NULL,
taxon VARCHAR(100) DEFAULT NULL,
taxon_rank VARCHAR(100) DEFAULT NULL,
added_by VARCHAR(100) DEFAULT NULL,
check_Fail VARCHAR(100) DEFAULT NULL,
source VARCHAR(500) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

