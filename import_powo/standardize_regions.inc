<?php

/////////////////////////////////////////////////////////
// Standardize area_names (mostly but not always countries)
// and combine any duplicate records
/////////////////////////////////////////////////////////

echo "  Standardizing regions:\r\n";

echo "    Adding columns...";
$sql="
ALTER TABLE $tbl_raw
ADD id INT PRIMARY KEY AUTO_INCREMENT,
ADD COLUMN country VARCHAR(250) DEFAULT NULL,
ADD COLUMN include INT(1) DEFAULT 0,
ADD INDEX (include)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Populating `area_std`...";
$sql="
UPDATE $tbl_raw
SET country=
CASE
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
WHEN area_name='xxx' THEN 'yyy'
ELSE area_name
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


echo "  Marking duplicate records...";
$sql="
UPDATE $tbl_raw r JOIN
(
SELECT 
country,
name, 
(
SELECT id
FROM $tbl_raw r
WHERE $tbl_raw.taxon=r.taxon AND $tbl_raw.country=r.country
ORDER BY id
LIMIT 1
) AS first_id
FROM $tbl_raw
GROUP BY country, name
) AS nodupes
ON r.id=nodupes.first_id
SET include=1
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>