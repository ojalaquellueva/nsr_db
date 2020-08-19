<?php

/////////////////////////////////////////////////////
// Extracts empirical IN list of countries from the 
// data itself
/////////////////////////////////////////////////////

echo "Preparing list of comprehensive checklist countries...";
$sql="SELECT CONCAT('\'',GROUP_CONCAT(DISTINCT country SEPARATOR '\', \''), '\'') AS cclist FROM powo_raw LIMIT 1";
$result = mysqli_query($dbh,$sql);
$row = mysqli_fetch_assoc($result);
$cclist_countries = $row['cclist'];
echo $done;

//echo "\$cclist_countries:\r\n$cclist_countries\r\n";

?>