using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Srednie
{
    public class SredniaGeometryczna : ISrednia
    {
        public double ObliczSrednia(double[] liczby)
        {
            double iloczyn = 1;
            foreach (var liczba in liczby)
            {
                iloczyn *= liczba;
            }
            return Math.Pow(iloczyn,1.0/liczby.Length);
        }
    }
}
