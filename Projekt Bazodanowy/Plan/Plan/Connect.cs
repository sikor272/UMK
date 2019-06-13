using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Oracle.DataAccess.Client;

namespace Plan
{
    class Connect
    {

        protected string connectionString = "Data Source=(DESCRIPTION="
                + "(ADDRESS=(PROTOCOL=TCP)(HOST=localhost)(PORT=1521))"
                + "(CONNECT_DATA=(SID=xe)));"
                + "User Id=" + User.Id + ";Password=" + User.Password + ";";
        protected OracleConnection polaczenie;
        protected OracleCommand komenda;
        protected OracleDataReader wynik;
        protected OracleTransaction transakcja;
        public Connect()
        {
            polaczenie = new OracleConnection(connectionString);
            try
            {
                polaczenie.Open();
            }
            catch(Exception ex)
            {
                MessageBox.Show("Bład podczas łączenia: " + ex.Message);
            }
        }
        ~Connect()
        {
            try
            {
                polaczenie.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Bład podczas rozłaczenia: " + ex.Message);
            }
        }
    }
}
