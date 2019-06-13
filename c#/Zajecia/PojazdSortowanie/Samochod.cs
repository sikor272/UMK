using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdSortowanie
{
    public class Samochod : Pojazd
    {
        private bool czyMaDach;
        public Samochod()
        {
            miejsca = 2;
            kola = 4;
            czyMaDach = false;
        }
        public Samochod(double cena, double waga, bool czyMaDach = false, int miejsca = 2, int kola = 4)
        {
            this.UstawIloscMiejsc(miejsca);
            this.UstawIloscKol(kola);
            this.UstawCene(cena);
            this.UstawWage(waga);
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
