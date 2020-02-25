using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;

namespace TypeSort
{
    class SomeClass
    {
        public int Field1;
        public int Field2;

        public void Mathod1() { }
        public int Method2() { return 1; }
    }

    class TypeOfTest
    {
        static void Main()
        {
            Type t = typeof(SomeClass);
            FieldInfo[] field = t.GetFields();
            MethodInfo[] method = t.GetMethods();

            foreach (FieldInfo f in field)
                Console.WriteLine($"Field : { f.Name }");
            foreach (MethodInfo m in method)
                Console.WriteLine($"Method : { m.Name }");
        }
    }
}
