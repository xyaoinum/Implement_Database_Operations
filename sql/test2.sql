-- The following code detects whether the program will accept string ''. The program should accept the insertion and the query result should have 1 tuple.
CREATE TABLE DB1 (serial INTEGER, ikey INTEGER, filler CHAR(80), dkey DOUBLE);

INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (0, 11618, '',  1.0);
SELECT * FROM DB1;

DROP TABLE DB1;
