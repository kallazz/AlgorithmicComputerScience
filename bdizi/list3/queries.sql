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
    zawod_id INT NOT NULL AUTO_INCREMENT,
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
CREATE TRIGGER IF NOT EXISTS on_insert_ludzie BEFORE INSERT ON Ludzie
FOR EACH ROW
BEGIN
    DECLARE gender_checker INT;
    DECLARE month_adjuster INT;
    DECLARE control_number INT;

    SET gender_checker = CASE WHEN NEW.plec = 'M' THEN 1 ELSE 0 END;
    SET month_adjuster = CASE WHEN (YEAR(NEW.data_urodzenia) BETWEEN 2000 AND 2099)
        THEN 20 ELSE 0 END;

    SET control_number =
        MOD(
            MOD(9 * CAST(SUBSTRING(NEW.PESEL, 1, 1)  AS UNSIGNED), 10) +
            MOD(7 * CAST(SUBSTRING(NEW.PESEL, 2, 1)  AS UNSIGNED), 10) +
            MOD(3 * CAST(SUBSTRING(NEW.PESEL, 3, 1)  AS UNSIGNED), 10) +
            MOD(1 * CAST(SUBSTRING(NEW.PESEL, 4, 1)  AS UNSIGNED), 10) +
            MOD(9 * CAST(SUBSTRING(NEW.PESEL, 5, 1)  AS UNSIGNED), 10) +
            MOD(7 * CAST(SUBSTRING(NEW.PESEL, 6, 1)  AS UNSIGNED), 10) +
            MOD(3 * CAST(SUBSTRING(NEW.PESEL, 7, 1)  AS UNSIGNED), 10) +
            MOD(1 * CAST(SUBSTRING(NEW.PESEL, 8, 1)  AS UNSIGNED), 10) +
            MOD(9 * CAST(SUBSTRING(NEW.PESEL, 9, 1)  AS UNSIGNED), 10) +
            MOD(7 * CAST(SUBSTRING(NEW.PESEL, 10, 1) AS UNSIGNED), 10)
            , 10
        );
    IF (
        LENGTH(NEW.PESEL) <> 11 OR
        SUBSTRING(NEW.PESEL, 1, 2) <> SUBSTRING(YEAR(NEW.data_urodzenia), 3, 2) OR
        SUBSTRING(NEW.PESEL, 3, 2) <> (MONTH(NEW.data_urodzenia) + month_adjuster) OR
        SUBSTRING(NEW.PESEL, 5, 2) <> DAYOFMONTH(NEW.data_urodzenia) OR
        MOD((CAST(SUBSTRING(NEW.PESEL, 10, 1) AS UNSIGNED)), 2) <> gender_checker OR
        control_number <> SUBSTRING(NEW.PESEL, 11, 1)
    ) THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = "Niepoprawny numer PESEL!";
    END IF;
END;

-- Generowanie poprawnego PESELa
CREATE FUNCTION IF NOT EXISTS generuj_pesel(data_urodzenia DATE, plec CHAR)
RETURNS CHAR(11)
BEGIN
    DECLARE pesel CHAR(11);
    DECLARE gender_digit INT;
    DECLARE month_adjuster INT;

    SET gender_digit = CASE WHEN plec = 'K' THEN 2 ELSE 1 END;
    SET month_adjuster = CASE WHEN YEAR(data_urodzenia) >= 2000 THEN 20 ELSE 0 END;

    SET pesel = CONCAT(
            SUBSTRING(YEAR(data_urodzenia), 3, 2),
            LPAD((MONTH(data_urodzenia) + month_adjuster), 2, '0'),
            LPAD(DAYOFMONTH(data_urodzenia), 2, '0'),
            FLOOR(RAND()*10),
            FLOOR(RAND()*10),
            FLOOR(RAND()*10),
            gender_digit
        );
        SET pesel = CONCAT(
            pesel,
            MOD(
                MOD(9 * CAST(SUBSTRING(pesel, 1, 1) AS UNSIGNED), 10) +
                MOD(7 * CAST(SUBSTRING(pesel, 2, 1) AS UNSIGNED), 10) +
                MOD(3 * CAST(SUBSTRING(pesel, 3, 1) AS UNSIGNED), 10) +
                MOD(1 * CAST(SUBSTRING(pesel, 4, 1) AS UNSIGNED), 10) +
                MOD(9 * CAST(SUBSTRING(pesel, 5, 1) AS UNSIGNED), 10) +
                MOD(7 * CAST(SUBSTRING(pesel, 6, 1) AS UNSIGNED), 10) +
                MOD(3 * CAST(SUBSTRING(pesel, 7, 1) AS UNSIGNED), 10) +
                MOD(1 * CAST(SUBSTRING(pesel, 8, 1) AS UNSIGNED), 10) +
                MOD(9 * CAST(SUBSTRING(pesel, 9, 1) AS UNSIGNED), 10) +
                MOD(7 * CAST(SUBSTRING(pesel, 10, 1) AS UNSIGNED), 10),
                10
            )
        );

    RETURN pesel;
