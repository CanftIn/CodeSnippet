#include <string>
#include <stdio.h>
#include <Windows.h>

struct C {
#if 1
	static const inline std::string N{ "abc" };
};
#else
	static std::string& N() {
		static std::string s{ "abc" };
		return s;
	}
};
#endif
#if 0
int main()
{
	printf("%s\n", C::N.c_str());

	system("pause");
}
#endif