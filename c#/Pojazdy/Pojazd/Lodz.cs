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
            // kola = 0; // można pominąć
            miejsca = 1;
            czyMaDach = false;
        }
        public Lodz(double cena, double waga, int miejsca = 1, 
            bool czyMaDach = false)
        {
            // UstawIloscKol(0); // można pominąć
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
            return false;
        }

        public override bool CzyWieloslad()
        {
            return false;
        }
    }
}
