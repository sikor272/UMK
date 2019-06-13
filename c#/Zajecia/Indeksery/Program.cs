using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

struct Bool32
{
    private Int32 liczba;
    public Bool32(Int32 value)
    {
        liczba = value;
    }
    public bool this[int i]
    {
        get
        {
            if( i< 0 || i >= 32 )
                throw new ArgumentOutOfRangeException("indeks");
            if (((liczba >> i) & (Int32)1) == 1)
                return true;
            return false;
        }
        set
        {
            if(i< 0 || i >= 32)
                throw new ArgumentOutOfRangeException("indeks");
            liczba &= ~(((Int32)1) << i);
            if(value)
                liczba |= ((Int32) 1) << i;
        }
    }
}

namespace Indeksery
{
    class Program
    {
        static void Main(string[] args)
        {
            Bool32 test = new Bool32(14);
            Console.WriteLine(test[4]);
            test[4] = true;
            Console.WriteLine(test[4]);
        }
    }
}
