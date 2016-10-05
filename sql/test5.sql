-- The following code detects whether the program will detect error that no relation exist
CREATE TABLE DB1 (serial INTEGER, ikey INTEGER, filler CHAR(80), dkey DOUBLE);

INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (0, 11618, 'asfsgag', 4.5);
SELECT * FROM cao;

DROP TABLE DB1;
