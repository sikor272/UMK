using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class ElementPlanu
    {
        public int Id { get; protected set; }
        public int Poczatek { get; protected set; }
        public int Koniec { get; protected set; }
        public int Sala_id { get; protected set; }
        public int Termin_id { get; protected set; }
        public int Przydzial_id { get; protected set; }

        public ElementPlanu(int id, int poczatek, int koniec, int sala, int data, int przydzial)
        {
            Id = id;
            Poczatek = poczatek;
            Koniec = koniec;
            Sala_id = sala;
            Termin_id = data;
            Przydzial_id = przydzial;
        }
    }
}
