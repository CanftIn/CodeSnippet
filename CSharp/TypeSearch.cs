using System;
using System.Collections.Generic;
using System.Text;

namespace TypeSort
{
    class TypeSearch
    {
        public static void TestSearch()
        {
            List<Square> listOfSquares = new List<Square>
            {
                new Square(1, 3),
                new Square(4, 3),
                new Square(2, 1),
                new Square(6, 1)
            };

            IComparer<Square> heightCompare = new CompareHeight();

            foreach(Square square in listOfSquares)
            {
                Console.WriteLine(square.ToString());
            }

        }

        public struct Dimensions
        {
            public int Height;
            public int Width;
            public int Depth;
        }

        public Tuple<int, int, int> ReturnDimensionsAsTuple(int inputShape)
        {
            var objDim = Tuple.Create<int, int, int>(5, 10, 15);
            return objDim;
        }

    }
}
