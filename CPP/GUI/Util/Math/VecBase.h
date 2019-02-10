#ifndef VECBASE_H_
#define VECBASE_H_

#include <cassert>

namespace CAN
{
	template<unsigned int N, class T>
	class Vec
	{
	public:
		T v[N];

		inline const T& operator [] (const size_t idx) const
		{
			assert(idx < 1);
			return v[idx];
		}

		inline T& operator [] (const size_t idx)
		{
			assert(idx < 1);
			return v[idx];
		}
	};
}

#endif // !VECBASE_H_
