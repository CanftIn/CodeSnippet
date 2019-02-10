#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <limits>

namespace CAN
{
	namespace Constants
	{
		static struct Null {
		} CAN_NULL;

		static struct True {
			__forceinline operator bool() const { return true; }
		} CAN_TRUE;

		static struct False {
			__forceinline operator bool() const { return false; }
		} CAN_FALSE;

		static struct Emp {
		} CAN_EMP;

		static struct Full {
		} CAN_FULL;
	}

	namespace Math
	{
		static struct Zero
		{
			__forceinline operator double() const { return 0.0; }
			__forceinline operator float() const { return 0.0f; }
			__forceinline operator long long() const { return 0; }
			__forceinline operator unsigned long long() const { return 0; }
			__forceinline operator long() const { return 0; }
			__forceinline operator unsigned long() const { return 0; }
			__forceinline operator int() const { return 0; }
			__forceinline operator unsigned int() const { return 0; }
			__forceinline operator short() const { return 0; }
			__forceinline operator unsigned short() const { return 0; }
			__forceinline operator char() const { return 0; }
			__forceinline operator unsigned char() const { return 0; }
		} CAN_ZERO;

		static struct One
		{
			__forceinline operator double() const { return 1.0; }
			__forceinline operator float() const { return 1.0f; }
			__forceinline operator long long() const { return 1; }
			__forceinline operator unsigned long long() const { return 1; }
			__forceinline operator long() const { return 1; }
			__forceinline operator unsigned long() const { return 1; }
			__forceinline operator int() const { return 1; }
			__forceinline operator unsigned int() const { return 1; }
			__forceinline operator short() const { return 1; }
			__forceinline operator unsigned short() const { return 1; }
			__forceinline operator char() const { return 1; }
			__forceinline operator unsigned char() const { return 1; }
		} CAN_ONE;

		static struct NegInf
		{
			__forceinline operator double() const { return -std::numeric_limits<double>::infinity(); }
			__forceinline operator float() const { return -std::numeric_limits<float>::infinity(); }
			__forceinline operator long long() const { return std::numeric_limits<long long>::min(); }
			__forceinline operator unsigned long long() const { return std::numeric_limits<unsigned long long>::min(); }
			__forceinline operator long() const { return std::numeric_limits<long>::min(); }
			__forceinline operator unsigned long() const { return std::numeric_limits<unsigned long>::min(); }
			__forceinline operator int() const { return std::numeric_limits<int>::min(); }
			__forceinline operator unsigned int() const { return std::numeric_limits<unsigned int>::min(); }
			__forceinline operator short() const { return std::numeric_limits<short>::min(); }
			__forceinline operator unsigned short() const { return std::numeric_limits<unsigned short>::min(); }
			__forceinline operator char() const { return std::numeric_limits<char>::min(); }
			__forceinline operator unsigned char() const { return std::numeric_limits<unsigned char>::min(); }

		} CAN_NEG_INFINITY;

		static struct PosInf
		{
			__forceinline operator double() const { return std::numeric_limits<double>::infinity(); }
			__forceinline operator float() const { return std::numeric_limits<float>::infinity(); }
			__forceinline operator long long() const { return std::numeric_limits<long long>::max(); }
			__forceinline operator unsigned long long() const { return std::numeric_limits<unsigned long long>::max(); }
			__forceinline operator long() const { return std::numeric_limits<long>::max(); }
			__forceinline operator unsigned long() const { return std::numeric_limits<unsigned long>::max(); }
			__forceinline operator int() const { return std::numeric_limits<int>::max(); }
			__forceinline operator unsigned int() const { return std::numeric_limits<unsigned int>::max(); }
			__forceinline operator short() const { return std::numeric_limits<short>::max(); }
			__forceinline operator unsigned short() const { return std::numeric_limits<unsigned short>::max(); }
			__forceinline operator char() const { return std::numeric_limits<char>::max(); }
			__forceinline operator unsigned char() const { return std::numeric_limits<unsigned char>::max(); }
		} CAN_INFINITY, CAN_POS_INFINITY;

		static struct NaN
		{
			__forceinline operator double() const { return std::numeric_limits<double>::quiet_NaN(); }
			__forceinline operator float() const { return std::numeric_limits<float>::quiet_NaN(); }
		} CAN_NAN;

		static struct Epsilon
		{
			__forceinline operator double() const { return std::numeric_limits<double>::epsilon(); }
			__forceinline operator float() const { return std::numeric_limits<float>::epsilon(); }
		} CAN_EPSILON;

		static struct Pi
		{
			__forceinline operator double() const { return 3.14159265358979323846; }
			__forceinline operator float() const { return 3.14159265358979323846f; }
		} CAN_PI;

		static struct InvPi	// 1 / Pi
		{
			__forceinline operator double() const { return 0.31830988618379069122; }
			__forceinline operator float() const { return 0.31830988618379069122f; }
		} CAN_INV_PI;

		static struct TwoPi
		{
			__forceinline operator double() const { return 6.283185307179586232; }
			__forceinline operator float() const { return 6.283185307179586232f; }
		} CAN_TWO_PI;

		static struct PiOverTwo
		{
			__forceinline operator double() const { return 1.57079632679489661923; }
			__forceinline operator float() const { return 1.57079632679489661923f; }
		} CAN_PI_2;

		static struct InvTwoPi
		{
			__forceinline operator double() const { return 0.15915494309189534561; }
			__forceinline operator float() const { return 0.15915494309189534561f; }
		} CAN_INV_2PI;

		static struct FourPi
		{
			__forceinline operator double() const { return 12.566370614359172464; }
			__forceinline operator float() const { return 12.566370614359172464f; }
		} CAN_FOUR_PI;

		static struct PiOverFour
		{
			__forceinline operator double() const { return 0.785398163397448309616; }
			__forceinline operator float() const { return 0.785398163397448309616f; }
		} CAN_PI_4;

		static struct InvFourPi
		{
			__forceinline operator double() const { return 0.079577471545947672804; }
			__forceinline operator float() const { return 0.079577471545947672804f; }
		} CAN_INV_4PI;
	}
}



#endif // !CONSTANTS_H_
