#include<iostream>
#include<stdio.h>
#include<string>
#include<codecvt>
#include<windows.h>
#include<locale>

using namespace std;

//utf8转string，不是gbk格式
const std::string UTF8_To_string(const std::string & str)
{
int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
 
wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
memset(pwBuf, 0, nwLen * 2 + 2);
 
MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
 
int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
 
char * pBuf = new char[nLen + 1];
memset(pBuf, 0, nLen + 1);
 
WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
 
std::string retStr = pBuf;
 
delete []pBuf;
delete []pwBuf;
 
pBuf = NULL;
pwBuf = NULL;
 
return retStr;
}
//gbk转utf8，输出为utf8格式的字符串
string GBKToUTF8(const std::string& strGBK)
{
    string strOutUTF8 = "";
    WCHAR * str1;
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char * str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[]str1;
    str1 = NULL;
    delete[]str2;
    str2 = NULL;
    return strOutUTF8;
}
//gbk转utf8格式，输出为gbk格式的字符串
string UTF8ToGBK(const std::string& strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
    unsigned short * wszGBK = new unsigned short[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, (LPCCH)strUTF8.c_str(), -1, reinterpret_cast<LPWSTR>(wszGBK), len);

    len = WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<LPCWCH>(wszGBK), -1, NULL, 0, NULL, NULL);
    char *szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP,0, reinterpret_cast<LPCWCH>(wszGBK), -1, szGBK, len, NULL, NULL);
    //strUTF8 = szGBK;
    std::string strTemp(szGBK);
    delete[]szGBK;
    delete[]wszGBK;
    return strTemp;
}

//c++11提供的宽字符转utf8，没有转gbk功能；
std::string wstringToUtf8(const std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > strCnv;
    return strCnv.to_bytes(str);
}

//c++11提供的utf8转宽字符
std::wstring utf8ToWstring(const std::string& str)
{
    std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
    return strCnv.from_bytes(str);
}