-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Review crime scene reports from the day of the crime
SELECT description, month, day, year, street FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Review the bakery security logs around 10:15am since that's where the crime took place
SELECT activity, license_plate, hour, minute FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10;

-- Suspicious license plates:
--5P2BI95, 6P58WS2, G412CB7, R3G7486, 13FNH73, 5P2BI95, 94KL13X, 6P58WS2, 4328GD8,G412CB7
-- look at 5P2BI95, 94KL13X, 6P58WS2 because they each left the bakery right around when the robbery happened

SELECT name, license_plate, passport_number FROM people
WHERE license_plate IN ('5P2BI95', '94KL13X', '6P58WS2');

-- Read interviews from Vanessa, Barry, and Bruce
SELECT name, transcript FROM interviews
WHERE name IN ('Vanessa', 'Barry', 'Bruce');

-- See if any phone calls were made between the three suspects
SELECT caller, p_caller.name, receiver, p_receive.name, month, day, duration
FROM phone_calls
    JOIN people AS p_caller on phone_calls.caller = p_caller.phone_number
    JOIN people AS p_receive on phone_calls.receiver = p_receive.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND p_caller.name IN ('Vanessa', 'Barry', 'Bruce');

|     caller     |  name   |    receiver    |  name   | month | day | duration |
+----------------+---------+----------------+---------+-------+-----+----------+
| (301) 555-4174 | Barry   | (711) 555-3007 | Joan    | 7     | 28  | 583      |
| (367) 555-5533 | Bruce   | (375) 555-8161 | Robin   | 7     | 28  | 45       |
| (367) 555-5533 | Bruce   | (344) 555-9601 | Deborah | 7     | 28  | 120      |
| (367) 555-5533 | Bruce   | (022) 555-4052 | Gregory | 7     | 28  | 241      |
| (725) 555-4692 | Vanessa | (821) 555-5262 | Amanda  | 7     | 28  | 456      |
| (367) 555-5533 | Bruce   | (704) 555-5790 | Carl    | 7     | 28  | 75       |

-- Check security logs for license plates from any of these other ppl
SELECT name, people.license_plate, bsl.activity, bsl.hour, bsl.minute FROM people
    JOIN bakery_security_logs bsl on people.license_plate = bsl.license_plate
WHERE bsl.month = 7 AND bsl.day = 28 AND people.name IN ('Barry', 'Bruce', 'Vanessa', 'Joan', 'Robin', 'Deborah', 'Gregory', 'Amanda', 'Carl');

-- Vanessa, Barry, Bruce = main suspects
-- Joan, Robin, Deborah, Gregory, Amanda, Carl = accomplices

-- Look for flights out of Fiftyville that day
SELECT flights.id, airport_orig.city, airport_dest.city, hour, minute FROM flights
    JOIN airports AS airport_orig on origin_airport_id = airport_orig.id
    JOIN airports AS airport_dest on destination_airport_id = airport_dest.id
WHERE month = 7 AND day = 28 AND year = 2021 AND origin_airport_id = 8
ORDER BY hour, minute;

+----+------------+---------------+------+--------+
| id |    city    |     city      | hour | minute |
+----+------------+---------------+------+--------+
| 6  | Fiftyville | Dallas        | 13   | 49     |
| 35 | Fiftyville | New York City | 16   | 16     |
| 34 | Fiftyville | Dallas        | 17   | 20     |
| 1  | Fiftyville | Dubai         | 17   | 50     |
| 17 | Fiftyville | New York City | 20   | 16

-- Culprit could have been on any of these flights!
SELECT name, flights.id, airport_orig.city, airport_dest.city FROM people
    JOIN passengers on people.passport_number = passengers.passport_number
    JOIN flights on passengers.flight_id = flights.id
    JOIN airports AS airport_orig on origin_airport_id = airport_orig.id
    JOIN airports AS airport_dest on destination_airport_id = airport_dest.id
WHERE airport_orig.city = 'Fiftyville'
    AND flights.month = 7 AND flights.day = 28 AND flights.year = 2021;

