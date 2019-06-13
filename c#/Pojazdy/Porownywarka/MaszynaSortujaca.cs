using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Porownywarka
{
    public class MaszynaSortujaca
    {
        private Pojazd[] pojazdy;
        public int Ilosc { get; private set; }
        public int Zaalokowane { get; private set; }

        //private readonly IComparer porownywacz;

        //public MaszynaSortujaca(System.Collections.IComparer porownywacz)
        //{
        //    Ilosc = 0;
        //    Zaalokowane = 100;
        //    pojazdy = new Pojazd[Zaalokowane];
        //    this.porownywacz = porownywacz;
        //}

        private readonly IPorownywarka porownywarka;
        public MaszynaSortujaca(IPorownywarka porownywarka)
        {
            Ilosc = 0;
            Zaalokowane = 100;
            pojazdy = new Pojazd[Zaalokowane];
            this.porownywarka = porownywarka;
        }

        public void DodajPojazd(Pojazd p)
        {
            if (Ilosc == Zaalokowane)
            {
                Zaalokowane *= 2;
                var tmp = new Pojazd[Zaalokowane];
                pojazdy.CopyTo(tmp, 0);
                pojazdy = tmp;
            }
            pojazdy[Ilosc] = p;
            Ilosc++;
        } 

        public void Wypisz()
        {
            for (int i = 0; i < Ilosc; i++)
            {
                Console.WriteLine(pojazdy[i]);
            }
        }

        public void Sortuj()
        {
            //Array.Sort(pojazdy, 0, Ilosc, porownywacz);
            for(int i = Ilosc - 2; i >= 0; i--)
            {
                for (int j = 0; j <= i; j++)
                {
                    if (porownywarka.PorownajPojazdy(pojazdy[j], pojazdy[j+1]) > 0)
                    {
                        var p = pojazdy[j];
                        pojazdy[j] = pojazdy[j + 1];
                        pojazdy[j + 1] = p;
                    }
                }
            }
        }
    }
}
