<?php

///////////////////////////////////////////////////////
// Deletes rows not needed for NSR
///////////////////////////////////////////////////////


echo "  Removing unnecessary rows:\r\n";

echo "    area_name IS NULL...";
$sql="
DELETE FROM $tbl_raw
WHERE area_name IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    establishment='Absent'...";
// Deleting 'Doubtful','Extinct' as well for now 
// until I figure out what to about these
$sql="
DELETE FROM $tbl_raw
WHERE establishment IN ('Absent','Doubtful','Extinct')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>