using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agrumenty
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Argumenty programu:");
            for(int i = 0; i < args.Length; i++)
            {
                Console.WriteLine("Argument {0}: {1}", i, args[i]);
            }
            foreach (string ala in args)
            {
                Console.WriteLine(ala);
            }
            
        }
    }
}
