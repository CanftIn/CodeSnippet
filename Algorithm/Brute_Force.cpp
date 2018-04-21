/*
模式匹配之BF(Brute Force)暴力算法
*/
# include<iostream>
# include<string>

using namespace std;

int patternMatch_BF(string s,string t);
int BF(string s, string t);
int main()
{
    string s;
    string t;

    cout << "input main string:";
    cin >> s;
    cout << "input sub string:";
    cin >> t;

    int result = BF(s, t);
    if (result==-1)
        cout <<endl<< "match failed..." << endl;
    else cout << endl<<"the position of sub str in main str :" << result << endl;
    return 0;
}

int patternMatch_BF(string s, string t)//返回子串t在串s第一次出现的位置(从1开始)，若t不是s的子串
                                    //返回-1
{
    int i = 1, j = 1;
    while (i <=s.length()&& j <=t.length())//两个串都没扫描完
    {
        if (s[i-1] == t[j-1])//该位置上字符相等，就比较下一个字符
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2; //否则，i为上次扫描位置的下一位置
            j = 1; //j从1开始
        }

    }
    if (j > t.length())
        return (i - t.length());
    return -1;
}

int BF(string s, string t)
{
    int i = 0;
    int j = 0;
    int guard;
    for(; i <= s.length() - t.length(); ++i)
    {
        for(; j < t.length(); ++j)
        {
            if(s[i+j] != t[j])
                break;
        }
        if(j == t.length())
        {
            guard = i;
            return i;
        }
    }
    return -1;
}