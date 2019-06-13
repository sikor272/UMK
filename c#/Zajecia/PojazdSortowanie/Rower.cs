using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdSortowanie
{
    public class Rower : Pojazd
    {
        private bool czyMaDach;
        public Rower()
        {
            miejsca = 1;
            kola = 2;
            czyMaDach = false;
        }
        public Rower(double cena , double waga, int miejsca = 1, int kola = 2, bool czyMaDach = false)
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
            return (kola > 2);
        }
    }
}
