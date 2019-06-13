using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FiguraDziedziczenie
{
    class Kolo : Figura
    {
        readonly public double Promien;
        public Kolo(double promien)
        {
            Promien = promien;
            obliczObwod();
            obliczPole();
        }
        public override void obliczPole()
        {
            poleFigury = Math.PI * Promien * Promien;
        }
        public override void obliczObwod()
        {
            obwodFigury = 2 * Math.PI * Promien;
        }
        
    }
}
