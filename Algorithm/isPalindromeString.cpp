#include <string>
using namespace std;

bool isPalindrome(string s)
{
    int low = 0;
    int high = s.length() - 1;
    while(low < high)
    {
        if(s[low] != s[high])
            return false;
        low++;
        high--;
    }
    return true;
}