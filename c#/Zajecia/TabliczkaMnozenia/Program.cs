using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TabliczkaMnozenia
{
    class Program
    {
        static void Main(string[] args)
        {
            if(args.Length != 1)
            {
                Console.WriteLine("Nalezy podac dokladnie jeden argument!");
                return;
            }
            int n = Int32.Parse(args[0]);
            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <=n; j++)
                {
                    Console.Write("{0,4}", i * j);
                }
                Console.WriteLine();
            }
        }
    }
}
