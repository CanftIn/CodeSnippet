using System;
using System.Collections.Generic;
using System.Text;

namespace TypeSort
{

    delegate void MyDel(int value);

    class Program
    {
        void PrintLow(int value)
        {
            Console.WriteLine($"{value} - Low Value");
        }

        void PrintHigh(int value)
        {
            Console.WriteLine($"{value} - High Value");
        }

        delegate void MyAnonymousDel();

        static void Main()
        {
            Program program = new Program();
            MyDel del;
            Random rand = new Random();
            int randomValue = rand.Next(99);

            del = randomValue < 50
                ? new MyDel(program.PrintLow)
                : new MyDel(program.PrintHigh);
            del(randomValue);

            MyAnonymousDel mydel;
            mydel = delegate { Console.WriteLine("Value of x"); };
        }
    }
}
