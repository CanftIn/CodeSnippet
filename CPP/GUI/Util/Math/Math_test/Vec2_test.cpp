#include "../Vec2.h"

// !!! before test：annotate __forceinline in Constants.h when using gcc/clang

using namespace std;
using namespace CAN;
#if 0
int main()
{
    Vector2 vec2_zero;
    Vector2 vec2(10, 20);
    Vector2 vec2_equalxy(30);
    Vector2 vec2_copy_1(vec2);
    Vector2 vec2_copy_2(vec2_equalxy);
    Vector2i vec2_i(1, 2);
    Vector2b vec2_b(true, false);
    Vector2 vec2_copy_3(vec2_i);
    Vector2 vec2_copy_4 = vec2;

    cout << "vec2_zero             :  " << vec2_zero                  << endl;
    cout << "vec2                  :  " << vec2                       << endl;
    cout << "vec2_equalxy          :  " << vec2_equalxy               << endl;
    cout << "vec2_copy_1           :  " << vec2_copy_1                << endl;
    cout << "vec2_copy_2           :  " << vec2_copy_2                << endl;
    cout << "vec2_i                :  " << vec2_i                     << endl;
    cout << "vec2_b                :  " << vec2_b                     << endl;
    cout << "vec2_copy_3           :  " << vec2_copy_3                << endl;
    cout << "vec2[0]               :  " << vec2[0]                    << endl;
    cout << "vec2[1]               :  " << vec2[1]                    << endl;
    cout << "vec2_copy_4           :  " << vec2_copy_4                << endl;
    cout << "vec2.Sum()            :  " << vec2.Sum()                 << endl;
    cout << "vec2.Product()        :  " << vec2.Product()             << endl;
    cout << "vec2 + vec2_equalxy   :  " << vec2 + vec2_equalxy        << endl;
    cout << "vec2 - vec2_equalxy   :  " << vec2 - vec2_equalxy        << endl;
    cout << "vec2 / vec2_equalxy   :  " << vec2 / vec2_equalxy        << endl;
    cout << "vec2 * vec2_equalxy   :  " << vec2 * vec2_equalxy        << endl;
    cout << "vec2 + vec2_b         :  " << vec2 + vec2_b              << endl;
    cout << "vec2 - vec2_b         :  " << vec2 - vec2_b              << endl;
    cout << "vec2 / vec2_b         :  " << vec2 / vec2_b              << endl;
    cout << "vec2 * vec2_b         :  " << vec2 * vec2_b              << endl;
    cout << "vec2 + vec2_i         :  " << vec2 + vec2_i              << endl;
    cout << "vec2 - vec2_i         :  " << vec2 - vec2_i              << endl;
    cout << "vec2 / vec2_i         :  " << vec2 / vec2_i              << endl;
    cout << "vec2 * vec2_i         :  " << vec2 * vec2_i              << endl;
}
#endif