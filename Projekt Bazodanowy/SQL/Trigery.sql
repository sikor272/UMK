create or replace TRIGGER dodaj_sale
BEFORE INSERT OR UPDATE
ON Sale
FOR EACH ROW
DECLARE 
n INTEGER;
m INTEGER;
k INTEGER;
wprowadzona EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
	:NEW.nazwa := CONCAT(UPPER(SUBSTR(:NEW.nazwa, 1, 1)), SUBSTR(:NEW.nazwa, 2, length(:NEW.nazwa)));
    m := 0;
	SELECT MIN(id) INTO k
	FROM Sale;
	SELECT MIN(id+1) INTO n
	FROM Sale
	WHERE (id+1) NOT IN (SELECT id FROM Sale);
    SELECT COUNT(*) INTO m
    FROM Sale WHERE :NEW.nazwa = nazwa;
    IF n IS NULL THEN
        n := 1;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF m > 0 THEN
        RAISE wprowadzona;
    END IF;
    IF INSERTING THEN
        :NEW.id := n;
    END IF;
    COMMIT;
EXCEPTION
WHEN wprowadzona THEN
    RAISE_APPLICATION_ERROR(-20000, 'Taka sala jest juz w systemie');
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER dodaj_termin
BEFORE INSERT OR UPDATE
ON Zjazdy
FOR EACH ROW
DECLARE 
n INTEGER;
m INTEGER;
k INTEGER;
termin EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
	SELECT MIN(id) INTO k
	FROM Zjazdy;
	SELECT MIN(id+1) INTO n
	FROM Zjazdy
	WHERE (id+1) NOT IN (SELECT id FROM Zjazdy);
    SELECT COUNT(*) INTO m
    FROM Zjazdy WHERE :NEW.dzien = dzien;
    IF n IS NULL THEN
        n := 1;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF m > 0 THEN
        RAISE termin;
    END IF;
    IF INSERTING THEN
        :NEW.id := n;
    END IF;
    COMMIT;
EXCEPTION
WHEN termin THEN
    RAISE_APPLICATION_ERROR(-20001, 'Taki termin jest juz w systemie');
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER dodaj_grupe
BEFORE INSERT OR UPDATE
ON Grupy
FOR EACH ROW
DECLARE 
n INTEGER;
m INTEGER;
k INTEGER;
x INTEGER;
zajeta EXCEPTION;
nietykalna EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
    :New.grupa := UPPER(:New.grupa);
    :New.rok := UPPER(:New.rok);
	SELECT MIN(id) INTO k
	FROM Grupy;
	SELECT MIN(id+1) INTO n
	FROM Grupy
	WHERE (id+1) NOT IN (SELECT id FROM Grupy);
    SELECT COUNT(*) INTO m
    FROM Grupy WHERE :NEW.rok = rok;
    SELECT COUNT(*) INTO x
    FROM Grupy WHERE :OLD.rok = rok;
    IF m = 0 THEN
        :New.grupa := 'ALL';
    END IF;
    SELECT COUNT(*) INTO m
    FROM Grupy WHERE :NEW.grupa = grupa AND :NEW.rok = rok;
    IF n IS NULL THEN
        n := 1;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF :OLD.Grupa = 'ALL' THEN
        IF x > 1 THEN
            RAISE nietykalna;
        END IF;
        :New.grupa := 'ALL';
    END IF;
    IF m > 0 THEN
        RAISE zajeta;
    END IF;
    IF INSERTING THEN
        :NEW.id := n;
    END IF;
    COMMIT;
EXCEPTION
WHEN zajeta THEN
    RAISE_APPLICATION_ERROR(-20002, 'Taka grupa dla danego roku jest juz w systemie');
WHEN nietykalna THEN
    RAISE_APPLICATION_ERROR(-20006, 'Tej grupy nie wolno edytowac');
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER usun_grupe
BEFORE DELETE
ON Grupy
FOR EACH ROW
DECLARE 
m INTEGER;
nietykalna EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
    SELECT COUNT(*) INTO m
    FROM Grupy WHERE :OLD.rok = rok;
    IF :OLD.Grupa = 'ALL' THEN
        IF m > 1 THEN
            RAISE nietykalna;
        END IF;
    END IF;
    COMMIT;
