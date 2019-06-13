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
    class Deleting : Connect
    {
        public Deleting() : base()
        {
            try
            {
                transakcja = polaczenie.BeginTransaction(IsolationLevel.ReadCommitted);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład transakcji: " + ex.Message);
            }
        }
        public bool UsunTermin(int id)
        {
            bool wykonano = false;
            string oracleQuery = "DELETE FROM Zjazdy WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
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
                MessageBox.Show("Bład podczas usuwania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool UsunSale(int id)
        {
            bool wykonano = false;
            string oracleQuery = "DELETE FROM Sale WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
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
                MessageBox.Show("Bład podczas usuwania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool UsunPrzedmiot(int id)
        {
            bool wykonano = false;
            string oracleQuery = "DELETE FROM ProgramStudiow WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
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
                MessageBox.Show("Bład podczas usuwania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool UsunPracownika(int id)
        {
            bool wykonano = false;
            string oracleQuery = "DELETE FROM Pracownicy WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
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
                MessageBox.Show("Bład podczas usuwania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool UsunPrzydzial(int id)
        {
            bool wykonano = false;
            string oracleQuery = "DELETE FROM Przydzialy WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
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
                MessageBox.Show("Bład podczas usuwania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool UsunGrupe(int id)
        {
            bool wykonano = false;
            string oracleQuery = "DELETE FROM Grupy WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
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
                MessageBox.Show("Bład podczas usuwania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
        public bool UsunZPlanu(int id)
        {
            bool wykonano = false;
            string oracleQuery = "DELETE FROM PlanZajec WHERE id = :id";
            try
            {
                komenda = new OracleCommand(oracleQuery)
                {
                    Connection = polaczenie
                };
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
                MessageBox.Show("Bład podczas usuwania danych: " + ex.Message);
                transakcja.Rollback();
                wykonano = false;
            }
            return wykonano;
        }
    }
}
