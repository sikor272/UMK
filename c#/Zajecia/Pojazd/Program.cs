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
            Pojazd rower = new Rower(999.99,50.0);
            Pojazd audi = new Samochod(54999.99, 1478.87, true, 5);
        }
    }
}
