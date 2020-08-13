<?php
// Imports species distribution data from Tropicos

include "params.inc";	// everything you need to set is here and in global_params.inc

////////////// Import raw data file //////////////////////

// create empty import table
include "create_raw_data_tables.inc";

// import text files to raw data tables
include "import.inc";

// Remove rows not relevant to NSR
include "delete_unnecessary_rows.inc";

echo "Standardizing " . $src . "_raw:\r\n";

// separate taxon name from author and dump to taxon field
include "standardize_rank.inc";

// standardize native status codes
include "standardize_status.inc";

// standardize region names and delete superfluous records
include "standardize_regions.inc";

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";


die("\nSTOPPING...\n");


// load metadata on regions covered by this source
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; 

// delete raw data tables
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////


?>
