using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class Przedmiot
    {
        public int Id { get; protected set; }
        public string Nazwa { get; protected set; }
        public int Ilosc { get; protected set; }
        public int Typ_id { get; protected set; }
        public Przedmiot(int id, string nazwa,int ilosc, int typ_id)
        {
            Id = id;
            Nazwa = nazwa;
            Ilosc = ilosc;
            Typ_id = typ_id;
        }
        public override string ToString()
        {
            return Nazwa;
        }
    }
}