EXCEPTION
WHEN nietykalna THEN
    RAISE_APPLICATION_ERROR(-20007, 'Pierw usun pozostale grupy');
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER dodaj_pracownika
BEFORE INSERT OR UPDATE
ON Pracownicy
FOR EACH ROW
DECLARE 
n INTEGER;
k INTEGER;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN

	:NEW.imie := CONCAT(UPPER(SUBSTR(:NEW.imie, 1, 1)), SUBSTR(:NEW.imie, 2, length(:NEW.imie)));
    :NEW.tytul := LOWER(:NEW.tytul);
	SELECT MIN(id) INTO k
	FROM Pracownicy;
	SELECT MIN(id+1) INTO n
	FROM Pracownicy
	WHERE (id+1) NOT IN (SELECT id FROM Pracownicy);
    IF n IS NULL THEN
        n := 1;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF INSERTING THEN
        :NEW.id := n;
    END IF;
    COMMIT;
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER dodaj_typ
BEFORE INSERT OR UPDATE
ON Typ
FOR EACH ROW
DECLARE 
n INTEGER;
m INTEGER;
k INTEGER;
wprowadzona EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
	:NEW.nazwa := CONCAT(UPPER(SUBSTR(:NEW.nazwa, 1, 1)), SUBSTR(:NEW.nazwa, 2, length(:NEW.nazwa)));
    m := 0;
	SELECT MIN(id) INTO k
	FROM Typ;
	SELECT MIN(id+1) INTO n
	FROM Typ
	WHERE (id+1) NOT IN (SELECT id FROM Typ);
    SELECT COUNT(*) INTO m
    FROM Typ WHERE :NEW.nazwa = nazwa;
    IF n IS NULL THEN
        n := 1;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF m > 0 THEN
        RAISE wprowadzona;
    END IF;
    IF INSERTING THEN
        :NEW.id := n;
    END IF;
    COMMIT;
EXCEPTION
WHEN wprowadzona THEN
    RAISE_APPLICATION_ERROR(-20003, 'Taki typ przedmiotu jest juz w systemie');
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER dodaj_przedmiot
BEFORE INSERT OR UPDATE
ON ProgramStudiow
FOR EACH ROW
DECLARE 
n INTEGER;
m INTEGER;
k INTEGER;
wprowadzona EXCEPTION;
godziny EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
	:NEW.nazwa := CONCAT(UPPER(SUBSTR(:NEW.nazwa, 1, 1)), SUBSTR(:NEW.nazwa, 2, length(:NEW.nazwa)));
    m := 0;
	SELECT MIN(id) INTO k
	FROM ProgramStudiow;
	SELECT MIN(id+1) INTO n
	FROM ProgramStudiow
	WHERE (id+1) NOT IN (SELECT id FROM ProgramStudiow);
    SELECT COUNT(*) INTO m
    FROM ProgramStudiow WHERE :New.typ_id = typ_id AND :NEW.nazwa = nazwa AND :New.id != id;
    IF n IS NULL THEN
        n := 1;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF m > 0 THEN
        RAISE wprowadzona;
    END IF;
    IF :NEW.ilosc_godzin < 0 THEN
        RAISE godziny;
    END IF;
    IF INSERTING THEN
        :NEW.id := n;
    END IF;
    COMMIT;
EXCEPTION
WHEN wprowadzona THEN
    RAISE_APPLICATION_ERROR(-20004, 'Taki przedmiot jest juz w systemie');
WHEN godziny THEN
    RAISE_APPLICATION_ERROR(-20005, 'Wprowadzono za mala ilosc godzin');
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER dodaj_przydzial
BEFORE INSERT OR UPDATE
ON Przydzialy
FOR EACH ROW
DECLARE 
n INTEGER;
k INTEGER;
m INTEGER;
wprowadzona EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
	SELECT MIN(id) INTO k
	FROM Przydzialy;
	SELECT MIN(id+1) INTO n
	FROM Przydzialy
	WHERE (id+1) NOT IN (SELECT id FROM Przydzialy);
    SELECT COUNT(*) INTO m
    FROM Przydzialy
    WHERE :NEW.programstudiow_id = programstudiow_id AND :NEW.pracownicy_id = pracownicy_id AND :NEW.grupy_id = grupy_id;
    IF n IS NULL THEN
        n := 1;
    END IF;
    IF m > 0 THEN
        RAISE wprowadzona;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF INSERTING THEN
        :NEW.id := n;
    END IF;
    COMMIT;
EXCEPTION
WHEN wprowadzona THEN
    RAISE_APPLICATION_ERROR(-20007, 'Taki przydzial jest juz w systemie');
