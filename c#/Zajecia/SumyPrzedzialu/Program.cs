using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SumyPrzedzialu
{
    class Program
    {
        static void Main(string[] args)
        {
            double[] tab = { 0, 5, 3, 6, 7, 3, 7, 9, 0, 3, 7, 9, 0, 1, 7 };
            
            SumyPrzedzialu suma = new SumyPrzedzialu(tab);
            Console.WriteLine(suma.PodajPodSume(0, 10));
            Console.WriteLine(suma.PodajPodSume(0, 0));
            Console.WriteLine(suma.PodajPodSume(5, 10));
            Console.WriteLine(suma.PodajPodSume(7, 9));
            Console.WriteLine(suma.PodajPodSume(3, 5));
            Console.WriteLine(suma.PodajPodSume(10, 8));
        }
    }
}