END;

-- Wstawianie informacji o 5 osobach niepełnoletnich
INSERT INTO Ludzie (PESEL, imie, nazwisko, data_urodzenia, plec)
VALUES
  (generuj_pesel('2008-01-01', 'K'), 'Anna', 'Nowak', '2008-01-01', 'K'),
  (generuj_pesel('2007-02-15', 'M'), 'Jan', 'Kowalski', '2007-02-15', 'M'),
  (generuj_pesel('2009-05-20', 'K'), 'Katarzyna', 'Wiśniewska', '2009-05-20', 'K'),
  (generuj_pesel('2010-09-10', 'M'), 'Piotr', 'Lis', '2010-09-10', 'M'),
  (generuj_pesel('2011-11-30', 'K'), 'Małgorzata', 'Dąbrowska', '2011-11-30', 'K');


-- Wstawianie informacji o 5 osobach w wieku co najmniej 60 lat
INSERT INTO Ludzie (PESEL, imie, nazwisko, data_urodzenia, plec)
VALUES
  (generuj_pesel('1960-01-01', 'K'), 'Barbara', 'Kowalczyk', '1960-01-01', 'K'),
  (generuj_pesel('1958-04-15', 'M'), 'Stanisław', 'Nowak', '1958-04-15', 'M'),
  (generuj_pesel('1956-07-20', 'K'), 'Zofia', 'Lis', '1956-07-20', 'K'),
  (generuj_pesel('1955-09-10', 'M'), 'Tadeusz', 'Szymański', '1955-09-10', 'M'),
  (generuj_pesel('1954-11-30', 'K'), 'Irena', 'Duda', '1954-11-30', 'K');

