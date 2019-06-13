using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Figura
{
    class Figura
    {
        private double pole;
        private double obwod;
        private double wymiar;
        private string nazwa;
        private static int Licznik = 0;
        public string Nazwa
        {
            get;
            protected set;
        }
        public void UstawLicznik(int licznik)
        {
            Licznik = licznik;
        }
        static public void UstawLicznikStatycznie(int licznik)
        {
            Licznik = licznik;
        }
        public int WypiszLicznik()
        {
            return Licznik;
        }
        static public int WypiszLicznikStatycznie()
        {
            return Licznik;
        }
        public Figura(string nazwa)
        {
            Nazwa = nazwa;
        }
        public double Obwod
        {
            get
            {
                return obwod;
            }
            set
            {
                obwod = value;
            }
        }
        public double Pole
        {
            get
            {
                return pole;
            }
            set
            {
                if(pole >= 0)
                {
                    pole = value;
                }
            }
        }
        /*public void Ustaw(double pole, double obwod)
        {
            this.pole = pole;
            this.obwod = obwod;
        }*/
        /*public void Ustaw(string nazwa)
        {
            this.nazwa = nazwa;
        }*/
        public override string ToString()
        {
            return "Figura " + Nazwa + " o obwodzie " + Obwod + " i polu " + Pole;
        }
    }
}
