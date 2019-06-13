using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MonteCarlo
{
    class Program
    {
        const int IloscLosowan = 10000000;
        static void Main(string[] args)
        {
            Random generator = new Random();
            Figura kolo = new Figura(1);
            int iloscWewnatrz = 0;
            for(int i = 0; i < IloscLosowan; i++)
            {
                double x = generator.NextDouble();
                double y = generator.NextDouble();
                if (kolo.CzyPunktJestWewnatrz(x, y))
                    iloscWewnatrz++;
            }
            Console.WriteLine("Wysolowana ilosc : " + 4.0*iloscWewnatrz/IloscLosowan);
        }
    }
}
