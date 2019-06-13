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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Plan
{
    /// <summary>
    /// Logika interakcji dla klasy MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        private void Zaloguj(object sender, RoutedEventArgs e)
        {
            string login = Login.Text.ToString();
            string haslo = Passwd.Password.ToString();

            if (login == "Admin" && haslo == "Admin")
            {
                Admin panel = new Admin();
                Close();
                panel.Show();
            }
            else
            if (login == "" || haslo == "")
            {
                MessageBox.Show("Wpisz login/haslo!");
            }
            else
            {
                MessageBox.Show("Niepoprawne dane!");
            }
        }
        private void Wyswietl(object sender, RoutedEventArgs e)
        {
            View pokaz = new View();
            Close();
            pokaz.Show();
        }

        private void Passwd_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                Zaloguj(sender, e);
            }
        }
    }
}
