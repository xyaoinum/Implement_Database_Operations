-- The following code test the correctness SNL, INL, and SMJ, including correct projection, choice of selection method, and computation for corner cases. If it is not a equality query, the program should use SNL. If it is an equality query and has an index on either the two attribute, it should use INL. If it is an equality query with no indices, it should use SMJ. The testcases include corner cases such as both relations are empty, only one is empty, and both have tuples. For the third one, we also consider corner cases such as duplicate tuples and duplicate attributes.
CREATE TABLE DB1 (serial INTEGER, ikey INTEGER, filler CHAR(80), dkey DOUBLE);
CREATE TABLE DB2 (serial INTEGER, ikey INTEGER, filler CHAR(80), dkey DOUBLE);

SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey = DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey < DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey > DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey >= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <> DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler = DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler < DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler > DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler >= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <> DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey = DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey < DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey > DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey >= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <> DB2.ikey;

INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (0, 11618, 'asfsgag',  2.1);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (1, 12318, 'fdhdfhfdh',  2.1);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (2, 47658, 'sdfdfsdfsdf',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (2, 47658, 'sdfdfsdfsdf',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (2, 47658, 'sdfdfsdfsdf',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (3, 12318, 'etete',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (4, 12318, 'sdfds',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (5, 89656, 'dfhfdh',  3.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (6, 37888, 'asdsd',  3.9);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (7, 757, 'etete',  4.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (8, 7, 'asfha',  4.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (9, 236876, 'sdfsd',  4.0);

SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey = DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey < DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey > DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey >= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <> DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler = DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler < DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler > DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler >= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <> DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey = DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey < DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey > DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey >= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <> DB2.ikey;

CREATE INDEX DB2 (dkey);
CREATE INDEX DB2 (ikey);

INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (0, 11618, 'asfsgag',  0.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (1, 11618, 'asfsgag',  1.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (2, 12318, 'asfsgag',  1.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (3, 11618, 'asfsgag',  1.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (4, 11618, 'etete',  2.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (5, 11618, 'asfsgag',  2.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (6, 11618, 'asfsgag',  2.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (7, 11618, 'asfsgag',  1.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (8, 11618, 'etete',  1.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (9, 11618, 'asfsgag',  1.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (10, 11618, 'asfsgag',  1.0);
INSERT INTO DB2 (serial, ikey, filler, dkey) VALUES (11, 11618, 'asfsgag',  4.0);


SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey = DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey < DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey > DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey >= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <> DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler = DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler < DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler > DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler >= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <> DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey = DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey < DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey > DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey >= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <> DB2.ikey;

DROP INDEX DB2 (dkey);
DROP INDEX DB2 (ikey);

SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey = DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey < DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey > DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey >= DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.dkey <> DB2.dkey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler = DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler < DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler > DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler >= DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.filler <> DB2.filler;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey = DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey < DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey > DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey >= DB2.ikey;
SELECT DB1.serial, DB1.filler, DB2.serial, DB2.filler FROM DB1, DB2 WHERE DB1.ikey <> DB2.ikey;

DROP TABLE DB1;
DROP TABLE DB2;


