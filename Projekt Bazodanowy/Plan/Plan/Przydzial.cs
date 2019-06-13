using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class Przydzial
    {
        public int Id { get; protected set; }
        public int Id_przedmiot { get; protected set; }
        public int Id_pracownik { get; protected set; }
        public int Id_student { get; protected set; }
        public Przydzial(int id, int przedmiot, int pracownik, int student)
        {
            Id = id;
            Id_przedmiot = przedmiot;
            Id_pracownik = pracownik;
            Id_student = student;
        }
    }
}
