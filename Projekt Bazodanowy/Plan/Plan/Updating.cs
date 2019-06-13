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
    class Updating : Connect
    {
        public Updating() : base()
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
        public bool ZmienTermin(int id, string data)
        {
            bool wykonano = false;
            string oracleQuery = "UPDATE Zjazdy SET dzien = :data WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("data", data);
                komenda.Parameters.Add("id", id);
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
                MessageBox.Show("Bład podczas zmieniania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool ZmienSale(int id, string nazwa)
        {
            bool wykonano = false;
            string oracleQuery = "UPDATE Sale SET nazwa = :nazwa WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("nazwa", nazwa);
                komenda.Parameters.Add("id", id);
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
                MessageBox.Show("Bład podczas zmieniania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool ZmienGrupe(int id, string rok, string grupa)
        {
            bool wykonano = false;
            string oracleQuery = "UPDATE Grupy SET rok = :rok , grupa = :grupa WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("rok", rok);
                komenda.Parameters.Add("grupa", grupa);
                komenda.Parameters.Add("id", id);
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
                MessageBox.Show("Bład podczas zmieniania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool ZmienPracownika(int id, string imie, string nazwisko, string tytul, int lokalny)
        {
            bool wykonano = false;
            string oracleQuery = "UPDATE Pracownicy SET imie = :imie , nazwisko = :nazwisko , tytul = :tytul , lokalny = :lokalny WHERE id = :id";
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
                komenda.Parameters.Add("id", id);
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
                MessageBox.Show("Bład podczas zmieniania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool ZmienPrzedmiot(int id, string nazwa, int ilosc, int typ)
        {
            bool wykonano = false;
            string oracleQuery = "UPDATE ProgramStudiow SET nazwa = :nazwa , ilosc_godzin = :ilosc , typ_id = :typ WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("nazwa", nazwa);
                komenda.Parameters.Add("ilosc", ilosc);
                komenda.Parameters.Add("typ", typ);
                komenda.Parameters.Add("id", id);
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
                MessageBox.Show("Bład podczas zmieniania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool ZmienPrzydzial(int id, int przedmiot, int pracownik, int grupa)
        {
            bool wykonano = false;
            string oracleQuery = "UPDATE Przydzialy SET programstudiow_id = :przedmiot , pracownicy_id = :pracownik , grupy_id = :grupa WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
                komenda.Parameters.Add("przedmiot", przedmiot);
                komenda.Parameters.Add("pracownik", pracownik);
                komenda.Parameters.Add("grupa", grupa);
                komenda.Parameters.Add("id", id);
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
                MessageBox.Show("Bład podczas zmieniania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool ZmienWPlanie(int id, int poczatek, int koniec, int sala, int termin, int przydzial)
        {
            bool wykonano = false;
            string oracleQuery = "UPDATE PlanZajec SET rozpoczecie = :poczatek , koniec = :koniec , " +
                                    "sale_id = :sala , zjazdy_id = :termin , przydzialy_id = :przydzial WHERE id = :id";
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
                komenda.Parameters.Add("id", id);
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
                MessageBox.Show("Bład podczas zmieniania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
    }
}
