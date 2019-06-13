using System;
using System.Threading;
class Program
{
    static void MetodaWatku()
    {
        int j = 1;
        Thread.Sleep(50);
        for (int i = 1; i < 100000000; i++)
        {
            j *= i;
        }
    }
    static void Main(string[] args)
    {
        Thread t = new Thread(new ThreadStart(MetodaWatku));
        Console.Write("Stan przed uruchomieniem:\n ");
        Console.WriteLine(t.ThreadState);
        t.Start();
        Thread.Sleep(10);
        Console.Write("Stan w uspieniu:\n ");
        Console.WriteLine(t.ThreadState);
        Thread.Sleep(60);
        Console.Write("Stan odczas pracy:\n ");
        Console.WriteLine(t.ThreadState);
        t.Join();
        Console.Write("Stan po zatrzymaniu:\n ");
        Console.WriteLine(t.ThreadState);
    }
}