-- Wstawianie informacji o 45 osobach dorosłych w wieku poniżej 60 lat
INSERT INTO Ludzie (PESEL, imie, nazwisko, data_urodzenia, plec)
VALUES
    (generuj_pesel('1965-05-15', 'M'), 'Jan', 'Kowalski', '1965-05-15', 'M'),
    (generuj_pesel('1966-08-22', 'K'), 'Anna', 'Nowak', '1966-08-22', 'K'),
    (generuj_pesel('1967-12-10', 'M'), 'Piotr', 'Wiśniewski', '1967-12-10', 'M'),
    (generuj_pesel('1968-03-05', 'K'), 'Katarzyna', 'Dąbrowska', '1968-03-05', 'K'),
    (generuj_pesel('1969-07-30', 'M'), 'Marcin', 'Lewandowski', '1969-07-30', 'M'),
    (generuj_pesel('1970-02-18', 'K'), 'Mateusz', 'Kozłowski', '1970-02-18', 'K'),
    (generuj_pesel('1971-11-03', 'K'), 'Magdalena', 'Jankowska', '1971-11-03', 'K'),
    (generuj_pesel('1972-09-20', 'M'), 'Grzegorz', 'Wójcik', '1972-09-20', 'M'),
    (generuj_pesel('1973-04-12', 'K'), 'Natalia', 'Kaczmarek', '1973-04-12', 'K'),
    (generuj_pesel('1974-06-25', 'M'), 'Adam', 'Mazur', '1974-06-25', 'M'),
    (generuj_pesel('1975-10-08', 'K'), 'Ewa', 'Adamczyk', '1975-10-08', 'K'),
    (generuj_pesel('1976-01-29', 'M'), 'Tomasz', 'Kwiatkowski', '1976-01-29', 'M'),
    (generuj_pesel('1977-07-15', 'K'), 'Izabela', 'Krawczyk', '1977-07-15', 'K'),
    (generuj_pesel('1978-12-04', 'M'), 'Dawid', 'Piotrowski', '1978-12-04', 'M'),
    (generuj_pesel('1979-09-17', 'K'), 'Patrycja', 'Grabowska', '1979-09-17', 'K'),
    (generuj_pesel('1980-03-08', 'M'), 'Kamil', 'Nowakowski', '1980-03-08', 'M'),
    (generuj_pesel('1981-05-23', 'K'), 'Monika', 'Zielińska', '1981-05-23', 'K'),
    (generuj_pesel('1982-08-31', 'M'), 'Rafał', 'Szymański', '1982-08-31', 'M'),
    (generuj_pesel('1983-06-10', 'K'), 'Alicja', 'Jabłońska', '1983-06-10', 'K'),
    (generuj_pesel('1984-02-14', 'M'), 'Michał', 'Olszewski', '1984-02-14', 'M'),
    (generuj_pesel('1985-05-15', 'K'), 'Agnieszka', 'Witkowska', '1985-05-15', 'K'),
    (generuj_pesel('1986-08-22', 'M'), 'Bartłomiej', 'Kubiak', '1986-08-22', 'M'),
    (generuj_pesel('1987-12-10', 'K'), 'Karolina', 'Sikora', '1987-12-10', 'K'),
    (generuj_pesel('1988-03-05', 'M'), 'Łukasz', 'Ostrowski', '1988-03-05', 'M'),
    (generuj_pesel('1989-07-30', 'M'), 'Dariusz', 'Zając', '1989-07-30', 'M'),
    (generuj_pesel('1990-02-18', 'K'), 'Marcelina', 'Rutkowska', '1990-02-18', 'K'),
    (generuj_pesel('1991-11-03', 'M'), 'Marek', 'Baran', '1991-11-03', 'M'),
    (generuj_pesel('1992-09-20', 'K'), 'Kamila', 'Lis', '1992-09-20', 'K'),
    (generuj_pesel('1993-04-12', 'M'), 'Radosław', 'Głowacki', '1993-04-12', 'M'),
    (generuj_pesel('1994-06-25', 'K'), 'Dominika', 'Pawłowska', '1994-06-25', 'K'),
    (generuj_pesel('1995-10-08', 'M'), 'Hubert', 'Witkowski', '1995-10-08', 'M'),
    (generuj_pesel('1977-01-29', 'K'), 'Ewelina', 'Jóźwiak', '1977-01-29', 'K'),
    (generuj_pesel('1998-07-15', 'M'), 'Szymon', 'Sawicki', '1998-07-15', 'M'),
    (generuj_pesel('1984-12-04', 'K'), 'Nikola', 'Majewska', '1984-12-04', 'K'),
    (generuj_pesel('1993-09-17', 'M'), 'Artur', 'Czarnecki', '1993-09-17', 'M'),
    (generuj_pesel('1979-03-08', 'K'), 'Adrianna', 'Tomaszewska', '1979-03-08', 'K'),
    (generuj_pesel('1991-05-23', 'M'), 'Krzysztof', 'Włodarczyk', '1991-05-23', 'M'),
    (generuj_pesel('1981-08-31', 'K'), 'Patrycja', 'Piotrowska', '1981-08-31', 'K'),
    (generuj_pesel('1997-06-10', 'M'), 'Daniel', 'Kaczmarczyk', '1997-06-10', 'M'),
    (generuj_pesel('1987-02-14', 'K'), 'Oliwia', 'Borkowska', '1987-02-14', 'K'),
    (generuj_pesel('1980-05-15', 'M'), 'Adrian', 'Sokołowski', '1980-05-15', 'M'),
    (generuj_pesel('1982-08-22', 'K'), 'Justyna', 'Kaczorowska', '1982-08-22', 'K'),
    (generuj_pesel('1975-12-10', 'M'), 'Łukasz', 'Gajewski', '1975-12-10', 'M'),
    (generuj_pesel('1990-03-05', 'K'), 'Natalia', 'Pawlak', '1990-03-05', 'K'),
    (generuj_pesel('1965-07-30', 'M'), 'Mikołaj', 'Zalewski', '1965-07-30', 'M');

INSERT INTO Zawody(nazwa, pensja_min, pensja_max)
VALUES
    ("Polityk", 10000, 50000),
    ("Nauczyciel", 5000, 8000),
    ("Informatyk", 3000, 50000),
    ("Lekarz", 5000, 60000);

