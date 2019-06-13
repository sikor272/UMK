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
    /// Logika interakcji dla klasy EdycjaPrzedmioty.xaml
    /// </summary>
    public partial class EdycjaPrzedmioty : Window
    {
        public static int Id { get; set; }
        static Przedmiot[] przedmioty = null;
        static Typ[] typy = null;
        static Selecting polaczenie = new Selecting();
        public EdycjaPrzedmioty()
        {
            InitializeComponent();
            Initialize();
        }
        private void Walidacja(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }
        
        public void Initialize()
        {
            try
            {
                przedmioty = polaczenie.ListaPrzedmiotow();
                typy = polaczenie.ListaTypow();
                DataTable tabela = new DataTable();
                tabela.Columns.Add("Id", typeof(int));
                tabela.Columns.Add("Nazwa", typeof(string));
                tabela.Columns.Add("Ilość godzin", typeof(string));
                tabela.Columns.Add("Typ_id", typeof(int));
                tabela.Columns.Add("Typ", typeof(string));
                foreach (DataColumn kolumna in tabela.Columns)
                {
                    kolumna.ReadOnly = true;
                }
                object[] wiersz = new object[5];
                foreach (Przedmiot przedmiot in przedmioty)
                {
                    if(przedmiot != null)
                    {
                        wiersz[0] = przedmiot.Id;
                        wiersz[1] = przedmiot.Nazwa;
                        wiersz[2] = przedmiot.Ilosc;
                        wiersz[3] = przedmiot.Typ_id;
                        wiersz[4] = typy[przedmiot.Typ_id];
                        tabela.Rows.Add(wiersz);
                    }
                }
                Dane.ItemsSource = tabela.DefaultView;
                ComboTyp.Items.Clear();
                foreach (Typ typ in typy)
                {
                    if(typ != null)
                    {
                        ComboTyp.Items.Add(typ.ComboItem());
                    }
                }
                ComboTyp.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Błąd startowy!" + ex.Message);
            }
        }
        private void Ukrywanie(object sender, DataGridAutoGeneratingColumnEventArgs e)
        {
            PropertyDescriptor propertyDescriptor = (PropertyDescriptor)e.PropertyDescriptor;
            e.Column.Header = propertyDescriptor.DisplayName;
            if (propertyDescriptor.DisplayName == "Id" || propertyDescriptor.DisplayName == "Typ_id")
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
            Ilosc.Text = "";
            ComboTyp.SelectedIndex = 0;
            napis.Text = "Edycja przedmiotów";
            Id = -1;
        }

        private void Dodaj(object sender, RoutedEventArgs e)
        {
            
            if (Nazwa.Text == "" || Ilosc.Text == "")
            {
                MessageBox.Show("Proszę wpisać nazwę oraz ilość godzin!");
                return;
            }
            try
            {
                int.TryParse(Ilosc.Text, out int ile);
                Inserting dodawanie = new Inserting();
                if (dodawanie.DodajPrzedmiot(Nazwa.Text,ile, ((ComboBoxItem)ComboTyp.SelectedItem).Value))
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
            if (Nazwa.Text == "" || Ilosc.Text == "")
            {
                MessageBox.Show("Proszę wpisać nazwę oraz ilość godzin!");
                return;
            }
            try
            {
                int.TryParse(Ilosc.Text, out int ile);
                Updating zmienianie = new Updating();
                if (zmienianie.ZmienPrzedmiot(Id, Nazwa.Text, ile, ((ComboBoxItem)ComboTyp.SelectedItem).Value))
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
                if (zmienianie.UsunPrzedmiot(Id))
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
                int.TryParse(wiersz["Typ_id"].ToString(), out int typ_id);
                Nazwa.Text = wiersz["Nazwa"].ToString();
                Ilosc.Text = wiersz["Ilość godzin"].ToString();
                foreach(ComboBoxItem item in ComboTyp.Items)
                {
                    if(item.ToString() == (new ComboBoxItem(typ_id, wiersz["Typ"].ToString()).ToString()))
                    {
                        ComboTyp.SelectedValue = item;
                        break;
                    }
                }
                Id = id;
                Insert.IsEnabled = false;
                Update.IsEnabled = true;
                Delete.IsEnabled = true;
                napis.Text = "Edycja: " + Nazwa.Text + " - " + ComboTyp.SelectedValue + " : " + Ilosc.Text + " godzin";

            }
        }
    }
}
