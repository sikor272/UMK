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
    /// Logika interakcji dla klasy EdycjaWybor.xaml
    /// </summary>
    public partial class EdycjaWybor : Window
    {
        static Pracownik[] pracownicy = null;
        static Student[] studenci = null;
        static Selecting polaczenie = new Selecting();
        public EdycjaWybor()
        {
            InitializeComponent();
            GetData();
            InitializeComboBox();
        }
        void GetData()
        {
            try
            {
                studenci = polaczenie.ListaStudentow();
                pracownicy = polaczenie.ListaPracownikow();
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
            foreach (Student student in studenci)
            {
                if (student != null)
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
                if (pracownik != null)
                {
                    Prowadzacy.Items.Add(pracownik.ComboItem());
                }
            }
            Prowadzacy.SelectedIndex = 0;

        }
        private void EdycjaRok(object sender, RoutedEventArgs e)
        {
            try
            {
                //MessageBox.Show("Id "+ ((ComboBoxItem)prowadzacy.SelectedItem).Value.ToString());
                EdycjaPlanStudenci okno = new EdycjaPlanStudenci(Rocznik.SelectedValue.ToString());
                okno.Show();
            }
            catch (Exception)
            {
                MessageBox.Show("Nie wybrano studenta!");
            }
        }

        private void EdycjaPracownik(object sender, RoutedEventArgs e)
        {
            try
            {
                int.TryParse(((ComboBoxItem)Prowadzacy.SelectedItem).Value.ToString(), out int ID);
                EdycjaPlanPracownik okno = new EdycjaPlanPracownik(ID, Prowadzacy.SelectedValue.ToString());
                okno.Show();

            }
            catch (Exception)
            {
                MessageBox.Show("Nie wybrano pracownika!");
            }
        }
    }
}
