using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Srednie
{
    class Program
    {
        static void Main(string[] args)
        {
            double[] liczby = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            ISrednia wyliczarka = new SredniaArytmetyczna();
            ISrednia liczarka = new SredniaGeometryczna();
            ISrednia obliczarka = new SredniaHarmoniczna();
            ISrednia doliczarka = new SredniaKwadratowa();
            Console.WriteLine(wyliczarka.ObliczSrednia(liczby));
            Console.WriteLine(liczarka.ObliczSrednia(liczby));
            Console.WriteLine(obliczarka.ObliczSrednia(liczby));
            Console.WriteLine(doliczarka.ObliczSrednia(liczby));
        }
    }
}
