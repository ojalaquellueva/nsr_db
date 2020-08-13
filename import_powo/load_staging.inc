<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
//
// Omits duplicate records of the same value of taxon 
// + country. 
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT
'$src',
area_name,
name,
rank,
establishment,
NULL
FROM $tbl_raw
WHERE include=1
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>