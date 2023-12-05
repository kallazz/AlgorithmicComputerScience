-- 1.
CREATE DATABASE IF NOT EXISTS praca;
USE praca;


CREATE TABLE IF NOT EXISTS Ludzie (
    PESEL CHAR(11) NOT NULL,
    imie VARCHAR(30),
    nazwisko VARCHAR(30),
    data_urodzenia DATE,
    plec ENUM('K', 'M'),
    PRIMARY KEY (PESEL)
);

CREATE TABLE IF NOT EXISTS Zawody (
    zawod_id INT,
    nazwa VARCHAR(50),
    pensja_min FLOAT CHECK(pensja_min >= 0),
    pensja_max FLOAT CHECK(pensja_max >= 0 AND pensja_max > pensja_min),
    PRIMARY KEY (zawod_id)
);

CREATE TABLE IF NOT EXISTS Pracownicy (
    PESEL CHAR(11) NOT NULL,
    zawod_id INT,
    pensja FLOAT CHECK(pensja >= 0),
    FOREIGN KEY (PESEL) REFERENCES Ludzie(PESEL),
    FOREIGN KEY (zawod_id) REFERENCES Zawody(zawod_id),
    PRIMARY KEY (PESEL, zawod_id)
);

-- Sprawdzenie poprawności PESELa
CREATE TRIGGER IF NOT EXISTS insert_ludzie BEFORE INSERT ON Ludzie
FOR EACH ROW
BEGIN
    DECLARE gender_checker INT;
    DECLARE month_adjuster INT;
    DECLARE control_number INT;

    CASE
        WHEN (NEW.plec = 'M') THEN
            SET gender_checker = 1;
        ELSE
            SET gender_checker = 0;
    END CASE;

    CASE
        WHEN (YEAR(NEW.data_urodzenia) BETWEEN 2000 AND 2009) THEN
            SET month_adjuster = 20;
        ELSE
            SET month_adjuster = 0;
    END CASE;

    SET control_number = 10 -
        MOD(
            MOD(1 * CAST(SUBSTRING(NEW.PESEL, 1, 1)  AS SIGNED), 10) +
            MOD(3 * CAST(SUBSTRING(NEW.PESEL, 2, 1)  AS SIGNED), 10) +
            MOD(7 * CAST(SUBSTRING(NEW.PESEL, 3, 1)  AS SIGNED), 10) +
            MOD(9 * CAST(SUBSTRING(NEW.PESEL, 4, 1)  AS SIGNED), 10) +
            MOD(1 * CAST(SUBSTRING(NEW.PESEL, 5, 1)  AS SIGNED), 10) +
            MOD(3 * CAST(SUBSTRING(NEW.PESEL, 6, 1)  AS SIGNED), 10) +
            MOD(7 * CAST(SUBSTRING(NEW.PESEL, 7, 1)  AS SIGNED), 10) +
            MOD(9 * CAST(SUBSTRING(NEW.PESEL, 8, 1)  AS SIGNED), 10) +
            MOD(1 * CAST(SUBSTRING(NEW.PESEL, 9, 1)  AS SIGNED), 10) +
            MOD(3 * CAST(SUBSTRING(NEW.PESEL, 10, 1) AS SIGNED), 10)
            , 10
        );

    IF (
        LENGTH(NEW.PESEL) <> 11 OR
        SUBSTRING(NEW.PESEL, 1, 2) <> SUBSTRING(YEAR(NEW.data_urodzenia), 3, 2) OR
        SUBSTRING(NEW.PESEL, 3, 2) <> (MONTH(NEW.data_urodzenia) + month_adjuster) OR
        SUBSTRING(NEW.PESEL, 5, 2) <> DAY(NEW.data_urodzenia) OR
        CAST(SUBSTRING(NEW.PESEL, 10, 1) AS SIGNED) % 2 <> gender_checker OR
        control_number <> SUBSTRING(NEW.PESEL, 11, 1)
    ) THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Niepoprawny numer PESEL!';
    END IF;
END;

DROP TRIGGER insert_ludzie;
DROP DATABASE praca;

