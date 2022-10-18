-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE year = 2020 AND
day = 28 AND month = 7 AND street = 'Chamberlin Street';

Theft of the CS50 duck took place at 10:15am at the Chamberlin Street
courthouse. Interviews were conducted today with three witnesses who were 
present at the time — each of their interview transcripts mentions the 
courthouse.

SELECT name, transcript FROM interviews 
WHERE transcript LIKE "%courthouse%";

Ruth
Eugene
Raymond

SELECT license_plate FROM courthouse_security_logs 
WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute >= 15
AND minute <= 25 AND activity = 'exit';

5P2BI95
94KL13X
6P58WS2
4328GD8
G412CB7
L93JTIZ
322W7JE
0NTHK55

SELECT DISTINCT(name) FROM people JOIN courthouse_security_logs 
ON people.license_plate = courthouse_security_logs.license_plate 
WHERE people.license_plate IN (SELECT license_plate FROM courthouse_security_logs 
WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute >= 15
AND minute <= 25 AND activity = 'exit');

Patrick
Amber
Elizabeth
Roger
Danielle
Russell
Evelyn
Ernest