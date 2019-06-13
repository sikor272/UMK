using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Data;
using System.ComponentModel;

namespace Plan
{
    /// <summary>
    /// Logika interakcji dla klasy EdycjaTermin.xaml
    /// </summary>
    public partial class EdycjaTermin : Window
    {
        public static int Id { get; set; }
        static Termin[] terminy = null;
        static Selecting polaczenie = new Selecting();
        public EdycjaTermin()
        {
            InitializeComponent();
            Initialize();
        }
        public void Initialize()
        {
            try
            {
                terminy = polaczenie.ListaTerminy();
                DataTable tabela = new DataTable();
                tabela.Columns.Add("Id", typeof(int));
                tabela.Columns.Add("Data", typeof(string));
                foreach(DataColumn kolumna in tabela.Columns)
                {
                    kolumna.ReadOnly = true;
                }
                object[] wiersz = new object[2];
                foreach(Termin dane in terminy)
                {
                    if(dane != null)
                    {
                        wiersz[0] = dane.Id;
                        wiersz[1] = dane.Data;
                        tabela.Rows.Add(wiersz);
                    }
                }
                Dane.ItemsSource = tabela.DefaultView;
            }
            catch (Exception)
            {
                MessageBox.Show("Błąd startowy!");
            }
        }

        private void Wyczysc(object sender, RoutedEventArgs e)
        {
            Insert.IsEnabled = true;
            Update.IsEnabled = false;
            Delete.IsEnabled = false;
            Data.SelectedDate = null;
            napis.Text = "Edycja terminów";
        }

        private void Dodaj(object sender, RoutedEventArgs e)
        {
            if(Data.SelectedDate == null)
            {
                MessageBox.Show("Proszę wybrać datę!");
                return;
            }
            try
            {
                Inserting dodawanie = new Inserting();
                string data = Data.ToString();
                string day = data.Remove(2);
                string month = data.Remove(0, 3).Remove(2);
                string year = data.Remove(0, 6).Remove(4);
                if(dodawanie.DodajTermin(year + "-" + month + "-" + day))
                {
                    MessageBox.Show("Pomyślnie dodano!");
                    Initialize();
                    Wyczysc(sender,e);
                } else
                {
                    MessageBox.Show("Błąd dodawania!");
                }
            }
            catch(Exception)
            {
                MessageBox.Show("Błąd dodawania!");
            }
        }

        private void Zmien(object sender, RoutedEventArgs e)
        {
            if (Data.SelectedDate == null)
            {
                MessageBox.Show("Proszę wybrać datę!");
                return;
            }
            try
            {
                Updating zmienianie = new Updating();
                string data = Data.ToString();
                string day = data.Remove(2);
                string month = data.Remove(0, 3).Remove(2);
                string year = data.Remove(0, 6).Remove(4);
                if(zmienianie.ZmienTermin(Id, year + "-" + month + "-" + day))
                {
                    MessageBox.Show("Pomyślnie zmieniono!");
                    Initialize();
                    Wyczysc(sender, e);
                }
                else
                {
                    MessageBox.Show("Błąd zmiany!");
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Błąd zmiany!");
            }
        }

        private void Usun(object sender, RoutedEventArgs e)
        {
            try
            {
                Deleting zmienianie = new Deleting();
                if(zmienianie.UsunTermin(Id))
                {
                    MessageBox.Show("Pomyślnie usunięto!");
                    Initialize();
                    Wyczysc(sender, e);
                }
                else
                {
                    MessageBox.Show("Błąd usuwania!");
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Błąd usuwania!");
            }
        }
        private void Ukrywanie(object sender, DataGridAutoGeneratingColumnEventArgs e)
        {
            PropertyDescriptor propertyDescriptor = (PropertyDescriptor)e.PropertyDescriptor;
            e.Column.Header = propertyDescriptor.DisplayName;
            if (propertyDescriptor.DisplayName == "Id")
            {
                e.Cancel = true;
            }
        }
        private void Wybrano(object sender, SelectionChangedEventArgs e)
        {
            DataGrid Tabela = sender as DataGrid;
            DataRowView wiersz = Tabela.SelectedItem as DataRowView;
            if(wiersz != null)
            {
                int.TryParse(wiersz["Id"].ToString(), out int id);
                Id = id;
                string data = wiersz["Data"].ToString();
                try
                {
                    int.TryParse(data.Remove(2), out int day);
                    int.TryParse(data.Remove(0, 3).Remove(2), out int month);
                    int.TryParse(data.Remove(0, 6), out int year);
                    Data.SelectedDate = new DateTime(year, month, day);
                    Insert.IsEnabled = false;
                    Update.IsEnabled = true;
                    Delete.IsEnabled = true;
                    napis.Text = "Edycja: " + data;
                }
                catch
                {
                    MessageBox.Show("Błąd podczas odczytu!");
                }
            }
        }
    }
}
