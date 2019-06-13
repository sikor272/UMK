using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PojazdSortowanie
{
    class Program
    {
        static void Main(string[] args)
        {
            /*Pojazd[] pojazdy =
            {
                new Samochod(25000, 1300),
                new Rower(500,50),
                new Rower(500,10),
                new Lodz(20000,450),
                new Lodz(10000,450),
                new Samochod(234500,3400)
            };
            Console.WriteLine("Przed sort:");
            foreach(Pojazd p in pojazdy)
            {
                Console.WriteLine(p);
            }
            //Array.Sort<Pojazd>(pojazdy);
            Array.Sort(pojazdy);
            Console.WriteLine("Po sort:");
            foreach (Pojazd p in pojazdy)
            {
                Console.WriteLine(p);
            }*/
            IPorownywarka porownaj = new Porownywarka();
            MaszynaSortujaca m = new MaszynaSortujaca(porownaj);
            Pojazd[] pojazdy =
           {
               new Samochod(25000, 1300),
               new Rower(500,50),
               new Rower(500,10),
               new Lodz(20000,450),
               new Lodz(10000,450),
               new Samochod(234500,3400)
           };
           foreach (Pojazd p in pojazdy)
           {
               m.DodajPojazd(p);
           }
            Console.WriteLine("Przed sort:");
            m.Wypisz();
            m.Sortuj();
           Console.WriteLine("Po sort:");
            m.Wypisz();
        }
    }
}
