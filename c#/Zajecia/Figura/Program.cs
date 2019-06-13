using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Figura
{
    class Program
    {
        static void Main(string[] args)
        {
            Figura f = new Figura("Kolo");
            f.Pole = 15;
            f.Obwod = 10;

            Figura k = new Figura("Kwadrat");
            k.Pole = 20;
            k.Obwod = 14;

            Figura s = new Figura("Kwadrat 2");
            s.Pole = 20;
            s.Obwod = 14;

            Console.WriteLine(f.WypiszLicznik());
            k.UstawLicznik(124);
            Console.WriteLine(Figura.WypiszLicznikStatycznie());
            Figura.UstawLicznikStatycznie(150);
            Console.WriteLine(k.WypiszLicznik());
        }
    }
}
