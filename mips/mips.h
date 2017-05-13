#ifndef MIPS_H_
#define MIPS_H_

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class MIPS{
    public:
    class instructor;
    MIPS(string path);
    void convertToBinary(string path1 , string path2);
    void print();
    private:
    static bool cmp(instructor a , instructor b);
    vector<instructor> v;
    int binarySearch(string s);
    void binary(int n , vector<int>& t);
    void binary_16(int n , vector<int>& t);
    void binary_26(int n , vector<int>& t);
};

class MIPS::instructor{
    public:
    string type;
    string instructorName;
    vector<int> op;
    vector<int> func;
};

#endif

