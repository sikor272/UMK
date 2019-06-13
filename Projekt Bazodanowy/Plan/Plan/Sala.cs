using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class Sala
    {
        public int Id { get; protected set; }
        public string Nazwa { get; protected set; }
        public Sala(int id, string nazwa)
        {
            Id = id;
            Nazwa = nazwa;
        }
        public override string ToString()
        {
            return Nazwa;
        }
        public ComboBoxItem ComboItem()
        {
            return new ComboBoxItem(Id, Nazwa);
        }
    }
}
