#pragma once

#include <string>
using namespace std;
//首先要定义hash函数与比较函数
class HashFunc
{
public:
    int operator()(const string & key )
    {
        int hash = 0;
        for(int i = 0; i < key.length(); ++i)
        {
            hash = hash << 7 ^ key[i];
        }
        return (hash & 0x7FFFFFFF);
    }
};


class EqualKey
{
public:
    bool operator()(const string & A, const string & B)
    {
        if (A.compare(B) == 0)
            return true;
        else
            return false;
    }
};