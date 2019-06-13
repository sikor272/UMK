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
            double[] jedynki = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } ;
            double[] liczby = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            ISrednia wyliczarkaKwadratowa = new SredniaKwadratowa();
            Console.WriteLine(wyliczarkaKwadratowa.ObliczSrednia(liczby));

            ISrednia wyliczarkaArytmetyczna = new SredniaArytmetyczna();
            Console.WriteLine(wyliczarkaArytmetyczna.ObliczSrednia(liczby));

            ISrednia wyliczarkaGeometryczna = new SredniaGeometryczna();
            Console.WriteLine(wyliczarkaGeometryczna.ObliczSrednia(liczby));

            ISrednia wyliczarkaHarmoniczna = new SredniaHarmoniczna();
            Console.WriteLine(wyliczarkaHarmoniczna.ObliczSrednia(liczby));


        }
    }
}
