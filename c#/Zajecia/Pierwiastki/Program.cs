using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pierwiastki
{
    class Program
    {
        static void Main(string[] args)
        {
            SzukajPierwiastka fun = new SzukajPierwiastka();
            fun.Szukaj(-10, 14);
        }
    }
}
