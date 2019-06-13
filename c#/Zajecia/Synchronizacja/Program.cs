using System;
using System.Threading;
namespace Synchronizacja
{
    class Program
    {
        static void Main(string[] args)
        {
            Pisarz pisarz = new Pisarz();
            ParameterizedThreadStart metoda = new ParameterizedThreadStart(pisarz.Wypisz);
            Thread w1, w2;
            w1 = new Thread(metoda);
            w2 = new Thread(metoda);
            w1.Name = "Mickiewicz";
            w2.Name = "Sienkiewicz";
            w1.Priority = ThreadPriority.Lowest;
            w2.Priority = ThreadPriority.Highest;
            w1.Start(w1.Name);
            w2.Start(w2.Name);
            
        }
    }
}
