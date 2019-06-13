using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Srednie
{
    class SredniaArytmetyczna : ISrednia
    {
        public double ObliczSrednia(double[] liczby)
        {
            double suma = 0;
            foreach (var liczba in liczby)
            {
                suma += liczba;
            }
            return suma / liczby.Length;
            // Mozna jako metoda wbudowanaa
            // return liczby.Average();
        }
    }
}
