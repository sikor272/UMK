using Oracle.DataAccess.Client;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Plan
{
    class Inserting : Connect
    {
        public Inserting() : base()
        {
            try
            {
                transakcja = polaczenie.BeginTransaction(IsolationLevel.ReadCommitted);
            }
            catch(Exception ex)
            {
                MessageBox.Show("Bład transakcji: "+ ex.Message);
            }
        }
        public bool DodajTermin(string data)
        {
            bool wykonano = false;
            string oracleQuery = "INSERT INTO Zjazdy (dzien) VALUES(:data)";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("data", data);
                komenda.CommandType = CommandType.Text;
                komenda.Transaction = transakcja;
                int wiersze = komenda.ExecuteNonQuery();
                transakcja.Commit();
                if (wiersze > 0)
                {
                    wykonano = true;
                }
                else
                {
                    wykonano = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas dodawania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool DodajSale(string nazwa)
        {
            bool wykonano = false;
            string oracleQuery = "INSERT INTO Sale (nazwa) VALUES(:nazwa)";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("nazwa", nazwa);
                komenda.CommandType = CommandType.Text;
                komenda.Transaction = transakcja;
                int wiersze = komenda.ExecuteNonQuery();
                transakcja.Commit();
                if (wiersze > 0)
                {
                    wykonano = true;
                }
                else
                {
                    wykonano = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas dodawania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool DodajGrupe(string rok, string grupa)
        {
            bool wykonano = false;
            string oracleQuery = "INSERT INTO Grupy (rok,grupa) VALUES(:rok,:grupa)";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("rok", rok);
                komenda.Parameters.Add("grupa", grupa);
                komenda.CommandType = CommandType.Text;
                komenda.Transaction = transakcja;
                int wiersze = komenda.ExecuteNonQuery();
                transakcja.Commit();
                if (wiersze > 0)
                {
                    wykonano = true;
                }
                else
                {
                    wykonano = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas dodawania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool DodajPracownika(string imie, string nazwisko, string tytul, int lokalny)
        {
            bool wykonano = false;
            string oracleQuery = "INSERT INTO Pracownicy (imie,nazwisko,tytul,lokalny) VALUES (:imie,:nazwisko,:tytul,:lokalny)";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("imie", imie);
                komenda.Parameters.Add("nazwisko", nazwisko);
                komenda.Parameters.Add("tytul", tytul);
                komenda.Parameters.Add("lokalny", lokalny);
                komenda.CommandType = CommandType.Text;
                komenda.Transaction = transakcja;
                int wiersze = komenda.ExecuteNonQuery();
                transakcja.Commit();
                if (wiersze > 0)
                {
                    wykonano = true;
                }
                else
                {
                    wykonano = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas dodawania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool DodajPrzedmiot(string nazwa, int ilosc, int typ)
        {
            bool wykonano = false;
            string oracleQuery = "INSERT INTO ProgramStudiow(Nazwa,Ilosc_godzin,Typ_id) VALUES (:nazwa,:ilosc,:typ)";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("nazwa", nazwa);
                komenda.Parameters.Add("ilosc", ilosc);
                komenda.Parameters.Add("typ", typ);
                komenda.CommandType = CommandType.Text;
                komenda.Transaction = transakcja;
                int wiersze = komenda.ExecuteNonQuery();
                transakcja.Commit();
                if (wiersze > 0)
                {
                    wykonano = true;
                }
                else
                {
                    wykonano = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas dodawania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool DodajPrzydzial(int przedmiot, int pracownik, int grupa)
        {
            bool wykonano = false;
            string oracleQuery = "INSERT INTO Przydzialy (PROGRAMSTUDIOW_ID, PRACOWNICY_ID, GRUPY_ID) VALUES (:przedmiot, :pracownik, :grupa)";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("przedmiot", przedmiot);
                komenda.Parameters.Add("pracownik", pracownik);
                komenda.Parameters.Add("grupa", grupa);
                komenda.CommandType = CommandType.Text;
                komenda.Transaction = transakcja;
                int wiersze = komenda.ExecuteNonQuery();
                transakcja.Commit();
                if (wiersze > 0)
                {
                    wykonano = true;
                }
                else
                {
                    wykonano = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas dodawania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool DodawanieDoPlanu(int poczatek, int koniec, int sala, int termin, int przydzial)
        {
            bool wykonano = false;
            string oracleQuery = "INSERT INTO PlanZajec (ROZPOCZECIE, KONIEC, SALE_ID, ZJAZDY_ID, PRZYDZIALY_ID) " +
                                    "VALUES (:poczatek, :koniec, :sala, :termin, :przydzial)";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("poczatek", poczatek);
                komenda.Parameters.Add("koniec", koniec);
                komenda.Parameters.Add("sala", sala);
                komenda.Parameters.Add("termin", termin);
                komenda.Parameters.Add("przydzial", przydzial);
                komenda.CommandType = CommandType.Text;
                komenda.Transaction = transakcja;
                int wiersze = komenda.ExecuteNonQuery();
                transakcja.Commit();
                if (wiersze > 0)
                {
                    wykonano = true;
                }
                else
                {
                    wykonano = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas dodawania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
    }
}
