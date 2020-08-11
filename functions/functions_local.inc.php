<?php

/////////////////////////////////////////////////////////
// Temporary location for testing PHP functions locally
// before commiting to submodule "includes"
/////////////////////////////////////////////////////////

function db_exists($dbname, $uname, $pwd) {
	/////////////////////////////////////////////////////
	// Returns TRUE if (local) MySQL database dbname 
	// exists, else FALSE
	/////////////////////////////////////////////////////

    $connection;
    $connection = new PDO("mysql:host=localhost", $uname, $pwd);
    $connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION); 
    $stmt = $connection->prepare("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME =:dbname");
    $stmt->execute(array(":dbname"=>$dbname));
    $row=$stmt->fetch(PDO::FETCH_ASSOC);

    if ($stmt->rowCount() == 1) {
        Return TRUE;
    } else { 
    	Return FALSE; 
    }
}

?>