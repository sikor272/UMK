using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SumyPrzedzialu
{
    class SumyPrzedzialu
    {
        private double[] sumy;
        public SumyPrzedzialu(double[] tab)
        {
            if(tab == null || tab.LongLength == 0)
            {
                throw new ArgumentOutOfRangeException("Zły rozmiar tablicy");
            }
            sumy = new double[tab.Length];
            sumy[0] = tab[0];
            for (int i = 1; i < tab.Length; i++)
            {
                sumy[i] = sumy[i - 1] + tab[i];
            }
        }
        public double PodajPodSume(int a, int b)
        {
            if(b < 0 || b > sumy.Length || a > b)
            {
                throw new ArgumentOutOfRangeException("Zly przedzial");
            }
            if (a == 0)
                return sumy[b];
            
            return sumy[b] - sumy[a - 1];
        }
    }
}
