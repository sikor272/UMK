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
    /// Logika interakcji dla klasy EdycjaSala.xaml
    /// </summary>
    public partial class EdycjaSala : Window
    {
        public static int Id { get; set; }
        static Sala[] sale = null;
        static Selecting polaczenie = new Selecting();
        public EdycjaSala()
        {
            InitializeComponent();
            Initialize();
        }
        public void Initialize()
        {
            try
            {
                sale = polaczenie.ListaSal();
                DataTable tabela = new DataTable();
                tabela.Columns.Add("Id", typeof(int));
                tabela.Columns.Add("Nazwa", typeof(string));
                foreach (DataColumn kolumna in tabela.Columns)
                {
                    kolumna.ReadOnly = true;
                }
                object[] wiersz = new object[2];
                foreach (Sala dane in sale)
                {
                    if(dane != null)
                    {
                        wiersz[0] = dane.Id;
                        wiersz[1] = dane.Nazwa;
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
            Nazwa.Text = "";
            napis.Text = "Edycja sal";
        }

        private void Dodaj(object sender, RoutedEventArgs e)
        {
            if (Nazwa.Text == "")
            {
                MessageBox.Show("Proszę wpisać nazwę!");
                return;
            }
            try
            {
                Inserting dodawanie = new Inserting();
                if (dodawanie.DodajSale(Nazwa.Text))
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
            if (Nazwa.Text == "")
            {
                MessageBox.Show("Proszę wpisać nazwę!");
                return;
            }
            try
            {
                Updating zmienianie = new Updating();
                if (zmienianie.ZmienSale(Id, Nazwa.Text))
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
                if (zmienianie.UsunSale(Id))
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
                Nazwa.Text = wiersz["Nazwa"].ToString();
                Id = id;
                Insert.IsEnabled = false;
                Update.IsEnabled = true;
                Delete.IsEnabled = true;
                napis.Text = "Edycja: " + Nazwa.Text;
                
            }
        }
    }
}