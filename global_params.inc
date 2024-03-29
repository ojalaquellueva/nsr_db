<?php

//////////////////////////////////////////////////
//////////////////////////////////////////////////
// Loading scripts for BIEN Cultivated Species database
//
// By: Brad Boyle
// Contact: bboyle@email.arizona.edu
// Date created: 18 Feb. 2014
// Date last revised: 13 Dec. 2017
//
// Everything you need to set is here and in local
// params.inc file in each import directory
//
// Read the readme files in this directory and 
// all main subdirectories!
//////////////////////////////////////////////////
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// Replace database? (true/false)
//
// IMPORTANT! Set to true to replace database entirely
// all tables will be dropped and replaced with new,
// empty tables. Application will automatically prompt
// for confirmation if this option is set to true.
//
// Set to false keep existing database and
// add (if new) or replace (if already present) only
// the source(s) listed in $src_array.
//
//////////////////////////////////////////////////
$REPLACE_DB = FALSE;

//////////////////////////////////////////////////
// Distribution sources
//
// CRITICAL!!!
// Include in this array the name of every source
// you will be importing into the database
// Import scripts and data for each source MUST
// be their own directory called "import_[$sourceName]",
// for example, "import_tropicos". Source names 
// below MUST match the parameter $sourceName 
// as specified in params.inc in import subdirectory
// for that source. 
//////////////////////////////////////////////////

$src_array=array(
	"enquist",
	"weakley",
	"mab",
	"ipane",
	"powo",
	"flbr",
	"conosur",
	"fwi",
	"mexico",
	"tropicos",
	"usda",
	"vascan",
	"newguinea"
);
/* 
$src_array=array(
	"powo",
	"enquist",
	"newguinea"
);
$src_array=array(
	"enquist"
);
 */

//////////////////////////////////////////////////
// Limit rows loaded per source?
// For testing/development using subsample of data
// Set to empty string for production (imports all)
//////////////////////////////////////////////////

# Integer # of rows to import, "" imports all
$ROW_LIMIT="";
$ROW_LIMIT=300;

//////////////////////////////////////////////////
// NSR metadata
//////////////////////////////////////////////////

// Database version
// Required! Added to table meta, along with today's date
$DB_VERSION="3.0";

// Code version
// Use tag # for commit associated with this DB version
// Added to table meta, along with today's date
$CODE_VERSION="3.0";

//////////////////////////////////////////////////
// Users & access levels
//
// IMPORTANT! These users will be granted access to
// the completed database. All usernames must already 
// exist in MySQL. This variable is an array with one
// username + access level per line, separated by pipe (|)
// and surround by double quotes, quoted elements 
// separated by commas. If you do not wish to grant any
// privileges, set to entire array to empty string "".
//
// Access levels:
//	read: SELECT only
//	write: SELECT, INSERT, UPDATE, DELETE, CREATE, DROP (tables only)
//	admin: All privileges
//////////////////////////////////////////////////

$usr_array=array(
	"nsr_read|read",
	"nsr|write"
);

//////////////////////////////////////////////////
// Include paths and filenames
//////////////////////////////////////////////////

// Base directory
// All other paths set relative to this one
$base_dir = "/home/boyle/bien/";

// Base directory for all code related to this application
$app_base_dir = $base_dir . "nsr/";

// Application code directory (this one; git repo)
$app_dir = $app_base_dir . "db/";

// Data directory
// Keep outside repo
$data_dir = $app_base_dir . "data/db/";

// DB config file (DB name, users, passwords
// Keep outside repo
$config_dir = $app_base_dir . "config/";

// Path to general php functions and other generic include files
// Subdirectory "includes/" is a git submodule
$global_utilities_path = $base_dir . "includes/php/";

// Path to local functions not in submodule "includes"
// Recommend move to submodule once functions have 
// been tested
$local_utilities_path = $app_dir."functions/";

//////////////////////////////////////////////////
// Db connection file
//////////////////////////////////////////////////

$config_file = $config_dir . "db_config_nsr_db.inc";

///////////////////////////////////////////////////
// Include files (functions, etc.)
///////////////////////////////////////////////////

include $global_utilities_path."functions.inc";
include $global_utilities_path."taxon_functions.inc";
include $global_utilities_path."sql_functions.inc";
include $global_utilities_path."geo_functions.inc";
$timer_on=$global_utilities_path."timer_on.inc";
$timer_off=$global_utilities_path."timer_off.inc";
include $local_utilities_path."functions_local.inc.php";

//////////////////////////////////////////////////
// Drop raw data tables after import complete?
// (true/false)
//////////////////////////////////////////////////

$drop_raw=false;
$drop_raw_force=false;		// over-rides any source-specific settings
$drop_staging_force=false;		// over-rides any source-specific settings

//////////////////////////////////////////////////
// API parameters
//////////////////////////////////////////////////

// GNRS base url
$gnrs_url = "http://vegbiendev.nceas.ucsb.edu:8875/gnrs_ws.php"; 

//////////////////////////////////////////////////
// Error-reporting & runtime behavior
//////////////////////////////////////////////////

// echos error messages to screen
$echo_on = true;		

// aborts entire script on error
$die_on_fail = true;		

// default success and fail messages
$done = "done\r\n";
$msg_success = "done\r\n";
$msg_fail = "failed!\r\n";

?>