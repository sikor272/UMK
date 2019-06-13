using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
namespace Synchronizacja
{
    class Pisarz
    {
        public void Wypisz(object value)
        {
            lock (this)
            {
                for (int i = 0; i < 10; i++)
                {
                    Console.WriteLine(value.ToString());
                    //Console.WriteLine(Thread.CurrentThread.Name);
                    for (int j = 0, w = 1; j < 100000000; j++)
                    {
                        w *= j;
                    }
                }
                Console.WriteLine(value.ToString() + " - koniec");
            }
            
        }
    }
}
