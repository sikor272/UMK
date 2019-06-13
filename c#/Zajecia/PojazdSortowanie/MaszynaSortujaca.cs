using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdSortowanie
{
    class MaszynaSortujaca
    {
        private Pojazd[] pojazdy;
        public int Ilosc { get; private set; }
        public int Zalokowane { get; private set; }
        private readonly IPorownywarka porownywarka;
        public MaszynaSortujaca(IPorownywarka porownywacz)
        {
            Ilosc = 0;
            Zalokowane = 100;
            pojazdy = new Pojazd[Zalokowane];
            this.porownywarka = porownywacz;
        }
        public void DodajPojazd(Pojazd p)
        {
            if(Ilosc == Zalokowane)
            {
                Zalokowane *= 2;
                var tmp = new Pojazd[Zalokowane];
                pojazdy.CopyTo(tmp,0);
                pojazdy = tmp;
            }
            pojazdy[Ilosc] = p;
            Ilosc++;
        }
        public void Wypisz()
        {
            for(int i = 0; i < Ilosc; i++)
            {
                Console.WriteLine(pojazdy[i]);
            }
        }
        public void Sortuj()
        {
            //Array.Sort<Pojazd>(pojazdy, 0, Ilosc, PorownajPojazdy);
            for (int i = 0; i < Ilosc; i++)
            {
                for (int j = 1; j < Ilosc - i; j++)
                {
                    if (porownywarka.PorownajPojazdy(pojazdy[j], pojazdy[j - 1]) < 0)
                    {
                        var p = pojazdy[j];
                        pojazdy[j] = pojazdy[j - 1];
                        pojazdy[j - 1] = p;
                    }
                }
            }
        }
    }
}
