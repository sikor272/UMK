using System;
using System.Threading; 
namespace Watki_2
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread t = new Thread(new ThreadStart(() =>
            {
                for (int i = 1; i <= 100; i++)
                {
                    Console.Write("{0,4}", i);
                }
            }));
            t.Start();
        }
    }
}
