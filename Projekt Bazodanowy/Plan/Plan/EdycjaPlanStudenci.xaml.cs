using System;
using System.Collections.Generic;
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
    /// Logika interakcji dla klasy EdycjaPlanStudenci.xaml
    /// </summary>
    public partial class EdycjaPlanStudenci : Window
    {
        static Sala[] sale = null;
        static Termin[] terminy = null;
        static Przydzial[] przydzialy = null;
        static Pracownik[] pracownicy = null;
        static Przedmiot[] przedmioty = null;
        static Student[] studenci = null;
        static Typ[] typy = null;
        static ElementPlanu[] plan = null;
        static Dictionary<string, int> zbior;
        static Selecting polaczenie = new Selecting();
        static int ID;
        static string StudenciNazwa;
        static int IloscGrup;
        public EdycjaPlanStudenci(string nazwa)
        {
            StudenciNazwa = nazwa;
            InitializeComponent();
            GetData();
            InitializeGrid();
            napis.Text += StudenciNazwa;
        }
        void GetData()
        {
            try
            {
                studenci = polaczenie.ListaStudentow();
                pracownicy = polaczenie.ListaPracownikow();
                sale = polaczenie.ListaSal();
                terminy = polaczenie.ListaTerminy();
                typy = polaczenie.ListaTypow();
                przydzialy = polaczenie.ListaPrzydzialow();
                przedmioty = polaczenie.ListaPrzedmiotow();
                plan = polaczenie.ListaPlanStudentow(StudenciNazwa);
                IloscGrup = polaczenie.IloscGrup(StudenciNazwa);
                zbior = polaczenie.NazwyGrup(StudenciNazwa);
                ComboZajecia.Items.Clear();
                ComboData.Items.Clear();
                ComboSala.Items.Clear();
                foreach (Przydzial item in polaczenie.ListaPrzydzialowStudentow(StudenciNazwa))
                {
                    if (item != null)
                    {
                        ComboZajecia.Items.Add(new ComboBoxItem(item.Id, przedmioty[item.Id_przedmiot].Nazwa + " - " +
                                                                                        typy[przedmioty[item.Id_przedmiot].Typ_id].Nazwa + " -> " +
                                                                                                studenci[item.Id_student].Grupa));
                    }
                }
                ComboZajecia.SelectedIndex = 0;
                foreach (Termin item in terminy)
                {
                    if (item != null)
                    {
                        ComboData.Items.Add(new ComboBoxItem(item.Id, item.Data));
                    }
                }
                ComboData.SelectedIndex = 0;
                foreach (Sala item in sale)
                {
                    if (item != null)
                    {
                        ComboSala.Items.Add(new ComboBoxItem(item.Id, item.Nazwa));
                    }
                }
                ComboSala.SelectedIndex = 0;
            }
            catch (Exception)
            {
                MessageBox.Show("Błąd podczas pobierania danych!");
            }
        }
        private void Walidacja(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }
        void InitializeGrid()
        {
            try
            {
                int i, j;
                Plan.Children.Clear();
                for (i = 0; i < 13; i++)
                {
                    RowDefinition wiersz = new RowDefinition();
                    wiersz.Height = GridLength.Auto;
                    Plan.RowDefinitions.Add(wiersz);
                }
                ColumnDefinition kolumna = new ColumnDefinition();
                kolumna.Width = GridLength.Auto;
                Plan.ColumnDefinitions.Add(kolumna);
                Plan.Children.Add((new TextBlockItem("Godzina || Data", 0, 0)).Element());
                for (i = 8, j = 1; i < 20; i++, j++)
                {
                    Plan.Children.Add((new TextBlockItem(i.ToString() + ".00 - " + (i + 1).ToString() + ".00", 0, j)).Element());
                }
                for (i = 0; i < IloscGrup; i++)
                {
                    ColumnDefinition kolumnaT = new ColumnDefinition();
                    kolumnaT.Width = GridLength.Auto;
                    Plan.ColumnDefinitions.Add(kolumnaT);
                }
                foreach (Termin termin in terminy)
                {
                    for (i = 0; i < IloscGrup; i++)
                    {
                        
                        ColumnDefinition kolumnaT = new ColumnDefinition();
                        kolumnaT.Width = GridLength.Auto;
                        Plan.ColumnDefinitions.Add(kolumnaT);
                    }
                    if (termin != null)
                    {
                        Border obramowanie = new Border();
                        obramowanie.BorderBrush = Brushes.Black;
                        obramowanie.BorderThickness = new Thickness(1);
                        Grid.SetColumn(obramowanie, IloscGrup * termin.Id);
                        Grid.SetRow(obramowanie, 1);
                        Grid.SetRowSpan(obramowanie, 13);
                        Grid.SetColumnSpan(obramowanie, IloscGrup);
                        Plan.Children.Add((new TextBlockItem(termin.ToString(), IloscGrup * termin.Id, 0, 1, IloscGrup)).Element());
                        Plan.Children.Add(obramowanie);
                    }
                }
                
                foreach (ElementPlanu element in plan)
                {
                    if (element != null)
                    {
                        Button przycisk = new Button
                        {
                            Content = przedmioty[przydzialy[element.Przydzial_id].Id_przedmiot].Nazwa + '\n' +
                                          typy[przedmioty[przydzialy[element.Przydzial_id].Id_przedmiot].Typ_id].Nazwa + '\n' +
                                            studenci[przydzialy[element.Przydzial_id].Id_student].Rok + " - " +
                                              studenci[przydzialy[element.Przydzial_id].Id_student].Grupa + '\n' +
                                                "(" + pracownicy[przydzialy[element.Przydzial_id].Id_pracownik] + " )" + '\n' +
                                                     "[" + sale[element.Sala_id].Nazwa + "]",
                            FontSize = 10,
                            Uid = element.Id.ToString(),
                            Margin = new Thickness(2)
                        };
                        Grid.SetColumn(przycisk, IloscGrup * element.Termin_id + zbior[studenci[przydzialy[element.Przydzial_id].Id_student].Grupa]);
                        Grid.SetRow(przycisk, element.Poczatek - 7);
                        Grid.SetRowSpan(przycisk, element.Koniec - element.Poczatek);
                        przycisk.Click += Wybrano;
                        Plan.Children.Add(przycisk);
                        /*Plan.Children.Add((new ButtonItem(
                            '"' + przedmioty[przydzialy[element.Przydzial_id].Id_przedmiot].Nazwa + '"' + '\n' +
                            studenci[przydzialy[element.Przydzial_id].Id_student].Rok + " - " +
                            studenci[przydzialy[element.Przydzial_id].Id_student].Grupa + '\n' +
                            "(" + sale[element.Sala_id].Nazwa + ")",
                                        element.Termin_id, element.Poczatek - 7, element.Koniec - element.Poczatek)).Element());*/
                    }
                }
            }
            catch
            {
                MessageBox.Show("Błąd startowy!");
            }
        }
        private void Wyczysc(object sender, RoutedEventArgs e)
        {
            Insert.IsEnabled = true;
            Update.IsEnabled = false;
            Delete.IsEnabled = false;
            Rozpoczecie.Text = "";
            Zakonczenie.Text = "";
            ComboSala.SelectedIndex = 0;
            ComboData.SelectedIndex = 0;
            ComboZajecia.SelectedIndex = 0;
            aktualny.Text = " ";
        }
        private void Wybrano(object sender, RoutedEventArgs e)
        {
            try
            {
                Button przycisk = sender as Button;
                int.TryParse(przycisk.Uid, out ID);
                Rozpoczecie.Text = plan[ID].Poczatek.ToString();
                Zakonczenie.Text = plan[ID].Koniec.ToString();
                foreach (ComboBoxItem item in ComboZajecia.Items)
                {
                    if (item.Value == przydzialy[plan[ID].Przydzial_id].Id)
                    {
                        ComboZajecia.SelectedValue = item;
                        break;
                    }
                }
                foreach (ComboBoxItem item in ComboSala.Items)
                {
                    if (item.Value == plan[ID].Sala_id)
                    {
                        ComboSala.SelectedValue = item;
                        break;
                    }
                }
                foreach (ComboBoxItem item in ComboData.Items)
                {
                    if (item.Value == plan[ID].Termin_id)
                    {
                        ComboData.SelectedValue = item;
                        break;
                    }
                }
                Insert.IsEnabled = false;
                Update.IsEnabled = true;
                Delete.IsEnabled = true;
                aktualny.Text = "Edycja: " + ComboData.SelectedValue + "(" + Rozpoczecie.Text + ".00-" + Zakonczenie.Text + ".00) : " +
                                    ComboZajecia.SelectedValue + " - " + ComboSala.SelectedValue;

            }
            catch
            {
                MessageBox.Show("Błąd pobierania informacji o elemencie!");
            }
        }
        private void Dodaj(object sender, RoutedEventArgs e)
        {
            try
            {
                if (Rozpoczecie.Text == "" || Zakonczenie.Text == "")
                {
                    MessageBox.Show("Wprowadź godzinę rozpoczęcia oraz zakończenia!");
                    return;
                }
                int.TryParse(Rozpoczecie.Text, out int start);
                int.TryParse(Zakonczenie.Text, out int koniec);
                if (start >= koniec)
                {
                    MessageBox.Show("Zajęcia muszą kończyć się później niż zaczynać!");
                    return;
                }
                Inserting dodawanie = new Inserting();
                if (dodawanie.DodawanieDoPlanu(start, koniec, ((ComboBoxItem)ComboSala.SelectedItem).Value,
                                             ((ComboBoxItem)ComboData.SelectedItem).Value,
                                             ((ComboBoxItem)ComboZajecia.SelectedItem).Value))
                {
                    MessageBox.Show("Pomyślnie dodano!");
                    GetData();
                    InitializeGrid();
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
                if (Rozpoczecie.Text == "" || Zakonczenie.Text == "")
                {
                    MessageBox.Show("Wprowadź godzinę rozpoczęcia oraz zakończenia!");
                    return;
                }
                int.TryParse(Rozpoczecie.Text, out int start);
                int.TryParse(Zakonczenie.Text, out int koniec);
                if (start >= koniec)
                {
                    MessageBox.Show("Zajęcia muszą kończyć się później niż zaczynać!");
                    return;
                }
                Updating zmienianie = new Updating();
                if (zmienianie.ZmienWPlanie(ID, start, koniec, ((ComboBoxItem)ComboSala.SelectedItem).Value,
                                             ((ComboBoxItem)ComboData.SelectedItem).Value,
                                             ((ComboBoxItem)ComboZajecia.SelectedItem).Value))
                {
                    MessageBox.Show("Pomyślnie zmieniono!");
                    GetData();
                    InitializeGrid();
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
                if (zmienianie.UsunZPlanu(ID))
                {
                    MessageBox.Show("Pomyślnie usunięto!");
                    GetData();
                    InitializeGrid();
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
    }
}

