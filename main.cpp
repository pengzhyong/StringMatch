#include <iostream>
#include <string>
#include <cstring>
using  namespace std;
void GetNextval(const char* p, int next[]);
int sunday(string dest, string pattern);
int KMP(string s, string p);
int main() {
    string str="abcdbedabede";
    string pattern = "abed";
    cin >> str;
    cin >> pattern;
    cout << sunday(str, pattern) << endl;
    cout << KMP(str, pattern) << endl;
    cout << endl;
    return 0;
}
/**
 * KMP算法,顯性時間複雜度
 * @param p
 * @param next
 */
int KMP(string s, string p)
{
    int* next = new int[p.length()];
    GetNextval(p.c_str(), next);
    int i = 0, j = 0;
    // j is int type, and p.size() is unsigned type.
    // //when j < 0, always will be y > p.size(), causing a wrong result!
    while(i < s.size() && j < (int)p.size())
    {
        if(j==-1) i++;
        for (; i < s.size() && j < p.size() && s[i] == p[j]; i++, j++);
        if (j == p.size()) return i - j;
        j = next[j];
    }
    return -1;
}
void GetNextval(const char* p, int next[])
{
    unsigned int len = strlen(p);
    next[0] = -1;
    int j = 0, k = -1;
    while(j < len - 1)
    {
        if(k==-1 || p[j]==p[k])
        {
            ++j;
            ++k;
            next[j] = k;
        }
        else
            k = next[k];
    }
}
/**
 * Sunday算法
 * @param dest 主串
 * @param pattern 模式串
 * @returns {number} 匹配位置处 或 -1（无匹配）
 */
int sunday(string dest, string pattern) {

    int pos = 0, destLen = dest.length(), patternLen = pattern.length();

    //使用hash方法：用字符编码作为下标保存字符所在位置，这样可以直接得到相匹配的最右边的位置。
    int next[256];
    for (int i = 0; i < 256; i++){
        next[i] = -1;
    }
    for (int i = 0; i < patternLen; i++){
        next[pattern[i]] = i;
    }

    while (pos < destLen - patternLen + 1)
    {
        int i = pos, j = 0;
        for (; j < patternLen && i < destLen && dest[i] == pattern[j]; i++, j++);

        if (j == patternLen)
            return pos;
        else {
            if (pos + patternLen < destLen)
                pos += (patternLen - next[dest[pos + patternLen]]);
            else
                return -1;
        }
    }
    return -1;
}