using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Porownywarka
{
    public class Rower : Pojazd
    {
        private bool czyMaDach;

        public Rower()
        {
            kola = 2;
            miejsca = 1;
            czyMaDach = false;
        }
        public Rower(double cena, double waga, int miejsca = 1, int kola = 2,
            bool czyMaDach = false)
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
            return kola > 2;
        }


    }
}
