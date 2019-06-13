using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MonteCarlo
{
    class Figura
    {
        private double r;
        public Figura(double r)
        {
            this.r = r;
        }
        public bool CzyPunktJestWewnatrz(double x, double y)
        {
            if (x * x + y * y < r * r)
                return true;
            return false;
        }
    }
}