END;
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------
create or replace TRIGGER dodaj_plan
BEFORE INSERT OR UPDATE
ON PlanZajec
FOR EACH ROW
DECLARE 
n INTEGER;
m INTEGER;
k INTEGER;
nalozenie EXCEPTION;
sala EXCEPTION;
godziny EXCEPTION;
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
    SELECT MIN(id) INTO k
	FROM PlanZajec;
	SELECT MIN(id+1) INTO n
	FROM PlanZajec
	WHERE (id+1) NOT IN (SELECT id FROM PlanZajec);
    IF n IS NULL THEN
        n := 1;
    END IF;
	IF k > 1 THEN
		n := 1;
	END IF;
    IF INSERTING THEN
        :NEW.id := n;
        SELECT COUNT(*) INTO k
        FROM planzajec
        WHERE zjazdy_id = :NEW.zjazdy_id AND :NEW.rozpoczecie < koniec AND :NEW.koniec > rozpoczecie AND
        przydzialy_id IN (SELECT id
                        FROM przydzialy
                        WHERE grupy_id = (SELECT grupy_id
                                        FROM przydzialy
                                        WHERE id = :NEW.przydzialy_id)
                            OR 
                            pracownicy_id = (SELECT pracownicy_id
                                        FROM przydzialy
                                        WHERE id = :NEW.przydzialy_id));
        IF k > 0 THEN
            RAISE nalozenie;
        END IF;
        SELECT COUNT(*) INTO k
        FROM planzajec
        WHERE zjazdy_id = :NEW.zjazdy_id AND sale_id = :NEW.sale_id AND :NEW.rozpoczecie < koniec AND :NEW.koniec > rozpoczecie;
        IF k > 0 THEN
            RAISE sala;
        END IF;
        SELECT SUM(koniec-rozpoczecie) INTO n
        FROM planzajec
        WHERE przydzialy_id = :NEW.przydzialy_id; 
        SELECT ilosc_godzin INTO m
        FROM programstudiow
        WHERE id = (SELECT programstudiow_id
                    FROM przydzialy
                    WHERE id = :NEW.przydzialy_id);
        k := n + :NEW.koniec - :NEW.rozpoczecie;
        IF k > m THEN
            RAISE godziny;
        END IF;
    END IF;
    IF UPDATING THEN
        SELECT COUNT(*) INTO k
        FROM planzajec
        WHERE id <> :OLD.id AND zjazdy_id = :NEW.zjazdy_id AND :NEW.rozpoczecie < koniec AND :NEW.koniec > rozpoczecie AND
        przydzialy_id IN (SELECT id
                        FROM przydzialy
                        WHERE grupy_id = (SELECT grupy_id
                                        FROM przydzialy
                                        WHERE id = :NEW.przydzialy_id)
                            OR 
                            pracownicy_id = (SELECT pracownicy_id
                                        FROM przydzialy
                                        WHERE id = :NEW.przydzialy_id));
        IF k > 0 THEN
            RAISE nalozenie;
        END IF;
        SELECT COUNT(*) INTO k
        FROM planzajec
        WHERE id <> :OLD.id AND zjazdy_id = :NEW.zjazdy_id AND sale_id = :NEW.sale_id AND :NEW.rozpoczecie < koniec AND :NEW.koniec > rozpoczecie;
        IF k > 0 THEN
            RAISE sala;
        END IF;
        SELECT SUM(koniec-rozpoczecie) INTO n
        FROM planzajec
        WHERE id <> :OLD.id AND przydzialy_id = :NEW.przydzialy_id; 
        SELECT ilosc_godzin INTO m
        FROM programstudiow
        WHERE id = (SELECT programstudiow_id
                    FROM przydzialy
                    WHERE id = :NEW.przydzialy_id);
        k := n + :NEW.koniec - :NEW.rozpoczecie;
        IF k > m THEN
            RAISE godziny;
        END IF;
    END IF;
    COMMIT;
EXCEPTION
WHEN nalozenie THEN
    RAISE_APPLICATION_ERROR(-20010, 'Dany pracownik lub grupa ma w tym czasie zajecia!');
WHEN sala THEN
    RAISE_APPLICATION_ERROR(-20011, 'Zajeta sala!');
WHEN godziny THEN
    RAISE_APPLICATION_ERROR(-20012, 'Zbyt duza laczna ilosc godzin!');
END;