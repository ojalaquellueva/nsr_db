<?php

//////////////////////////////////////////////////////
// Standardized status codes in raw data
//////////////////////////////////////////////////////

echo "  Standardizing status codes...";

//echo "  Native status...";
$sql="
UPDATE $tbl_raw
SET establishment=
CASE
WHEN establishment='Introduced' THEN 'introduced'
WHEN establishment='Native' THEN 'native'
ELSE establishment
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>