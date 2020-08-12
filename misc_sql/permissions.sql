REVOKE ALL PRIVILEGES ON nsr_dev.* FROM bien_read@localhost;
REVOKE ALL PRIVILEGES ON nsr_dev.* FROM bien_web@localhost;
REVOKE ALL PRIVILEGES ON nsr_dev.* FROM bien_write@localhost;
REVOKE ALL PRIVILEGES ON nsr_dev.* FROM nsr@localhost;

GRANT SELECT ON nsr_dev.* TO 'bien_read'@'localhost';

GRANT SELECT ON nsr_dev.* TO 'bien_web'@'localhost';

GRANT SELECT, INSERT, UPDATE, DELETE 
ON nsr_dev.* TO 'bien_write'@'localhost';
GRANT DROP ON TABLE nsr_dev.* TO 'bien_write'@'localhost';
GRANT CREATE ON TABLE nsr_dev.* TO 'bien_write'@'localhost';

GRANT ALL ON nsr_dev.* TO 'admin'@'localhost';

GRANT SELECT, INSERT, UPDATE, DELETE, ALTER 
ON nsr_dev.* TO 'nsr'@'localhost';
GRANT DROP ON TABLE nsr_dev.* TO 'nsr'@'localhost';
GRANT CREATE ON TABLE nsr_dev.* TO 'nsr'@'localhost';

FLUSH PRIVILEGES;