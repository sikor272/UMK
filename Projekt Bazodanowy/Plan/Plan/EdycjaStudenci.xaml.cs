using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
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

namespace Plan
{
    /// <summary>
    /// Logika interakcji dla klasy EdycjaStudenci.xaml
    /// </summary>
    public partial class EdycjaStudenci : Window
    {
        public static int Id { get; set; }
        static Student[] studenci = null;
        static Selecting polaczenie = new Selecting();
        public EdycjaStudenci()
        {
            InitializeComponent();
            Initialize();
        }
        public void Initialize()
        {
            try
            {
                studenci = polaczenie.ListaStudentow();
                DataTable tabela = new DataTable();
                tabela.Columns.Add("Id", typeof(int));
                tabela.Columns.Add("Rocznik", typeof(string));
                tabela.Columns.Add("Grupa", typeof(string));
                foreach (DataColumn kolumna in tabela.Columns)
                {
                    kolumna.ReadOnly = true;
                }
                object[] wiersz = new object[3];
                foreach (Student dane in studenci)
                {
                    if(dane != null)
                    {
                        wiersz[0] = dane.Id;
                        wiersz[1] = dane.Rok;
                        wiersz[2] = dane.Grupa;
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
        private void Ukrywanie(object sender, DataGridAutoGeneratingColumnEventArgs e)
        {
            PropertyDescriptor propertyDescriptor = (PropertyDescriptor)e.PropertyDescriptor;
            e.Column.Header = propertyDescriptor.DisplayName;
            if (propertyDescriptor.DisplayName == "Id")
            {
                e.Cancel = true;
            }
        }
        private void Wyczysc(object sender, RoutedEventArgs e)
        {
            Insert.IsEnabled = true;
            Update.IsEnabled = false;
            Delete.IsEnabled = false;
            Rocznik.Text = "";
            Grupa.Text = "";
            napis.Text = "Edycja studentów";
        }

        private void Dodaj(object sender, RoutedEventArgs e)
        {
            if(Rocznik.Text == "" || Grupa.Text == "")
            {
                MessageBox.Show("Proszę wpisać rocznik oraz grupę!");
                return;
            }
            try
            {
                Inserting dodawanie = new Inserting();
                if (dodawanie.DodajGrupe(Rocznik.Text,Grupa.Text))
                {
                    MessageBox.Show("Pomyślnie dodano!");
                    Initialize();
                    Wyczysc(sender, e);
                }
                else
                {
                    MessageBox.Show("Błąd dodawania!");
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Błąd dodawania!");
            }
        }

        private void Zmien(object sender, RoutedEventArgs e)
        {
            if (Rocznik.Text == "" || Grupa.Text == "")
            {
                MessageBox.Show("Proszę wpisać rocznik oraz grupę!");
                return;
            }
            try
            {
                Updating zmienianie = new Updating();
                if (zmienianie.ZmienGrupe(Id,Rocznik.Text,Grupa.Text))
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
                if (zmienianie.UsunGrupe(Id))
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

        private void Wybrano(object sender, SelectionChangedEventArgs e)
        {
            DataGrid Tabela = sender as DataGrid;
            DataRowView wiersz = Tabela.SelectedItem as DataRowView;
            if (wiersz != null)
            {
                int.TryParse(wiersz["Id"].ToString(), out int id);
                Rocznik.Text = wiersz["Rocznik"].ToString();
                Grupa.Text = wiersz["Grupa"].ToString();
                Id = id;
                Insert.IsEnabled = false;
                Update.IsEnabled = true;
                Delete.IsEnabled = true;
                napis.Text = "Edycja: " + Rocznik.Text + " - " + Grupa.Text;

            }
        }
    }
}
