CREATE TABLE grupy (
    id      INTEGER NOT NULL,
    rok     VARCHAR2(20) NOT NULL,
    grupa   VARCHAR2(3) NOT NULL
);

ALTER TABLE grupy ADD CONSTRAINT grupy_pk PRIMARY KEY ( id );

CREATE TABLE planzajec (
    rozpoczecie     INTEGER NOT NULL,
    koniec          INTEGER NOT NULL,
    sale_id         INTEGER NOT NULL,
    zjazdy_id       INTEGER NOT NULL,
    przydzialy_id   INTEGER NOT NULL
);

CREATE TABLE pracownicy (
    id         INTEGER NOT NULL,
    imie       VARCHAR2(20) NOT NULL,
    nazwisko   VARCHAR2(20) NOT NULL,
    tytul      VARCHAR2(20) NOT NULL,
    lokalny    NUMBER DEFAULT 1 NOT NULL
);

ALTER TABLE pracownicy ADD CONSTRAINT pracownicy_pk PRIMARY KEY ( id );

CREATE TABLE programstudiow (
    id             INTEGER NOT NULL,
    nazwa          VARCHAR2(50) NOT NULL,
    ilosc_godzin   INTEGER NOT NULL,
    typ_id         INTEGER NOT NULL
);

ALTER TABLE programstudiow ADD CONSTRAINT programstudiow_pk PRIMARY KEY ( id );

CREATE TABLE przydzialy (
    id                  INTEGER NOT NULL,
    programstudiow_id   INTEGER NOT NULL,
    pracownicy_id       INTEGER NOT NULL,
    grupy_id            INTEGER NOT NULL
);

ALTER TABLE przydzialy ADD CONSTRAINT przydzialy_pk PRIMARY KEY ( id );

CREATE TABLE sale (
    id      INTEGER NOT NULL,
    nazwa   VARCHAR2(10) NOT NULL
);

ALTER TABLE sale ADD CONSTRAINT sale_pk PRIMARY KEY ( id );

CREATE TABLE typ (
    id      INTEGER NOT NULL,
    nazwa   VARCHAR2(15) NOT NULL
);

ALTER TABLE typ ADD CONSTRAINT typ_pk PRIMARY KEY ( id );

CREATE TABLE zjazdy (
    id      INTEGER NOT NULL,
    dzien   DATE NOT NULL
);

ALTER TABLE zjazdy ADD CONSTRAINT zjazdy_pk PRIMARY KEY ( id );

ALTER TABLE planzajec
    ADD CONSTRAINT planzajec_przydzialy_fk FOREIGN KEY ( przydzialy_id )
        REFERENCES przydzialy ( id );

ALTER TABLE planzajec
    ADD CONSTRAINT planzajec_sale_fk FOREIGN KEY ( sale_id )
        REFERENCES sale ( id );

ALTER TABLE planzajec
    ADD CONSTRAINT planzajec_zjazdy_fk FOREIGN KEY ( zjazdy_id )
        REFERENCES zjazdy ( id );

ALTER TABLE programstudiow
    ADD CONSTRAINT programstudiow_typ_fk FOREIGN KEY ( typ_id )
        REFERENCES typ ( id );

ALTER TABLE przydzialy
    ADD CONSTRAINT przydzialy_grupy_fk FOREIGN KEY ( grupy_id )
        REFERENCES grupy ( id );

ALTER TABLE przydzialy
    ADD CONSTRAINT przydzialy_pracownicy_fk FOREIGN KEY ( pracownicy_id )
        REFERENCES pracownicy ( id );

ALTER TABLE przydzialy
    ADD CONSTRAINT przydzialy_programstudiow_fk FOREIGN KEY ( programstudiow_id )
        REFERENCES programstudiow ( id );