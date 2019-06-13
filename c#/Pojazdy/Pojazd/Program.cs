using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pojazd
{
    class Program
    {
        static void Main(string[] args)
        {
            Pojazd rower = new Rower();
            //rower.UstawIloscKol(2);
            rower.UstawWage(15);
            //rower.UstawIloscMiejsc(1);
            rower.UstawCene(599);


        }
    }
}
