using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Porownywarka
{
    class PorownywarkaA : IPorownywarka
    {
        public int PorownajPojazdy(Pojazd pojazd1, Pojazd pojazd2)
        {
            if (pojazd1.Cena > pojazd2.Cena)
            {
                return 1;
            }
            if (pojazd1.Cena < pojazd2.Cena)
            {
                return -1;
            }

            if (pojazd1.Waga > pojazd2.Waga)
            {
                return 1;
            }
            if (pojazd1.Waga < pojazd2.Waga)
            {
                return -1;
            }

            return 0;
        }
    }
}
