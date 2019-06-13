using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pierwiastki
{
    class SzukajPierwiastka
    {
        public double Funkcja(double x)
        {
            return x * x * x - 2 * x * x - x + 2;
        } // 2 i 1 //
        public void Szukaj(double l, double p)
        {
            double wartosc;
            while (Math.Abs(l - p) > 0.0001)
            {
                wartosc = (l + p) / 2;
                if (Math.Abs(Funkcja(wartosc)) <= 0.0001)
                {
                    Console.WriteLine(wartosc);
                }
                if(Funkcja(wartosc) * Funkcja(l) < 0.0001)
                {
                    p = wartosc;
                } else
                {
                    l = wartosc;
                }
            }
        }
    }
}