-- Wstawianie do tabeli Pracownicy przy użyciu kursora
CREATE PROCEDURE IF NOT EXISTS insert_pracownicy()
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE pesel_var CHAR(11);
    DECLARE imie_var VARCHAR(30);
    DECLARE nazwisko_var VARCHAR(30);
    DECLARE data_urodzenia_var DATE;
    DECLARE plec_var CHAR;
    DECLARE zawod_id_var INT;
    DECLARE pensja_var FLOAT;
    DECLARE pensja_min_var FLOAT;

    DECLARE pelnoletni_cursor CURSOR FOR
            SELECT PESEL, imie, nazwisko, data_urodzenia, plec
            FROM Ludzie
            WHERE YEAR(CURDATE()) - YEAR(data_urodzenia) >= 18;
    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET done = TRUE;

    OPEN pelnoletni_cursor;

    r: LOOP
        FETCH pelnoletni_cursor INTO pesel_var, imie_var, nazwisko_var, data_urodzenia_var, plec_var;
        IF done THEN
            LEAVE r;
        END IF;

        IF plec_var = 'M' AND YEAR(CURDATE()) - YEAR(data_urodzenia_var) <= 65 OR
           plec_var = 'K' AND YEAR(CURDATE()) - YEAR(data_urodzenia_var) <= 60 THEN
            SET zawod_id_var = FLOOR(RAND() * 4) + 1; -- Z lekarzami
            SET pensja_var = ROUND(RAND() * (SELECT (pensja_max + 1) FROM Zawody WHERE zawod_id = zawod_id_var), 2);
            SET pensja_min_var = (SELECT pensja_min FROM Zawody WHERE zawod_id = zawod_id_var);
            IF pensja_var < pensja_min_var THEN
                SET pensja_var = pensja_min_var;
            END IF;
        ELSE
            SET zawod_id_var = FLOOR(RAND() * 3) + 1; -- Bez lekarzy
            SET pensja_var = ROUND(RAND() * (SELECT (pensja_max + 1) FROM Zawody WHERE zawod_id = zawod_id_var), 2);
            SET pensja_min_var = (SELECT pensja_min FROM Zawody WHERE zawod_id = zawod_id_var);
            IF pensja_var < pensja_min_var THEN
                SET pensja_var = pensja_min_var;
            END IF;
        END IF;

        INSERT INTO Pracownicy (PESEL, zawod_id, pensja)
        VALUES (pesel_var, zawod_id_var, pensja_var);
    END LOOP;

    CLOSE pelnoletni_cursor;
END;

CALL insert_pracownicy;

-- 2.
CREATE INDEX ludzie_idx ON Ludzie(plec, imie);
CREATE INDEX pracownicy_idx ON Pracownicy(pensja);

EXPLAIN SELECT * FROM Ludzie WHERE plec = 'K' AND imie LIKE 'A%'; -- indeks użyty
EXPLAIN SELECT * FROM Ludzie WHERE plec = 'K';
EXPLAIN SELECT * FROM Ludzie WHERE imie LIKE 'K%';
EXPLAIN SELECT * FROM Pracownicy WHERE pensja < 2000; -- indeks użyty
EXPLAIN SELECT * FROM
Pracownicy
INNER JOIN Zawody
ON Pracownicy.zawod_id = Zawody.zawod_id
INNER JOIN Ludzie
ON Pracownicy.PESEL = Ludzie.PESEL
WHERE nazwa = 'Informatyk' AND plec = 'M' AND pensja > 10000; -- indeks użyty

SHOW INDEX FROM Ludzie;
SHOW INDEX FROM Pracownicy;

-- 3.
CREATE PROCEDURE IF NOT EXISTS daj_podwyzke(nazwa_zawodu VARCHAR(50))
daj_podwyzke_label: BEGIN
    DECLARE pensja_maksymalna FLOAT;
    DECLARE faktyczna_najwieksza_pensja FLOAT;

    SET pensja_maksymalna = (
        SELECT pensja_max FROM 
        Pracownicy
        INNER JOIN Zawody
        ON Pracownicy.zawod_id = Zawody.zawod_id
        WHERE Zawody.nazwa = nazwa_zawodu
        LIMIT 1
    );

    SET faktyczna_najwieksza_pensja = (
        SELECT MAX(Pracownicy.pensja) FROM 
        Pracownicy
        INNER JOIN Zawody
        ON Pracownicy.zawod_id = Zawody.zawod_id
        WHERE Zawody.nazwa = nazwa_zawodu
    );

    IF faktyczna_najwieksza_pensja > pensja_maksymalna THEN
        LEAVE daj_podwyzke_label;
    END IF;

    UPDATE Pracownicy
    INNER JOIN Zawody ON Pracownicy.zawod_id = Zawody.zawod_id
    SET Pracownicy.pensja = Pracownicy.pensja * 1.05
    WHERE Zawody.nazwa = nazwa_zawodu;

END daj_podwyzke_label;

-- 4.
SET @sql_query = "
    SELECT COUNT(*) FROM
    Pracownicy
    INNER JOIN Ludzie ON
    Pracownicy.PESEL = Ludzie.PESEL
    INNER JOIN Zawody ON
    Pracownicy.zawod_id = Zawody.zawod_id
    WHERE Ludzie.plec = 'K'
    AND Zawody.nazwa = ?
";
PREPARE stmt_zlicz_kobiety_w_zawodzie FROM @sql_query;

EXECUTE stmt_zlicz_kobiety_w_zawodzie USING 'Informatyk';
