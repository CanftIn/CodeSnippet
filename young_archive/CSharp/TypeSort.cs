using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;

namespace TypeSort
{
    public class Square : IComparable<Square>
    {
        public Square() { }

        public Square(int height, int width)
        {
            this.Height = height;
            this.Width = width;
        }

        public int Height { get; set; }

        public int Width { get; set; }

        public int CompareTo(object obj)
        {
            Square square = obj as Square;
            if (square != null)
                return CompareTo(square);
            throw
                new ArgumentException(
                    "Both objects being compared must be of type Square");
        }
        public int CompareTo(Square other)
        {
            long area1 = this.Height * this.Width;
            long area2 = other.Height * other.Width;

            if (area1 == area2)
                return 0;
            else if (area1 > area2)
                return 1;
            else if (area1 < area2)
                return -1;
            else
                return -1;
        }

        public override string ToString() =>
            ($"Height: {this.Height}    Width: {this.Width}");

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            Square square = obj as Square;
            if (square != null)
                return this.Height == square.Height && 
                    this.Width == square.Width;
            return false;
        }

        public override int GetHashCode()
        {
            return this.Height.GetHashCode() | this.Width.GetHashCode();
        }

        public static bool operator ==(Square x, Square y) => x.Equals(y);
        public static bool operator !=(Square x, Square y) => !(x == y);
        public static bool operator <(Square x, Square y) => (x.CompareTo(y) < 0);
        public static bool operator >(Square x, Square y) => (x.CompareTo(y) > 0);
    }

    public class CompareHeight : IComparer<Square>
    {
        public int Compare(object firstSquare, object secondSquare)
        {
            Square square1 = firstSquare as Square;
            Square square2 = secondSquare as Square;
            if (square1 == null || square2 == null)
                throw (new ArgumentException("Both parameters must be of type Square."));
            else
                return Compare(firstSquare, secondSquare);
        }

        public int Compare(Square x, Square y)
        {
            if (x.Height == y.Height)
                return 0;
            else if (x.Height > y.Height)
                return 1;
            else if (x.Height < y.Height)
                return -1;
            else
                return -1;
        }
    }


    class TypeSort
    {
        public static void TestSort()
        {
            List<Square> listOfSquares = new List<Square>()
            {
                new Square(1, 3),
                new Square(4, 3),
                new Square(2, 1),
                new Square(6, 1)
            };

            foreach (Square square in listOfSquares)
            {
                Console.WriteLine(square.ToString());
            }

            Console.WriteLine();

            listOfSquares.Sort();
            foreach (Square square in listOfSquares)
            {
                Console.WriteLine(square.ToString());
            }
        }

        static void Main(string[] args)
        {
            TestSort();
        }
    }
}
