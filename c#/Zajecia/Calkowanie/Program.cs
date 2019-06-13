using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calkowanie
{ 
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 5)
            {
                Console.WriteLine("Nalezy podac dokladnie piec argument!");
                return;
            }
            double a, b, c, d, e;
            a = double.Parse(args[0]);
            b = double.Parse(args[1]);
            c = double.Parse(args[2]);
            FunkcjaKwadratowa funkcja = new FunkcjaKwadratowa(a, b, c);
            for (int i = 3; i < args.Length; i += 2)
            {
                d = double.Parse(args[i]);
                e = double.Parse(args[i + 1]);
                Console.WriteLine(funkcja.CalkaOznaczona(d, e));
            }
        }
    }
}
