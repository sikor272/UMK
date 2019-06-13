using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class Termin
    {
        public int Id { get; protected set; }
        public string Data { get; protected set; }
        public Termin(int id, string data)
        {
            Id = id;
            Data = data;
        }
        public override string ToString()
        {
            return Data;
        }
    }
}
