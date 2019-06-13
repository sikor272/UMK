using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Szyfrowanie
{
    class Program
    {
        static void Main(string[] args)
        {
            string doZaszyfrowania,zaszyfrowany = "";
            doZaszyfrowania = Console.ReadLine();
            for(int i = 0; i < doZaszyfrowania.Length; i++)
            {
                char znak = doZaszyfrowania[i];
                char szyfrowany;
                int jeden, dwa, trzy, cztery;
                jeden = (int)znak & 1;
                dwa = (int)znak & 2;
                trzy = (int)znak & 4;
                cztery = (int)znak & 8;
                szyfrowany = (char)(znak ^ (znak & 15));
                szyfrowany = (char) (szyfrowany | trzy << 1 | jeden << 1 | cztery >> 1 | dwa >> 1);
                zaszyfrowany += szyfrowany;
            }
            Console.WriteLine(zaszyfrowany);
        }
    }
}
