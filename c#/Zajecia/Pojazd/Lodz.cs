using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pojazd
{
    public class Lodz : Pojazd
    {
        private bool czyMaDach;
        public Lodz()
        {
            miejsca = 2;
            kola = 0;
            czyMaDach = false;
        }
        public Lodz(double cena, double waga, int miejsca = 2, bool czyMaDach = false, int kola = 0)
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
            return false;
        }

        public override bool CzyWieloslad()
        {
            return false;
        }
    }
}
