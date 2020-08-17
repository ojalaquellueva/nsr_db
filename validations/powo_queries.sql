-- -----------------------------------------------------------------
-- Checks on structure & content of raw POWO import
-- -----------------------------------------------------------------

-- Add combined name + author column and index it
ALTER TABLE powo_raw
ADD COLUMN taxon_with_author VARCHAR(250) DEFAULT NULL
;
UPDATE powo_raw
SET taxon_with_author=CONCAT_WS(' ', `name`, `authors`)
;
ALTER TABLE powo_raw
ADD INDEX (taxon_with_author)
;

--
-- Check if total acceptedspecies of containing regions equal 
-- sum of child regions
-- Containing region e.g, AGE / Argentina Northeast
-- Child region e.g., AGE-CD / Cordoba; AGE-CH / Chaco
--

SELECT COUNT(DISTINCT taxon_with_author) AS parent_species
FROM powo_raw
WHERE taxonomicStatus='Accepted'
AND rank='species'
AND tdwgCode='AGE'


SELECT COUNT(DISTINCT taxon_with_author) AS child_species
FROM powo_raw
WHERE taxonomicStatus='Accepted'
AND rank='species'
AND tdwgCode IN ('
