-- DESCRIÇÃO DO CASO

SELECT description FROM crime_scene_reports WHERE day=28 and month=7 and year=2020
and street='Chamberlin Street';

-- TESTEMUNHAS DO ATO

SELECT name, transcript FROM interviews WHERE day=28 and month=7 and
year=2020;

-- CARROS QUE SAIRAM DO ESTACIONAMENTO ENTRE 10:15 E 10:25

SELECT license_plate FROM courthouse_security_logs WHERE day=28 and
month=7 and year=2020 and hour=10 and minute<=25 and minute >=15
and activity='exit';

-- QUEM SACOU DINHEIRO

SELECT name FROM bank_accounts JOIN atm_transactions ON
bank_accounts.account_number = atm_transactions.account_number
JOIN people ON person_id = people.id
WHERE day=28 and month=7 and year=2020 and 
atm_location='Fifer Street';

-- NOME DAS PESSOAS QUE SAIRAM DO ESTACIONAMENTO

SELECT name FROM courthouse_security_logs JOIN
people ON courthouse_security_logs.license_plate = people.license_plate
WHERE day=28 and
month=7 and year=2020 and hour=10 and minute<=25 and minute >=15
and activity='exit';

-- SUSPEITOS QUE ESTIVERAM EM AMBOS LUGARES

SELECT name FROM bank_accounts JOIN atm_transactions ON
bank_accounts.account_number = atm_transactions.account_number
JOIN people ON person_id = people.id
WHERE day=28 and month=7 and year=2020 and 
atm_location='Fifer Street' and name IN (
SELECT name FROM courthouse_security_logs JOIN
people ON courthouse_security_logs.license_plate = people.license_plate
WHERE day=28 and
month=7 and year=2020 and hour=10 and minute<=25 and minute >=15
and activity='exit'
);

-- SUSPEITOS QUE FIZERAM LIGAÇÃO

SELECT name, caller, receiver FROM bank_accounts JOIN atm_transactions ON
bank_accounts.account_number = atm_transactions.account_number
JOIN people ON person_id = people.id JOIN phone_calls ON
people.phone_number = phone_calls.caller
WHERE atm_transactions.day=28 and atm_transactions.month=7 and 
atm_transactions.year=2020 and 
atm_location='Fifer Street' and name IN (
SELECT name FROM courthouse_security_logs JOIN
people ON courthouse_security_logs.license_plate = people.license_plate
WHERE day=28 and
month=7 and year=2020 and hour=10 and minute<=25 and minute >=15
and activity='exit'
) and phone_calls.day=28 and phone_calls.month=7 and phone_calls.year=2020
and duration <= 60;         

-- NOME DE QUEM A RECEBEU LIGAÇÃO

SELECT name, phone_number FROM people WHERE phone_number IN
(SELECT receiver FROM bank_accounts JOIN atm_transactions ON
bank_accounts.account_number = atm_transactions.account_number
JOIN people ON person_id = people.id JOIN phone_calls ON
people.phone_number = phone_calls.caller
WHERE atm_transactions.day=28 and atm_transactions.month=7 and 
atm_transactions.year=2020 and 
atm_location='Fifer Street' and name IN (
SELECT name FROM courthouse_security_logs JOIN
people ON courthouse_security_logs.license_plate = people.license_plate
WHERE day=28 and
month=7 and year=2020 and hour=10 and minute<=25 and minute >=15
and activity='exit'
) and phone_calls.day=28 and phone_calls.month=7 and phone_calls.year=2020
and duration <= 60);

-- ID DO AEROPORTO

SELECT * FROM airports WHERE city='Fiftyville';

-- RETORNA TODOS VOOS DO DIA 29 EM ORDEM

SELECT id FROM flights WHERE origin_airport_id=8 and day=29 and month=7 
and year=2020 ORDER BY year, month, day, hour, minute;

-- PASSAGEIROS NO PRIMEIRO VOO DO DIA 29 DE JULHO

SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id=36;

-- CIDADE NA QUAL O LADRÃO FUGIU

SELECT city FROM airports JOIN flights ON destination_airport_id = airports.id
WHERE flights.id =36;