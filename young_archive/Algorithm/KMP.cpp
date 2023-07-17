#include<iostream>
#include<string>
using namespace std;

/* P为模式串，下标从0开始 */
void GetNext(string P, int next[])
{
    int p_len = P.size();
    int i = 0;   //P的下标
    int j = -1;  
    next[0] = -1;

    while (i < p_len)
    {
        if (j == -1 || P[i] == P[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

/* 在S中找到P第一次出现的位置 */
int KMP(string S, string P, int next[])
{
    GetNext(P, next);

    int i = 0;  //S的下标
    int j = 0;  //P的下标
    int s_len = S.size();
    int p_len = P.size();

    while (i < s_len && j < p_len)
    {
        if (j == -1 || S[i] == P[j])  //P的第一个字符不匹配或S[i] == P[j]
        {
            i++;
            j++;
        }
        else
            j = next[j];  //当前字符匹配失败，进行跳转
    }

    if (j == p_len)  //匹配成功
        return i - j;
    
    return -1;
}

int main()
{
    int next[100] = { 0 };

    cout << KMP("bbc abcdab abcdabcdabde", "abcdabd", next) << endl; //15
    
    return 0;
}