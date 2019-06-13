using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
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
    /// Logika interakcji dla klasy EdycjaPracownicy.xaml
    /// </summary>
    public partial class EdycjaPracownicy : Window
    {
        public static int Id { get; set; }
        static Pracownik[] pracownicy = null;
        static Selecting polaczenie = new Selecting();
        public EdycjaPracownicy()
        {
            InitializeComponent();
            Initialize();
        }
        public void Initialize()
        {
            try
            {
                pracownicy = polaczenie.ListaPracownikow();
                DataTable tabela = new DataTable();
                tabela.Columns.Add("Id", typeof(int));
                tabela.Columns.Add("Imie", typeof(string));
                tabela.Columns.Add("Nazwisko", typeof(string));
                tabela.Columns.Add("Tytuł", typeof(string));
                tabela.Columns.Add("Lokalny", typeof(string));
                foreach (DataColumn kolumna in tabela.Columns)
                {
                    kolumna.ReadOnly = true;
                }
                object[] wiersz = new object[5];
                foreach (Pracownik dane in pracownicy)
                {
                    if(dane != null)
                    {
                        wiersz[0] = dane.Id;
                        wiersz[1] = dane.Imie;
                        wiersz[2] = dane.Nazwisko;
                        wiersz[3] = dane.Tytul;
                        wiersz[4] = dane.Lokalny == 1 ? "Tak" : "Nie";
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
            Imie.Text = "";
            Nazwisko.Text = "";
            Tytul.Text = "";
            Lokalny.IsChecked = false;
            napis.Text = "Edycja pracowników";
            Id = -1;
        }

        private void Dodaj(object sender, RoutedEventArgs e)
        {
            if (Imie.Text == "" || Nazwisko.Text == "" || Tytul.Text == "")
            {
                MessageBox.Show("Proszę wpisać imie, nazwisko oraz tytuł!");
                return;
            }
            try
            {
                Inserting dodawanie = new Inserting();
                Regex regex = new Regex(@"^(([A-ZŁŻ][a-ząęóżźćńłś]{1,})(-[A-ZŁŻ][a-ząęóżźćńłś]{1,})?)$");
                if (!regex.IsMatch(Nazwisko.Text))
                {
                    MessageBox.Show("Nazwisko nie poprawne!");
                    return;
                }
                if (dodawanie.DodajPracownika(Imie.Text, Nazwisko.Text, Tytul.Text, Lokalny.IsChecked == true ? 1 : 0))
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
            if (Imie.Text == "" || Nazwisko.Text == "" || Tytul.Text == "")
            {
                MessageBox.Show("Proszę wpisać imie, nazwisko oraz tytuł!");
                return;
            }
            try
            {
                Updating zmienianie = new Updating();
                if (zmienianie.ZmienPracownika(Id, Imie.Text, Nazwisko.Text, Tytul.Text, Lokalny.IsChecked == true ? 1 : 0))
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
                if (zmienianie.UsunPracownika(Id))
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
            if (wiersz != null)
            {
                int.TryParse(wiersz["Id"].ToString(), out int id);
                Imie.Text = wiersz["Imie"].ToString();
                Nazwisko.Text = wiersz["Nazwisko"].ToString();
                Tytul.Text = wiersz["Tytuł"].ToString();
                Lokalny.IsChecked = wiersz["Lokalny"].ToString() == "Tak" ? true : false;
                Id = id;
                Insert.IsEnabled = false;
                Update.IsEnabled = true;
                Delete.IsEnabled = true;
                napis.Text = "Edycja: " + Tytul.Text + " " + Imie.Text + " " + Nazwisko.Text;

            }
        }
    }
}