-- Review ATM withdrawls at Leggetr St
SELECT name, atm.atm_location, atm.transaction_type, atm.amount FROM people
    JOIN bank_accounts on people.id = bank_accounts.person_id
    JOIN atm_transactions atm on bank_accounts.account_number = atm.account_number
WHERE atm.month = 7 AND atm.day = 28 AND atm.year = 2021 AND atm.transaction_type = 'withdraw' AND atm.atm_location = 'Leggett Street';

  name   |  atm_location  | transaction_type | amount |
+---------+----------------+------------------+--------+
| Bruce   | Leggett Street | withdraw         | 50     |
| Diana   | Leggett Street | withdraw         | 35     |
| Brooke  | Leggett Street | withdraw         | 80     |
| Kenny   | Leggett Street | withdraw         | 20     |
| Iman    | Leggett Street | withdraw         | 20     |
| Luca    | Leggett Street | withdraw         | 48     |
| Taylor  | Leggett Street | withdraw         | 60     |
| Benista | Leggett Street | withdraw         | 30     |
+---------+----------------+------------------+--------+check50 cs50/problems/2023/x/fiftyville
-- Go back to the security logs
-- Who was at the bakery that morning who also flew out of town later that day


SELECT name, flights.id, airport_orig.city, airport_dest.city FROM people
    JOIN passengers on people.passport_number = passengers.passport_number
    JOIN flights on passengers.flight_id = flights.id
    JOIN airports AS airport_orig on origin_airport_id = airport_orig.id
    JOIN airports AS airport_dest on destination_airport_id = airport_dest.id
WHERE (
    SELECT name FROM people
        JOIN bakery_security_logs bsl on people.license_plate = bsl.license_plate
    WHERE month = 7 AND day = 28 AND year = 2021)
AND airport_orig.city = 'Fiftyville' AND flights.month = 7 AND flights.day = 28 AND flights.year = 2021;

| Vanessa | exit     | 10   | 16     | 5P2BI95       |
| Bruce   | exit     | 10   | 18     | 94KL13X       |
| Barry   | exit     | 10   | 18     | 6P58WS2       |
| Luca    | exit     | 10   | 19     | 4328GD8       |
| Sofia   | exit     | 10   | 20     | G412CB7       |
| Iman    | exit     | 10   | 21     | L93JTIZ       |
| Diana   | exit     | 10   | 23     | 322W7JE       |
| Kelsey  | exit     | 10   | 23     | 0NTHK55       |
| Taylor  | exit     | 10   | 35     | 1106N58

-- Check the interviews again
SELECT name, transcript, month, day FROM interviews
WHERE month = 7 AND day = 28 AND year = 2021

--CHeck atm logs for Leggett Street

-- check call logs for calls less than one minute

-- check people on earliest flight on 7/29

SELECT name, flights.id, airport_orig.city, airport_dest.city, flights.hour, flights.minute FROM people
    JOIN passengers on people.passport_number = passengers.passport_number
    JOIN flights on passengers.flight_id = flights.id
    JOIN airports AS airport_orig on origin_airport_id = airport_orig.id
    JOIN airports AS airport_dest on destination_airport_id = airport_dest.id
AND airport_orig.city = 'Fiftyville' AND flights.month = 7 AND flights.day = 29 AND flights.year = 2021
ORDER BY hour, minute

-- Suspects from earliest flight the next day:
+-----------+----+------------+---------------+------+--------+
|   name    | id |    city    |     city      | hour | minute |
+-----------+----+------------+---------------+------+--------+
| Doris     | 36 | Fiftyville | New York City | 8    | 20     |
| Sofia     | 36 | Fiftyville | New York City | 8    | 20     |
| Bruce     | 36 | Fiftyville | New York City | 8    | 20     |
| Edward    | 36 | Fiftyville | New York City | 8    | 20     |
| Kelsey    | 36 | Fiftyville | New York City | 8    | 20     |
| Taylor    | 36 | Fiftyville | New York City | 8    | 20     |
| Kenny     | 36 | Fiftyville | New York City | 8    | 20     |
| Luca      | 36 | Fiftyville | New York City | 8    | 20

-- main suspects = Bruce, Luca

