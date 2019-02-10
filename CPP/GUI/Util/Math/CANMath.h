#ifndef CANMATH_H_
#define CANMATH_H_

#include "../Basic.h"
#include "Constants.h"

#include <utility>

namespace CAN
{
	namespace Math
	{
		template<typename T>
		inline bool NumericValid(T num) { return !_isnan(num) && _finite(num); }

		template <class T1, class T2, class T3>
		inline T1 Clamp(T1 tVal, T2 tMin, T3 tMax)
		{
			if (tVal < tMin) return tMin;
			if (tVal > tMax) return tMax;
			return tVal;
		}
		inline float Saturate(float fVal) { return Clamp(fVal, 0.0f, 1.0f); }
		inline float Pow(float fVal, float fPow) { return powf(fVal, fPow); }
		//inline float Abs(float fVal) { return fabsf(fVal); }
		template <class T> inline T Abs(T tVal) { return tVal >= 0 ? tVal : -tVal; }
		inline float Sqrt(float fVal) { return sqrtf(fVal); }
		inline float ToRadians(float fDeg) { return (fDeg / 180.0f) * float(CAN_PI); }
		inline float ToDegrees(float fRad) { return (fRad / float(CAN_PI)) * 180.0f; }
		inline float Sin(float fVal) { return sinf(fVal); }
		inline float Cos(float fVal) { return cosf(fVal); }
		inline void SinCos(float fVal, float& fSin, float& fCos) { fSin = sinf(fVal); fCos = cosf(fVal); }
		inline float Tan(float fVal) { return tanf(fVal); }
		inline float Exp(float fVal) { return expf(fVal); }
		inline float Atan2(float fVal1, float fVal2) { return atan2f(fVal1, fVal2); }

		inline int FloorToInt(float fVal) { return (int)fVal; }

		template<class T1, class T2> inline auto Max(const T1& e1, const T2& e2) -> decltype(e1 + e2) { return e1 > e2 ? e1 : e2; }
		template<class T1, class T2> inline auto AbsMax(const T1& e1, const T2& e2) -> decltype(e1 + e2) { return Abs(e1) > Abs(e2) ? e1 : e2; }
		template<class T1, class T2> inline auto Min(const T1& e1, const T2& e2) -> decltype(e1 + e2) { return e1 < e2 ? e1 : e2; }
		template<class T1, class T2> inline auto AbsMin(const T1& e1, const T2& e2) -> decltype(e1 + e2) { return Abs(e1) < Abs(e2) ? e1 : e2; }
	}
}

#endif // !CANMATH_H_
