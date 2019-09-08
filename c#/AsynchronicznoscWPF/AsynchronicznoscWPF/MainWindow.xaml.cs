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
using System.Threading;

namespace AsynchronicznoscWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        public void Pracuj()
        {
            Thread.Sleep(3000);
        }
        public void Uaktualnij()
        {
            Etykieta.Text = DateTime.Now.ToString("HH:mm:ss");
        }
        public void PracujOrazUaktualnij()
        {
            Pracuj();
            Uaktualnij();
        }

        private void ButSynchr_Click(object sender, RoutedEventArgs e)
        {
            PracujOrazUaktualnij();
        }

        private void ButNowyWatek_Click(object sender, RoutedEventArgs e)
        {
            Thread watek = new Thread(PracujOrazUaktualnij);
            //Thread watek = new Thread(() => {
            //    Pracuj();
            //    Uaktualnij();
            //});
            watek.Start();
        }

        private void ButMessageBox_Click(object sender, RoutedEventArgs e)
        {
            Thread watek = new Thread(()=> {
                Pracuj();
                MessageBox.Show("ukończono pracę o " 
                    + DateTime.Now.ToString("HH:mm:ss"));
            });
            watek.Start();
        }

        private void ButDispAll_Click(object sender, RoutedEventArgs e)
        {
            Thread watek = new Thread(() =>
            {
                this.Dispatcher.BeginInvoke(new ThreadStart(
                    () => { PracujOrazUaktualnij(); }));
            });
            watek.Start();
        }

        private void ButDispUpdate_Click(object sender, RoutedEventArgs e)
        {
            Thread watek = new Thread(() =>
            {
                Pracuj();
                this.Dispatcher.BeginInvoke(new ThreadStart(
                    () => { Uaktualnij(); }));
            });
            watek.Start();
        }
        public string PracujOrazZwrocWynik()
        {
            Pracuj();
            return DateTime.Now.ToString("HH:mm:ss");
        }

        async private void ButAsync_Click(object sender, RoutedEventArgs e)
        {
            Etykieta.Text = await Task<string>.Factory.StartNew(
                PracujOrazZwrocWynik);
        }
    }
}
