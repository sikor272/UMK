using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FiguraDziedziczenie
{
    class Kwadrat : Prostokat
    {
        public Kwadrat(double bok) : base(bok, bok)
        {
            obliczObwod();
            obliczPole();
        }

    }
}
