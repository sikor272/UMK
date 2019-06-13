using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calkowanie
{
    class FunkcjaKwadratowa
    {
        private double a, b, c;
        private double FunkcjaPierwotna(double x)
        {
            return x * (x * (x * a / 3.0 + b / 2.0) + c); 
        }
       public FunkcjaKwadratowa(double _a, double _b, double _c)
        {
            a = _a;
            b = _b;
            c = _c;
        }
        public double CalkaOznaczona(double x1, double x2)
        {
            return FunkcjaPierwotna(x1) - FunkcjaPierwotna(x2);
        }
    }
}
