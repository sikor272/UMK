using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Porownywarka
{
    public abstract class Pojazd
    {
        protected int miejsca, kola;
        protected double cena, waga;

        public double Cena { get { return cena; } }
        public double Waga { get { return waga; } }

        public void UstawIloscMiejsc(int ilosc)
        {
            miejsca = ilosc;
        }
        public void UstawIloscKol(int ilosc)
        {
            kola = ilosc;
        }
        public void UstawCene(double cena)
        {
            this.cena = cena;
        }
        public void UstawWage(double waga)
        {
            this.waga = waga;
        }

        public abstract bool CzyWieloslad();
        public abstract bool CzyMaDach();
        public abstract bool CzyUtonie();

        public override string ToString()
        {
            return this.GetType().Name + ": " + cena.ToString() + " zł, "
                 + waga.ToString() + " kg";
        }
    }
}
