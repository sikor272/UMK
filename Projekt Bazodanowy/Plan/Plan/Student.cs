using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class Student
    {
        public int Id { get; protected set; }
        public string Rok { get; protected set; }
        public string Grupa { get; protected set; }
        public Student(int id, string rok, string grupa)
        {
            Id = id;
            Rok = rok;
            Grupa = grupa;
        }
        public override string ToString()
        {
            return Rok;
        }
        public ComboBoxItem ComboItem()
        {
            return new ComboBoxItem(Id, Rok);
        }
        public ComboBoxItem ComboItemAll()
        {
            return new ComboBoxItem(Id, Rok + " [" + Grupa + "]");
        }
    }
}
