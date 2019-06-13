using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FiguraDziedziczenie
{
    class Prostokat : Figura
    {
        readonly public double bokA;
        readonly public double bokB;
        public Prostokat(double a,double b)
        {
            bokA = a;
            bokB = b;
            obliczObwod();
            obliczPole();
        }
        public override void obliczPole()
        {
            poleFigury = bokA * bokB;
        }
        public override void obliczObwod()
        {
            obwodFigury = 2 * bokA + 2 * bokB;
        }
    }
}
