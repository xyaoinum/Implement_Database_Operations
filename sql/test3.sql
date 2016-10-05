-- The following code test the correctness of Insertion, ScanSelect and IndexSelect, including correct projection, choice of selection method, and computation. For all the selection based on indexed attribute and op=EQ, the program should choose IndexSelect. For others, it should choose ScanSelect. The result should have projection tuple DB1.serial, DB1.ikey, DB1.filler with the same sequence.
CREATE TABLE DB1 (serial INTEGER, ikey INTEGER, filler CHAR(80), dkey DOUBLE);

CREATE INDEX DB1 (dkey);
CREATE INDEX DB1 (ikey);

INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (0, 11618, 'asfsgag',  1.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (1, 12318, 'fdhdfhfdh',  1.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (2, 47658, 'sdfdfsdfsdf',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (3, 12318, 'etete',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (4, 12318, 'sdfds',  2.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (5, 89656, 'dfhfdh',  3.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (6, 37888, 'asdsd',  4.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (7, 757, 'etete',  4.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (8, 7, 'asfha',  4.0);
INSERT INTO DB1 (serial, ikey, filler, dkey) VALUES (9, 236876, 'sdfsd',  4.0);

SELECT * FROM DB1;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey = 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey < 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey <= 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey > 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey >= 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey <> 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler = 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler < 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler <= 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler > 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler >= 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler <> 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey = 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey < 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey <= 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey > 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey >= 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey <> 12318;

DROP INDEX DB1 (dkey);
DROP INDEX DB1 (ikey);

SELECT * FROM DB1;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey = 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey < 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey <= 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey > 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey >= 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.dkey <> 2.0;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler = 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler < 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler <= 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler > 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler >= 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.filler <> 'etete';
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey = 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey < 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey <= 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey > 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey >= 12318;
SELECT DB1.serial, DB1.ikey, DB1.filler FROM DB1 WHERE DB1.ikey <> 12318;

DROP TABLE DB1;
