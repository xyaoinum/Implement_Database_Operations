-- The following code detects whether the program will reject insertion for a tuple with an attribute without value. In this case, the program should reject this insertion because there is no value for attribute dkey.
CREATE TABLE DB1 (serial INTEGER, ikey INTEGER, filler CHAR(80), dkey DOUBLE);

INSERT INTO DB1 (serial, ikey, filler) VALUES (0, 11618, 'asfsgag');
SELECT * FROM DB1;

DROP TABLE DB1;
