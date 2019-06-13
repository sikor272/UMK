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

namespace Plan
{
    /// <summary>
    /// Logika interakcji dla klasy View.xaml
    /// </summary>
    public partial class View : Window
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
        static int IloscGrup;
        static Selecting polaczenie = new Selecting();
        public View()
        {
            GetData();
            InitializeComponent();
            InitializeComboBox();
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
            }
            catch (Exception)
            {
                MessageBox.Show("Błąd podczas pobierania danych!");
            }
        }
        void InitializeComboBox()
        {
            Rocznik.Items.Clear();
            Prowadzacy.Items.Clear();
            Sala.Items.Clear();
            foreach (Student student in studenci)
            {
                if(student != null)
                {
                    if (student.Grupa == "ALL")
                    {
                        Rocznik.Items.Add(student.ComboItem());
                    }
                }
            }
            Rocznik.SelectedIndex = 0;
            
            foreach (Pracownik pracownik in pracownicy)
            {
                if(pracownik != null)
                {
                    Prowadzacy.Items.Add(pracownik.ComboItem());
                }
            }
            Prowadzacy.SelectedIndex = 0;
            
            foreach (Sala miejsce in sale)
            {
                if(miejsce != null)
                {
                    Sala.Items.Add(miejsce.ComboItem());
                }
            }
            Sala.SelectedIndex = 0;
        }
        void InitializeGrid()
        {
            Plan.Children.Clear();
            for(int i = 0; i < 13; i++)
            {
                RowDefinition wiersz = new RowDefinition();
                wiersz.Height = GridLength.Auto;
                Plan.RowDefinitions.Add(wiersz);
            }
            ColumnDefinition kolumna = new ColumnDefinition();
            kolumna.Width = GridLength.Auto;
            Plan.ColumnDefinitions.Add(kolumna);
            Plan.Children.Add((new TextBlockItem("Godzina || Data",0,0)).Element());
            for(int i = 8, j = 1; i < 20; i++, j++)
            {
                Plan.Children.Add((new TextBlockItem(i.ToString() + ".00 - " + (i + 1).ToString() + ".00", 0, j)).Element());
            }
        }
        private void Powrot(object sender, RoutedEventArgs e)
        {
            MainWindow glowny = new MainWindow();
            Close();
            glowny.Show();
        }
        private void Nastepny(object sender, RoutedEventArgs e)
        {
            View pokaz = new View();
            pokaz.Show();
        }
        private void PlanRok(object sender, RoutedEventArgs e)
        {
            try
            {
                GetData();
                info.Text = "Plan: " + Rocznik.SelectedValue.ToString();
                //MessageBox.Show("Id " + ((ComboBoxItem)rocznik.SelectedItem).Value.ToString());
                InitializeGrid();
                int i, j;
                IloscGrup = polaczenie.IloscGrup(Rocznik.SelectedValue.ToString());
                zbior = polaczenie.NazwyGrup(Rocznik.SelectedValue.ToString());
                plan = polaczenie.ListaPlanStudentow(Rocznik.SelectedValue.ToString());
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
                        Plan.Children.Add(przycisk);
                    }
                }
            }
            catch(Exception)
            {
                MessageBox.Show("Nie wybrano rocznika!");
            }
        }
        private void PlanPracownik(object sender, RoutedEventArgs e)
        {
            try
            {
                GetData();
                info.Text = "Plan: " + Prowadzacy.SelectedItem.ToString();
                InitializeGrid();
                int i = 1;
                foreach (Termin termin in terminy)
                {
                    if(termin != null)
                    {
                        ColumnDefinition kolumna = new ColumnDefinition();
                        kolumna.Width = GridLength.Auto;
                        Plan.ColumnDefinitions.Add(kolumna);
                        Plan.Children.Add((new TextBlockItem(termin.ToString(), i, 0)).Element());
                        i++;
                    }
                }
                plan = polaczenie.ListaPlanPracownika(((ComboBoxItem)Prowadzacy.SelectedItem).Value);
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
                                                "[" + sale[element.Sala_id].Nazwa + "]",
                            FontSize = 10,
                            Uid = element.Id.ToString(),
                            Margin = new Thickness(2)
                        };
                        Grid.SetColumn(przycisk, element.Termin_id);
                        Grid.SetRow(przycisk, element.Poczatek - 7);
                        Grid.SetRowSpan(przycisk, element.Koniec - element.Poczatek);
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
            catch (Exception)
            {
                MessageBox.Show("Nie wybrano pracownika!");
            }
        }
        private void PlanSala(object sender, RoutedEventArgs e)
        {
            try
            {
                GetData();
                info.Text = "Plan: " + Sala.SelectedItem.ToString();
                //MessageBox.Show("Id "+ ((ComboBoxItem)sala.SelectedItem).Value.ToString());
                InitializeGrid();
                int i = 1;
                foreach (Termin termin in terminy)
                {
                    if (termin != null)
                    {
                        ColumnDefinition kolumna = new ColumnDefinition();
                        kolumna.Width = GridLength.Auto;
                        Plan.ColumnDefinitions.Add(kolumna);
                        Plan.Children.Add((new TextBlockItem(termin.ToString(), i, 0)).Element());
                        i++;
                    }
                }
                plan = polaczenie.ListaPlanSala(((ComboBoxItem)Sala.SelectedItem).Value);
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
                                                "(" + pracownicy[przydzialy[element.Przydzial_id].Id_pracownik] + ")",
                            FontSize = 10,
                            Uid = element.Id.ToString(),
                            Margin = new Thickness(2)
                        };
                        Grid.SetColumn(przycisk, element.Termin_id);
                        Grid.SetRow(przycisk, element.Poczatek - 7);
                        Grid.SetRowSpan(przycisk, element.Koniec - element.Poczatek);
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
            catch (Exception)
            {
                MessageBox.Show("Nie wybrano sali!");
            }
        }
    }
}
