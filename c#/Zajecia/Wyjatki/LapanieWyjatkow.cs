using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Wyjatki
{
    class LapanieWyjatkow
    {
        public int Podziel(int[] tablica)
        {
            int wynik = 0;

            checked {
                try
                {
                    wynik = tablica[0];
                    for (int i = 1; i < 10; i++)
                    {
                        wynik *= tablica[i];
                    }
                    for (int i = 0; i <= 4; i++)
                    {
                        tablica[i] = tablica[i] / tablica[i + 1];
                    }
                    for (int i = 5; i <= 8; i++)
                    {
                        tablica[i] = tablica[i] * (tablica[i - 1] + tablica[i + 1]);
                    }
                }
                catch (OverflowException)
                {
                    Console.WriteLine("Poza zasieg");
                }
                catch (IndexOutOfRangeException)
                {
                    Console.WriteLine("Zly rozmiar");
                }
                catch (DivideByZeroException)
                {
                    Console.WriteLine("Dzielenie przez zero");
                }
                catch (NullReferenceException ex)
                {
                    Console.WriteLine("Wyjatek null");
                    Console.WriteLine("Informajca o bledzie: " + ex.Message);
                    Console.WriteLine(ex.StackTrace);
                    Console.WriteLine(ex.Source);
                    Console.WriteLine(ex.TargetSite);
                }
                catch (ArithmeticException ex)
                {
                    Console.WriteLine("Wyjatek arytmetyczny");
                    Console.WriteLine(ex.Message);
                    Console.WriteLine(ex.StackTrace);
                    Console.WriteLine(ex.Source);
                    Console.WriteLine(ex.TargetSite);
                }
                catch (Exception)
                {
                    Console.WriteLine("Wyjatek bez nazyw aktualnie :D");
                }
            }
            return wynik;
        }
    }
}
