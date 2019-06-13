using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FiguraDziedziczenie
{
    class Program
    {
        static void Main(string[] args)
        {
            Prostokat k = new Prostokat(1,5);
            Kolo o = new Kolo(1);
            Kwadrat p = new Kwadrat(1);
            Console.WriteLine(k);
            Console.WriteLine(o);
            Console.WriteLine(p);
        }
    }
}
