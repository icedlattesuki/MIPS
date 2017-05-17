#ifndef _MIPS_INVERT_H
#define _MIPS_INVERT_H

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;

class MipsInvert{
  public:
    MipsInvert(string path);
    void Convert(string path1 , string path2);
  private:
    struct info{
        string type;
        string op;
        string name;
    };
    vector<info> r_ , i_ , j_;
    string BinarySearch(const vector<info> &v , string s);
    int BinaryStringToInt(string s);
    static bool cmp(info a , info b);
};

#endif