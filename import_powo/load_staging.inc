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
country,
name,
rank,
establishment,
NULL
FROM $tbl_raw
WHERE is_dupe=0
AND country IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>