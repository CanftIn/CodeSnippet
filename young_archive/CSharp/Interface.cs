using System;
using System.Collections.Generic;
using System.Text;

namespace TypeSort
{
    class Interface
    {
        static void Main()
        {
            var trivInt = new Simple<int>();
            var trivString = new Simple<string>();

            Console.WriteLine($"{trivInt.ReturnIt(4)}");
            Console.WriteLine($"{trivString.ReturnIt("fuck")}");
        }
    }
    
    interface IMyIf<T>
    {
        T ReturnIt(T inValue);
    }

    class Simple<S> : IMyIf<S>
    {
        public S ReturnIt(S inValue)
        {
            return inValue;
        }
    }

}
