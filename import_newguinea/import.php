<?php

////////////////////////////////////////////////////
// Imports species distribution data
////////////////////////////////////////////////////

// Parameters specific to this source
include "params.inc";	

////////////// Import raw data file //////////////////////

// create empty import table
include "create_raw_data_tables.inc";

// import text files to raw data tables
include "import.inc";


die("STOPPING...\n");




// import text files to raw data tables
include "alter_tables.inc";

echo "Standardizing " . $src . "_raw:\r\n";

// Remove rows not relevant to NSR
include "delete_unnecessary_rows.inc";

// separate taxon name from author and dump to taxon field
include "standardize_rank.inc";

// standardize native status codes
include "standardize_status.inc";

// Scrub regions with GNRS API
include "scrub_regions.inc";

// Mark duplicate taxon+poldiv combos for removal
include "mark_duplicates.inc";

// Extract empirical list of countries and assign to 
// variable cclist_countries
include "prepare_cclist_countries.inc";

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";

// load metadata on regions covered by this source
include "create_poldiv_source_staging.inc";
include "load_poldiv_source_staging.inc"; 

// delete raw data tables
if ($drop_raw || $drop_raw_force) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////


?>