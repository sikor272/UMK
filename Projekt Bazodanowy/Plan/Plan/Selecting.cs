using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Oracle.DataAccess.Client;

namespace Plan
{
    class Selecting : Connect
    {
        public Selecting() : base() { }
        public Student[] ListaStudentow()
        {
            List<Student> dane = new List<Student>();
            Student[] zwracane = null;
            string oracleQuery = "SELECT id,rok,grupa FROM Grupy";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if(Id > max)
                    {
                        max = Id;
                    }
                    string Rok = wynik["rok"].ToString();
                    string Grupa = wynik["grupa"].ToString();
                    dane.Add(new Student(Id, Rok, Grupa));
                }
                wynik.Close();
                zwracane = new Student[max + 1];
                foreach(Student item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Pracownik[] ListaPracownikow()
        {
            List<Pracownik> dane = new List<Pracownik>();
            Pracownik[] zwracane = null;
            string oracleQuery = "SELECT id,imie,nazwisko,tytul,lokalny FROM Pracownicy";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if(Id > max)
                    {
                        max = Id;
                    }
                    string Imie = wynik["imie"].ToString();
                    string Nazwisko = wynik["nazwisko"].ToString();
                    string Tytul = wynik["tytul"].ToString();
                    int.TryParse(wynik["lokalny"].ToString(), out int Lokalny);
                    dane.Add(new Pracownik(Id, Imie, Nazwisko, Tytul, Lokalny));
                }
                wynik.Close();
                zwracane = new Pracownik[max + 1];
                foreach (Pracownik item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Sala[] ListaSal()
        {
            List<Sala> dane = new List<Sala>();
            Sala[] zwracane = null;
            string oracleQuery = "SELECT id,nazwa FROM Sale ORDER BY nazwa";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if(Id > max)
                    {
                        max = Id;
                    }
                    string Nazwa = wynik["nazwa"].ToString();
                    dane.Add(new Sala(Id, Nazwa));
                }
                wynik.Close();
                zwracane = new Sala[max + 1];
                foreach(Sala item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Termin[] ListaTerminy()
        {
            List<Termin> dane = new List<Termin>();
            Termin[] zwracane = null;
            string oracleQuery = "SELECT id,to_char(dzien , 'dd.mm.yyyy') as data FROM Zjazdy";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if(Id > max)
                    {
                        max = Id;
                    }
                    string Data = wynik["data"].ToString();
                    dane.Add(new Termin(Id, Data));
                }
                wynik.Close();
                zwracane = new Termin[max + 1];
                foreach(Termin item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Przedmiot[] ListaPrzedmiotow()
        {
            List<Przedmiot> dane = new List<Przedmiot>();
            Przedmiot[] zwracane = null;
            string oracleQuery = "SELECT id,nazwa,ilosc_godzin as ile,typ_id FROM programstudiow";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    string Nazwa = wynik["nazwa"].ToString();
                    int.TryParse(wynik["ile"].ToString(), out int Ilosc);
                    int.TryParse(wynik["typ_id"].ToString(), out int Id_Typ);
                    dane.Add(new Przedmiot(Id, Nazwa, Ilosc, Id_Typ));
                }
                wynik.Close();
                zwracane = new Przedmiot[max + 1];
                foreach(Przedmiot item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Typ[] ListaTypow()
        {
            List<Typ> dane = new List<Typ>();
            Typ[] zwracane = null;
            string oracleQuery = "SELECT id,nazwa FROM Typ";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    string Nazwa = wynik["nazwa"].ToString();
                    dane.Add(new Typ(Id, Nazwa));
                }
                wynik.Close();
                zwracane = new Typ[max + 1];
                foreach(Typ item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Przydzial[] ListaPrzydzialow()
        {
            List<Przydzial> dane = new List<Przydzial>();
            Przydzial[] zwracane = null;
            /*string oracleQuery = "SELECT przydzialy.id as id, grupy.id as idgrupa, rok, grupa, " +
                                 "pracownicy.id as idpracownik, imie, nazwisko, tytul, lokalny, " +
                                 "programstudiow.id as idprzedmiot, programstudiow.nazwa as przedmiot, ilosc_godzin as ile, " +
                                 "typ.nazwa as typ, typ.id as idtyp " +
                                 "FROM Przydzialy JOIN Grupy ON przydzialy.grupy_id = grupy.id " +
                                 "JOIN Pracownicy ON przydzialy.pracownicy_id = pracownicy.id " +
                                 "JOIN ProgramStudiow ON przydzialy.programstudiow_id = programstudiow.id " +
                                 "JOIN typ ON programstudiow.typ_id = typ.id";*/
            string oracleQuery = "SELECT id,programstudiow_id as przedmiot,pracownicy_id as pracownik,grupy_id as grupa FROM Przydzialy";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    int.TryParse(wynik["grupa"].ToString(), out int Idgrupa);
                    int.TryParse(wynik["przedmiot"].ToString(), out int Idprzedmiot);
                    int.TryParse(wynik["pracownik"].ToString(), out int Idpracownik);
                    dane.Add(new Przydzial(Id, Idprzedmiot, Idpracownik, Idgrupa));
                }
                wynik.Close();
                zwracane = new Przydzial[max + 1];
                foreach(Przydzial item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Przydzial[] ListaPrzydzialowPracownika(int id)
        {
            List<Przydzial> dane = new List<Przydzial>();
            Przydzial[] zwracane = null;
            /*string oracleQuery = "SELECT przydzialy.id as id, grupy.id as idgrupa, rok, grupa, " +
                                 "pracownicy.id as idpracownik, imie, nazwisko, tytul, lokalny, " +
                                 "programstudiow.id as idprzedmiot, programstudiow.nazwa as przedmiot, ilosc_godzin as ile, " +
                                 "typ.nazwa as typ, typ.id as idtyp " +
                                 "FROM Przydzialy JOIN Grupy ON przydzialy.grupy_id = grupy.id " +
                                 "JOIN Pracownicy ON przydzialy.pracownicy_id = pracownicy.id " +
                                 "JOIN ProgramStudiow ON przydzialy.programstudiow_id = programstudiow.id " +
                                 "JOIN typ ON programstudiow.typ_id = typ.id";*/
            string oracleQuery = "SELECT id,programstudiow_id as przedmiot,pracownicy_id as pracownik,grupy_id as grupa " +
                "                   FROM Przydzialy WHERE pracownicy_id = :id_prac";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("id_prac", id);
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    int.TryParse(wynik["grupa"].ToString(), out int Idgrupa);
                    int.TryParse(wynik["przedmiot"].ToString(), out int Idprzedmiot);
                    int.TryParse(wynik["pracownik"].ToString(), out int Idpracownik);
                    dane.Add(new Przydzial(Id, Idprzedmiot, Idpracownik, Idgrupa));
                }
                wynik.Close();
                zwracane = new Przydzial[max + 1];
                foreach (Przydzial item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public Przydzial[] ListaPrzydzialowStudentow(string nazwa)
        {
            List<Przydzial> dane = new List<Przydzial>();
            Przydzial[] zwracane = null;
            /*string oracleQuery = "SELECT przydzialy.id as id, grupy.id as idgrupa, rok, grupa, " +
                                 "pracownicy.id as idpracownik, imie, nazwisko, tytul, lokalny, " +
                                 "programstudiow.id as idprzedmiot, programstudiow.nazwa as przedmiot, ilosc_godzin as ile, " +
                                 "typ.nazwa as typ, typ.id as idtyp " +
                                 "FROM Przydzialy JOIN Grupy ON przydzialy.grupy_id = grupy.id " +
                                 "JOIN Pracownicy ON przydzialy.pracownicy_id = pracownicy.id " +
                                 "JOIN ProgramStudiow ON przydzialy.programstudiow_id = programstudiow.id " +
                                 "JOIN typ ON programstudiow.typ_id = typ.id";*/
            string oracleQuery = "SELECT id,programstudiow_id as przedmiot,pracownicy_id as pracownik,grupy_id as grupa " +
                "                   FROM Przydzialy WHERE grupy_id IN (SELECT id FROM grupy WHERE rok = :rocznik)";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("rocznik", nazwa);
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    int.TryParse(wynik["grupa"].ToString(), out int Idgrupa);
                    int.TryParse(wynik["przedmiot"].ToString(), out int Idprzedmiot);
                    int.TryParse(wynik["pracownik"].ToString(), out int Idpracownik);
                    dane.Add(new Przydzial(Id, Idprzedmiot, Idpracownik, Idgrupa));
                }
                wynik.Close();
                zwracane = new Przydzial[max + 1];
                foreach (Przydzial item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public ElementPlanu[] ListaPlanPracownika(int id)
        {
            List<ElementPlanu> dane = new List<ElementPlanu>();
            ElementPlanu[] zwracane = null;
            string oracleQuery = "SELECT id,rozpoczecie,koniec,sale_id,zjazdy_id,przydzialy_id FROM PlanZajec WHERE przydzialy_id IN " +
                                "(SELECT id FROM przydzialy WHERE pracownicy_id = :id_prac )";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("id_prac", id);
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    int.TryParse(wynik["rozpoczecie"].ToString(), out int Id_r);
                    int.TryParse(wynik["koniec"].ToString(), out int Id_z);
                    int.TryParse(wynik["sale_id"].ToString(), out int Id_s);
                    int.TryParse(wynik["zjazdy_id"].ToString(), out int Id_t);
                    int.TryParse(wynik["przydzialy_id"].ToString(), out int Id_p);
                    dane.Add(new ElementPlanu(Id, Id_r, Id_z, Id_s, Id_t, Id_p));
                }
                wynik.Close();
                zwracane = new ElementPlanu[max + 1];
                foreach (ElementPlanu item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public ElementPlanu[] ListaPlanStudentow(string nazwa)
        {
            List<ElementPlanu> dane = new List<ElementPlanu>();
            ElementPlanu[] zwracane = null;
            string oracleQuery = "SELECT id,rozpoczecie,koniec,sale_id,zjazdy_id,przydzialy_id FROM PlanZajec WHERE przydzialy_id IN " +
                                "(SELECT id FROM przydzialy WHERE grupy_id IN (SELECT id FROM grupy WHERE rok = :rocznik))";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("rocznik", nazwa);
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    int.TryParse(wynik["rozpoczecie"].ToString(), out int Id_r);
                    int.TryParse(wynik["koniec"].ToString(), out int Id_z);
                    int.TryParse(wynik["sale_id"].ToString(), out int Id_s);
                    int.TryParse(wynik["zjazdy_id"].ToString(), out int Id_t);
                    int.TryParse(wynik["przydzialy_id"].ToString(), out int Id_p);
                    dane.Add(new ElementPlanu(Id, Id_r, Id_z, Id_s, Id_t, Id_p));
                }
                wynik.Close();
                zwracane = new ElementPlanu[max + 1];
                foreach (ElementPlanu item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public ElementPlanu[] ListaPlanSala(int id)
        {
            List<ElementPlanu> dane = new List<ElementPlanu>();
            ElementPlanu[] zwracane = null;
            string oracleQuery = "SELECT id,rozpoczecie,koniec,sale_id,zjazdy_id,przydzialy_id FROM PlanZajec WHERE sale_id = :id_sala";
            try
            {
                int max = 0;
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("id_sala", id);
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["id"].ToString(), out int Id);
                    if (Id > max)
                    {
                        max = Id;
                    }
                    int.TryParse(wynik["rozpoczecie"].ToString(), out int Id_r);
                    int.TryParse(wynik["koniec"].ToString(), out int Id_z);
                    int.TryParse(wynik["sale_id"].ToString(), out int Id_s);
                    int.TryParse(wynik["zjazdy_id"].ToString(), out int Id_t);
                    int.TryParse(wynik["przydzialy_id"].ToString(), out int Id_p);
                    dane.Add(new ElementPlanu(Id, Id_r, Id_z, Id_s, Id_t, Id_p));
                }
                wynik.Close();
                zwracane = new ElementPlanu[max + 1];
                foreach (ElementPlanu item in dane)
                {
                    zwracane[item.Id] = item;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zwracane;
        }
        public int IloscGrup(string nazwa)
        {
            int ilosc = 0;
            string oracleQuery = "SELECT COUNT(id) as ilosc FROM grupy WHERE rok = :rocznik";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("rocznik", nazwa);
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    int.TryParse(wynik["ilosc"].ToString(), out ilosc);
                }
                wynik.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return ilosc;
        }
        public Dictionary<string, int> NazwyGrup(string nazwa)
        {
            Dictionary<string, int> zbior = new Dictionary<string, int>();
            string oracleQuery = "SELECT grupa FROM grupy WHERE rok = :rocznik";
            int licznik = 0;
            try
            {

                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("rocznik", nazwa);
                wynik = komenda.ExecuteReader();
                while (wynik.Read())
                {
                    zbior.Add(wynik["grupa"].ToString(), licznik);
                    licznik++;
                }
                wynik.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas pobierania danych: " + ex.Message);
            }
            return zbior;
        }
    }
}
