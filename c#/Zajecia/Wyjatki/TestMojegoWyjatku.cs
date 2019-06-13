using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Wyjatki
{
    public class TestMojegoWyjatku
    {
        private Random generator = new Random();
        public double Test()
        {
            
            double liczba = generator.NextDouble();
            if (liczba < .25)
            {
                throw new MojExeption();
            }
            return liczba;
        }
    }
}
