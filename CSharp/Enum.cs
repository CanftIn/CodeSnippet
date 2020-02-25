using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace TypeSort
{
    class Enum
    {
        static void Main()
        {
            func1();
        }

        static void func1()
        {
            int[] arr = { 1, 2, 3, 4 };
            IEnumerator ie = arr.GetEnumerator();
            while(ie.MoveNext())
            {
                int item = (int)ie.Current;

                Console.WriteLine("{0}  ", ie.Current);
            }
        }
    }
}
