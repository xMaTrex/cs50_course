-- Keep a log of any SQL queries you execute as you solve the mystery.


-- first get information about the crime on the date
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Humphrey Street";

-- OUTPUT:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- search for interviews from witnesses, maybe get their names, because they mentioned the bakery
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28;

-- better query would be:
SELECT name
FROM interviews
WHERE month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- OUTPUT:
-- | Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
--  Eugene   | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- | Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- | Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.

-- -> Ruth + Eugene + Raymond = witnesses

-- further investigations on the information out of the transcripts from the 3

-- car on parking lot within 10min:
SELECT activity, license_plate, hour, minute
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit";

-- possible licence plates:
-- 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55, 1106N58

-- ATM Leggett Street, earlier this morning:
SELECT id, account_number, amount
FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location LIKE "%Legget%";

-- possible bank acc number:
-- 28500762 48$, 28296815 20$, 76054385 60$, 49610011 50$, 16153065 80$, 25506511 20$, 81061156 30$, 26013199 35$

-- telephone call, earliest flight out of 50Ville on 07/29 other person should buy tickets:
-- lots of information, probably small duration call but no detailled information out here

-- airport ID from 50Ville:
SELECT *
FROM airports;

-- airport ID 50 Ville = 8, abb: CSF

-- earliest flight out of 50Ville on 07/29:
SELECT *
FROM flights
WHERE origin_airport_id = 8 AND month = 7 AND day = 29
ORDER BY hour;

-- earliest flight out of 50 Ville: -> to dest_airport_id 4, flight id = 36
-- flight id 36 -> LGA LaGuardia Airport, New York City on 07/29 at 8:20 AM

-- who booked tickets for this flight (id = 36): -> passengers
SELECT *
FROM passengers
WHERE flight_id = 36;

-- possible passport_numbers:
-- 7214083635, 1695452385, 5773159633, 1540955065, 8294398571, 1988161715, 9878712108, 8496433585

-- match passport_numbers with names:
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8 AND flights.minute = 20
ORDER BY passengers.passport_number;

 -- one of these guys is the thief:
 -- Edward, Sofia, Taylor, Bruce, Doris, Kelsey, Luca, Kenny

 -- check who calls someone from these guys in the timezone, probably short duration:
SELECT name, phone_calls.duration
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;
 -- callers: Kelsey, Carina, Taylor, Bruce, Diana, Kelsey, Sofia, Benista, Kenny, Kathryn

 -- caller and passengers:
 -- Sofia, Taylor, Bruce, Kelsey, Kenny

-- check license plate on parking lot at bakery:
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
   AND bakery_security_logs.activity = 'exit' AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 15
   AND bakery_security_logs.minute <= 25
ORDER BY bakery_security_logs.minute;

-- possible thiefs: Sofia, Bruce, Kelsey

-- check withdraw money on ATM
SELECT name, atm_transactions.amount
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw';

-- Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista

-- -> thief = Bruce


-- check call receivers from Bruce
SELECT people.name
FROM people
WHERE people.phone_number IN (
	SELECT receiver
	FROM phone_calls
	WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    AND caller = (
	    SELECT people.phone_number
        FROM people
        WHERE people.name = "Bruce"
    )
);

-- Robin