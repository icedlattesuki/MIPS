#ifndef _CPU_H
#define _CPU_H
#include "mips.h"
#include "mips_invert.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class Cpu {
  public:
    Cpu();
    void InsertInstructor();
    void RunByStep();
    void CheckRegister();
    void CheckMemory();
    void Convert();
    void Invert();
  private:
    vector<string> memory_;
    vector<string> register_;
    unsigned int PC_;
    unsigned int end_;
    string IR_;
    string DecimalToBinary32(int n);
    int BinaryToDecimalUnsigned(string s);
    int BinaryToDecimalSigned(string s);
    string BinaryToHexadecimal(string s);
    string ShiftLeftLogic(string s , unsigned int shamt);
    string ShiftRightLogic(string s , unsigned int shamt);
    string ShiftRightArithmetic(string s , unsigned int shamt);
    void Execute(string s);
    void Insert(string s);
};

#endif