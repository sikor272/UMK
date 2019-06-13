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
    /// Logika interakcji dla klasy EdycjaPrzydzialy.xaml
    /// </summary>
    public partial class EdycjaPrzydzialy : Window
    {
        public static int Id { get; set; }
        static Przydzial[] przydzialy = null;
        static Pracownik[] pracownicy = null;
        static Przedmiot[] przedmioty = null;
        static Student[] studenci = null;
        static Typ[] typy = null;
        static Selecting polaczenie = new Selecting();
        public EdycjaPrzydzialy()
        {
            InitializeComponent();
            Initialize();
        }
        public void Initialize()
        {
            try
            {
                przydzialy = polaczenie.ListaPrzydzialow();
                pracownicy = polaczenie.ListaPracownikow();
                studenci = polaczenie.ListaStudentow();
                przedmioty = polaczenie.ListaPrzedmiotow();
                typy = polaczenie.ListaTypow();
                DataTable tabela = new DataTable();
                tabela.Columns.Add("Id", typeof(int));
                tabela.Columns.Add("Idprzedmiot", typeof(int));
                tabela.Columns.Add("Idprowadzacy", typeof(int));
                tabela.Columns.Add("Idgrupy", typeof(int));
                tabela.Columns.Add("Przedmiot", typeof(string));
                tabela.Columns.Add("Typ", typeof(string));
                tabela.Columns.Add("Prowadzacy", typeof(string));
                tabela.Columns.Add("Rocznik", typeof(string));
                tabela.Columns.Add("Grupa", typeof(string));
                foreach (DataColumn kolumna in tabela.Columns)
                {
                    kolumna.ReadOnly = true;
                }
                object[] wiersz = new object[9];
                foreach (Przydzial przydzial in przydzialy)
                {
                    if(przydzial != null)
                    {
                        wiersz[0] = przydzial.Id;
                        wiersz[1] = przydzial.Id_przedmiot;
                        wiersz[2] = przydzial.Id_pracownik;
                        wiersz[3] = przydzial.Id_student;
                        wiersz[4] = przedmioty[przydzial.Id_przedmiot].Nazwa;
                        wiersz[5] = typy[przedmioty[przydzial.Id_przedmiot].Typ_id].Nazwa;
                        wiersz[6] = pracownicy[przydzial.Id_pracownik].ToString();
                        wiersz[7] = studenci[przydzial.Id_student].Rok;
                        wiersz[8] = studenci[przydzial.Id_student].Grupa;
                        tabela.Rows.Add(wiersz);
                    }
                }
                Dane.ItemsSource = tabela.DefaultView;

                Przedmioty.Items.Clear();
                Prowadzacy.Items.Clear();
                Studenci.Items.Clear();
                foreach (Przedmiot przedmiot in przedmioty)
                {
                    if(przedmiot != null)
                    {
                        Przedmioty.Items.Add(new ComboBoxItem(przedmiot.Id, przedmiot.Nazwa + " - " + typy[przedmiot.Typ_id].Nazwa + " : " + przedmiot.Ilosc));
                    }
                }
                Przedmioty.SelectedIndex = 0;

                foreach (Pracownik pracownik in pracownicy)
                {
                    if(pracownik != null)
                    {
                        Prowadzacy.Items.Add(pracownik.ComboItem());
                    }
                }
                Prowadzacy.SelectedIndex = 0;

                foreach (Student student in studenci)
                {
                    if(student != null)
                    {
                        Studenci.Items.Add(student.ComboItemAll());
                    }
                }
                Studenci.SelectedIndex = 0;
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
            if (propertyDescriptor.DisplayName == "Id" || propertyDescriptor.DisplayName == "Idprzedmiot" ||
                propertyDescriptor.DisplayName == "Idprowadzacy" || propertyDescriptor.DisplayName == "Idgrupy")
            {
                e.Cancel = true;
            }
        }
        private void Wyczysc(object sender, RoutedEventArgs e)
        {
            Insert.IsEnabled = true;
            Update.IsEnabled = false;
            Delete.IsEnabled = false;
            Prowadzacy.SelectedIndex = 0;
            Studenci.SelectedIndex = 0;
            Przedmioty.SelectedIndex = 0;
            napis.Text = "Edycja przydziałów";
        }

        private void Dodaj(object sender, RoutedEventArgs e)
        {
            try
            {
                Inserting dodawanie = new Inserting();
                if (dodawanie.DodajPrzydzial(((ComboBoxItem)Przedmioty.SelectedItem).Value,
                                             ((ComboBoxItem)Prowadzacy.SelectedItem).Value,
                                             ((ComboBoxItem)Studenci.SelectedItem).Value))
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
            try
            {
                Updating zmienianie = new Updating();
                if (zmienianie.ZmienPrzydzial(Id, ((ComboBoxItem)Przedmioty.SelectedItem).Value,
                                                    ((ComboBoxItem)Prowadzacy.SelectedItem).Value,
                                                    ((ComboBoxItem)Studenci.SelectedItem).Value))
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
                if (zmienianie.UsunPrzydzial(Id))
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
                int.TryParse(wiersz["Idprowadzacy"].ToString(), out int idprowadzacy);
                int.TryParse(wiersz["Idprzedmiot"].ToString(), out int idprzedmiot);
                int.TryParse(wiersz["Idgrupy"].ToString(), out int idgrupy);
                foreach (ComboBoxItem item in Prowadzacy.Items)
                {
                    if (item.Value == idprowadzacy)
                    {
                        Prowadzacy.SelectedValue = item;
                        break;
                    }
                }
                foreach (ComboBoxItem item in Studenci.Items)
                {
                    if (item.Value == idgrupy)
                    {
                        Studenci.SelectedValue = item;
                        break;
                    }
                }
                foreach (ComboBoxItem item in Przedmioty.Items)
                {
                    if (item.Value == idprzedmiot)
                    {
                        Przedmioty.SelectedValue = item;
                        break;
                    }
                }
                Id = id;
                Insert.IsEnabled = false;
                Update.IsEnabled = true;
                Delete.IsEnabled = true;
                napis.Text = "Edycja: " + Przedmioty.SelectedValue + " - " + Prowadzacy.SelectedValue + " : " + Studenci.SelectedValue;
            }
        }
    }
}
