using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdySortowanie
{
    class Samochod : Pojazd
    {
        private bool czyMaDach;

        public Samochod()
        {
            kola = 4;
            miejsca = 4;
            czyMaDach = true;
        }
        public Samochod(double cena, double waga, int miejsca = 4, 
            int kola = 4, bool czyMaDach = true)
        {
            this.UstawIloscKol(kola);
            UstawWage(waga);
            UstawIloscMiejsc(miejsca);
            UstawCene(cena);
            this.czyMaDach = czyMaDach;
        }
        public override bool CzyMaDach()
        {
            return czyMaDach;
        }

        public override bool CzyUtonie()
        {
            return true;
        }

        public override bool CzyWieloslad()
        {
            return true;
        }
    }
}
