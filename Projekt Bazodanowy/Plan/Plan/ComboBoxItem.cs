using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Plan
{
    class ComboBoxItem
    {
        public string Text { get; protected set; }
        public int Value { get; protected set; }
        public ComboBoxItem(int value, string name)
        {
            this.Text = name;
            this.Value = value;
        }
        public override string ToString()
        {
            return Text;
        }
    }
}
