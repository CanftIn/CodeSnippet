using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace TypeSort
{
    public class ROColection : ReadOnlyCollectionBase
    {
        public ROColection(IList sourceList)
        {
            InnerList.AddRange(sourceList);
        }

        public Object this[int index]
        {
            get { return (InnerList[index]); }
        }

        public int IndexOf(Object value)
        {
            return (InnerList.IndexOf(value));
        }

        public bool Contains(Object value)
        {
            return (InnerList.Contains(value));
        }
    }
    class Test
    {
    }
}
