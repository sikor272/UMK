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
namespace Plan
{
    /// <summary>
    /// Logika interakcji dla klasy Admin.xaml
    /// </summary>
    public partial class Admin : Window
    {
        public Admin()
        {
            InitializeComponent();
            
        }
        private void Wyswietl(object sender, RoutedEventArgs e)
        {
            View pokaz = new View();
            pokaz.Show();
        }
        private void Wyloguj(object sender, RoutedEventArgs e)
        {
            MainWindow glowny = new MainWindow();
            glowny.Show();
            Close();
        }

        private void EdytujPrzydzialy(object sender, RoutedEventArgs e)
        {
            EdycjaPrzydzialy okno = new EdycjaPrzydzialy();
            okno.Show();
        }

        private void EdytujPlan(object sender, RoutedEventArgs e)
        {
            EdycjaWybor okno = new EdycjaWybor();
            okno.Show();
        }

        private void EdytujStudenci(object sender, RoutedEventArgs e)
        {
            EdycjaStudenci okno = new EdycjaStudenci();
            okno.Show();
        }

        private void EdytujPracownicy(object sender, RoutedEventArgs e)
        {
            EdycjaPracownicy okno = new EdycjaPracownicy();
            okno.Show();
        }

        private void EdytujSale(object sender, RoutedEventArgs e)
        {
            EdycjaSala okno = new EdycjaSala();
            okno.Show();
        }
        private void EdytujPrzedmioty(object sender, RoutedEventArgs e)
        {
            EdycjaPrzedmioty okno = new EdycjaPrzedmioty();
            okno.Show();
        }
        private void EdytujTerminy(object sender, RoutedEventArgs e)
        {
            EdycjaTermin okno = new EdycjaTermin();
            okno.Show();
        }
    }
}
