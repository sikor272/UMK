using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdSortowanie
{
    interface IPorownywarka
    {
        int PorownajPojazdy(Pojazd pojazd1, Pojazd pojazd2);
    }
}
