using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Porownywarka
{


    class Program
    {
        static void Main(string[] args)
        {
            IPorownywarka porownywarka = new PorownywarkaA();
            MaszynaSortujaca m = new MaszynaSortujaca(porownywarka);

            Pojazd[] pojazdy =
               {
                new Samochod(25000,1500),
                new Rower(799,15),
                new Rower(799,14),
                new Lodz(150000,2000),
                new Rower(299,10)
            };

            foreach (Pojazd p in pojazdy)
            {
                m.DodajPojazd(p);
            }
            Console.WriteLine("Przed sortowaniem:");
            m.Wypisz();
            Console.WriteLine("Po sortowaniu:");
            m.Sortuj();
            m.Wypisz();
        }
    }
}
