using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Wyjatki
{
    class Program
    {
        static void Main(string[] args)
        {
            /*LapanieWyjatkow testuj = new LapanieWyjatkow();
            int[] dane = new int[] { 1,2,0,4,5,6,7,8,9,10,11};
            Console.WriteLine(testuj.Podziel(dane));*/
            TestMojegoWyjatku test = new TestMojegoWyjatku();
            for(int i = 0; i < 100; i++)
            {
                string wartosc = "Wartosc nie zostala odczytana";
                try
                {
                    wartosc = test.Test().ToString();
                }
                catch
                {
                    Console.WriteLine("Przechwycenie wyjatku dla i = {0}", i);
                }
                finally
                {
                    Console.WriteLine("Losowanie: {0}", wartosc);
                }
            }
            
        }
    }
}
