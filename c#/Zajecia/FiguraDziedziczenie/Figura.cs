using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FiguraDziedziczenie
{
    class Figura
    {
        public double obwodFigury { get; protected set; }
        public double poleFigury { get; protected set; }
        public virtual void obliczPole() { }
        public virtual void obliczObwod() { }
        public override string ToString()
        {
            return "Figura klasy: " + base.ToString() + " obwod: " + obwodFigury + " pole: " + poleFigury;
        }
    }
}
