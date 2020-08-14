<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables\r\n";

$tbl_raw=$src."_raw";
echo "  `$tbl_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
fqId VARCHAR(250) DEFAULT NULL,
query VARCHAR(250) DEFAULT NULL,
modified VARCHAR(250) DEFAULT NULL,
bibliographicCitation VARCHAR(500) DEFAULT NULL,
genus VARCHAR(250) DEFAULT NULL,
taxonomicStatus VARCHAR(250) DEFAULT NULL,
kingdom VARCHAR(250) DEFAULT NULL,
phylum VARCHAR(250) DEFAULT NULL,
family VARCHAR(250) DEFAULT NULL,
source VARCHAR(250) DEFAULT NULL,
namePublishedInYear VARCHAR(250) DEFAULT NULL,
name VARCHAR(250) DEFAULT NULL,
authors VARCHAR(250) DEFAULT NULL,
species VARCHAR(250) DEFAULT NULL,
rank VARCHAR(250) DEFAULT NULL,
reference VARCHAR(250) DEFAULT NULL,
accepted_fqId VARCHAR(250) DEFAULT NULL,
accepted_name VARCHAR(250) DEFAULT NULL,
accepted_author VARCHAR(250) DEFAULT NULL,
accepted_rank VARCHAR(250) DEFAULT NULL,
accepted_taxonomicStatus VARCHAR(250) DEFAULT NULL,
establishment VARCHAR(250) DEFAULT NULL,
featureId VARCHAR(250) DEFAULT NULL,
tdwgCode VARCHAR(250) DEFAULT NULL,
tdwgLevel VARCHAR(250) DEFAULT NULL,
area_name VARCHAR(250) DEFAULT NULL,
infraspecies VARCHAR(250) DEFAULT NULL,
occurrenceStatus VARCHAR(250) DEFAULT NULL,
threatStatus VARCHAR(250) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($dbh, $sql);
echo "done";

echo "  `region_codes`...";
$sql="
DROP TABLE IF EXISTS `region_codes`;
CREATE TABLE region_codes (
seq INT(11) NOT NULL,
code VARCHAR(250),
region VARCHAR(250),
alt_region VARCHAR(250),
country VARCHAR(250),
notes VARCHAR(250),
INDEX(code),
INDEX(region)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($dbh, $sql);
echo "done";

?>

