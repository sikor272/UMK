using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdSortowanie 
{
    public abstract class Pojazd : IComparable<Pojazd>
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
        public int CompareTo(Pojazd other)
        {
            if(this.cena > other.cena)
            {
                return 1;
            }
            if (this.cena < other.cena)
            {
                return -1;
            }
            if (this.waga > other.waga)
            {
                return 1;
            }
            if (this.waga < other.waga)
            {
                return -1;
            }
            return 0;

        }
        public override string ToString()
        {
            return this.GetType().Name + " " + cena.ToString() + "zl, " + waga.ToString() + "kg";
        }
    }
}
