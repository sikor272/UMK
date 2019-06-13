using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Plan
{
    /// <summary>
    /// Klasa z wlasnasci czcionki, srodkowania dla pola TextBlock
    /// </summary>
    class TextBlockItem
    {
        TextBlock pole;
        public TextBlockItem(string nazwa, int kolumna, int wiersz)
        {
            pole = new TextBlock
            {
                Margin = new Thickness(5),
                Text = nazwa,
                FontSize = 10,
                HorizontalAlignment = HorizontalAlignment.Center,
                VerticalAlignment = VerticalAlignment.Center
            };
            Grid.SetColumn(pole, kolumna);
            Grid.SetRow(pole, wiersz);
        }
        public TextBlockItem(string nazwa, int kolumna, int wiersz, int wiersze)
        {
            pole = new TextBlock
            {
                Margin = new Thickness(5),
                Text = nazwa,
                FontSize = 10,
                HorizontalAlignment = HorizontalAlignment.Center,
                VerticalAlignment = VerticalAlignment.Center
            };
            Grid.SetColumn(pole, kolumna);
            Grid.SetRow(pole, wiersz);
            Grid.SetRowSpan(pole, wiersze);
        }
        public TextBlockItem(string nazwa, int kolumna, int wiersz, int wiersze, int kolumny)
        {
            pole = new TextBlock
            {
                Margin = new Thickness(5),
                Text = nazwa,
                FontSize = 10,
                HorizontalAlignment = HorizontalAlignment.Center,
                VerticalAlignment = VerticalAlignment.Center
            };
            Grid.SetColumn(pole, kolumna);
            Grid.SetRow(pole, wiersz);
            Grid.SetRowSpan(pole, wiersze);
            Grid.SetColumnSpan(pole, kolumny);
        }
        public TextBlock Element()
        {
            return pole;
        }
    }
}
