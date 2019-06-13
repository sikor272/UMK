using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdySortowanie
{
    class Program
    {
        static void Main(string[] args)
        {
            Pojazd[] pojazdy =
            {
                new Samochod(25000,1500),
                new Rower(799,15),
                new Rower(799,14),
                new Lodz(150000,2000),
                new Rower(299,10)
            };

            Console.WriteLine("Przed sortowaniem:");
            foreach (Pojazd p in pojazdy)
            {
                Console.WriteLine(p);
            }

            Console.WriteLine("\nPo sortowaniu:");
            //Array.Sort<Pojazd>(pojazdy);
            Array.Sort(pojazdy);

            foreach (Pojazd p in pojazdy)
            {
                Console.WriteLine(p);
            }
        }
    }
}
