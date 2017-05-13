#include "cpu.h"

int main() {
    Cpu test;
    cout << "+------------+-----------------------+" << endl;
    cout << "| instructor |       function        |" << endl;
    cout << "+------------+-----------------------+" << endl;
    cout << "|     R      |   check the register  |" << endl;
    cout << "+------------+-----------------------+" << endl;
    cout << "|     D      |   check the memory    |" << endl;
    cout << "+------------+-----------------------+" << endl;
    cout << "|     A      | insert assembly clause|" << endl;
    cout << "+------------+-----------------------+" << endl;
    cout << "|     T      |     run by step       |" << endl;
    cout << "+------------+-----------------------+" << endl;
    cout << "|     Q      |       quit            |" << endl;
    cout << "+------------+-----------------------+" << endl;
    while (1) {
        string instructor;
        cout << "please input the command" << endl;
        cin >> instructor;
        if (instructor == "R") 
            test.CheckRegister();
        else if (instructor == "D")
            test.CheckMemory();
        else if (instructor == "A")
            test.InsertInstructor();
        else if (instructor == "T")
            test.RunByStep();
        else if (instructor == "Q")
            break;
    }
    cout << "program quit" << endl;
}