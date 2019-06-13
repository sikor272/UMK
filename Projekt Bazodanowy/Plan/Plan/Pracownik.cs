using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class Pracownik
    {
        public int Id { get; protected set; }
        public string Imie { get; protected set; }
        public string Nazwisko { get; protected set; }
        public string Tytul { get; protected set; }
        public int Lokalny { get; protected set; }
        public Pracownik(int id, string imie, string nazwisko, string tytul, int lokalny)
        {
            Id = id;
            Imie = imie;
            Nazwisko = nazwisko;
            Tytul = tytul;
            Lokalny = lokalny;
        }
        public override string ToString()
        {
            return Tytul + " " + Imie + " " + Nazwisko;
        }
        public ComboBoxItem ComboItem()
        {
            return new ComboBoxItem(Id, this.ToString());
        }
    }
}
