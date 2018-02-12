#include <iostream>

using namespace std;

template<typename T>
bool equivalent(const T& a, const T& b)
{
	return !(a < b) && !(b < a);
}

template<typename T = int>
class bignum
{
	T _v;
public:
	bignum(T a) : _v(a) {}
	bool operator<(const bignum& b) const
	{
		return this->_v < b._v;
	}
};
#if 0
int main()
{
	bignum<> a(1), b(1); // ʹ��Ĭ�ϲ�����"<>"����ʡ��
	std::cout << equivalent(a, b) << '\n';
	cout << equivalent<double>(1, 1) << endl;
	return 0;
}
#endif