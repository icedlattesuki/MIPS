#include "cpu.h"

// default constructor
Cpu::Cpu() {
    int i;
    for (i = 0; i < 5001; ++i) 
        memory_.push_back("00000000");
    string s = "";
    for (i = 0; i < 32; ++i) 
        s += "0";
    for (i = 0; i < 32; ++i) 
        register_.push_back(s);
    s = DecimalToBinary32(5001);
    register_[29] = s;
    PC_ = 0;
    end_ = 0;
    IR_ = "";
}

// insert an instructor into memory
void Cpu::InsertInstructor() {
    string s;
    cout << "please input the assembly clause." << endl;
    cout << "Input example: add $1,$2,$3" << endl;
    getchar();
    getline(cin , s);
    string op;
    int i = 0;
    while (s[i] != ' ') {
        op += s[i];
        i++;
    }
    if (op == "move" || op == "blt" || op == "bgt" || op == "ble" || op == "bge") {
        string rr;
        string rs;
        string rt;
        i++;
        while (s[i] != ',') {
            rs += s[i];
            i++;
        }
        i++;
        while (i < s.length() && s[i] != ',') {
            rt += s[i];
            i++;
        }
        i++;
        while (i < s.length() && s[i] != ',') {
            rr += s[i];
            i++;
        }
        if (op == "move") {
            string s1 = "add " + rs + "," + rt + ",$0";
            Insert(s1);
        }
        else if (op == "blt") {
            string s1 = "slt $1," + rs + "," + rt;
            Insert(s1);
            s1 = "bne $1,$0," + rr;
            Insert(s1);
        }
        else if (op == "bgt") {
            string s1 = "slt $1," + rt + "," + rs;
            Insert(s1);
            s1 = "bne $1,$0," + rr;
            Insert(s1);
        }
        else if (op == "ble") {
            string s1 = "slt $1," + rt + "," + rs;
            Insert(s1);
            s1 = "beq $1,$0," + rr;
            Insert(s1);
        }
        else if (op == "bge") {
            string s1 = "slt $1," + rs + "," + rt;
            Insert(s1);
            s1 = "beq $1,$0," + rr;
        }
    }
    else {
        Insert(s);
    }
    cout << "insert successfully!" << endl;
}

// run the program step by step
void Cpu::RunByStep() {
    IR_ = "";
    for (int i = 0; i < 4; ++i) {
        IR_ += memory_[PC_ + i];
    }
    PC_ += 4;
    Execute(IR_);
}

// show the 32 registers
void Cpu::CheckRegister() {
    for (int i = 0; i < 32; ++i) {
        cout << "+------------------+-----------------------+" << endl;
        cout << "|   Register" << i;
        if (i < 10)
            cout <<  "      |";
        else
            cout <<  "     |";
        string s = BinaryToHexadecimal(register_[i]);
        cout << "    0x" << s << "         |" << endl;
    }
    cout << "+------------------+-----------------------+" << endl;
}

// show the memory
void Cpu::CheckMemory() {
    cout << "PC: " << PC_ << endl;
    for (int i = 0; i < end_; ++i) {
        string s = DecimalToBinary32(i);
        s = BinaryToHexadecimal(s);
        cout << "+----------------+----------------+" << endl;
        cout << "|  0x" << s << "    |";
        cout << "   " << memory_[i] << "     |" << endl;
    }
    cout << "+----------------+----------------+" << endl;
}

void Cpu::Convert() {
    cout << "please input the assembly code" << endl;
    string s;
    getchar();
    getline(cin , s);
    MIPS mips("instructor");
    ofstream ofs("tmp_instructor");
    ofs << s;
    ofs.close();
    mips.convertToBinary("tmp_instructor" , "tmp_binary_code");
    ifstream ifs("tmp_binary_code");
    ifs >> s;
    ifs.close();
    cout << "the binary code is " << s << endl;
}
void Cpu::Invert() {
    cout << "please input the binary code" << endl;
    string s;
    getchar();
    getline(cin , s);
    MipsInvert mips_invert("info.txt");
    ofstream ofs("binary.txt");
    ofs << s;
    ofs.close();
    mips_invert.Convert("binary.txt" , "assemble.txt");
    ifstream ifs("assemble.txt");
    getline(ifs , s);
    ifs.close();
    cout << "the assembly code is " << s << endl;
}

// convert a decimal number to 32-bit binary string
string Cpu::DecimalToBinary32(int n) {
    vector<int> v;
    int flag = 0;
    if (n < 0) {
        flag = 1;
        n = -n;
    }
    while (n > 0) {
        v.push_back(n % 2);
        n /= 2;
    }
    string res = "";
    for (int i = 0; i < 32 - v.size(); ++i) {
        res += "0";
    }
    for (int i = v.size() - 1; i >= 0; --i) {
        res += v[i] + '0';
    }
    if (flag == 1) {
        string res1 = "";
        for (int i = 0; i < res.length(); ++i) {
            if (res[i] == '0')
                res1 += '1';
            else
                res1 += '0';
        }
        int carry = 1;
        for (int i = res1.length() - 1; i >= 0; --i) {
            int t = res1[i] - '0';
            t += carry;
            if (t > 1) {
                res1[i] = '0';
                carry = 1;
            }
            else {
                res1[i] = t + '0';
                break;
            }
        }
        return res1;
    }
    return res;
}

// convert a binary string to signed decimal
int Cpu::BinaryToDecimalSigned(string s) {
    int flag = 0;
    if (s[0] == 1) {
        flag = 1;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '0')
                s[i] = '1';
            else
                s[i] = '0';
        }
        int carry = 0;
        for (int i = s.length() - 1; i >= 0; --i) {
            int t = s[i] - '0';
            t = t + carry;
            if (t > 1) {
                s[i] = 0;
                carry = 1;
            }
            else{
                s[i] = t;
                carry = 0;
            }
        }
    }
    int res = 0;
    for (int i = 1; i < s.length(); ++i) {
        res = res * 2 + s[i] - '0';
    }
    if (flag == 1)
        res = -res;
    return res;
}

// convert a binary string to unsigned decimal
int Cpu::BinaryToDecimalUnsigned(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); ++i) {
        res = res * 2 + s[i] - '0';
    }
    return res;
}

// convert a binary string to hexadecimal string
string Cpu::BinaryToHexadecimal(string s) {
    string res = "";
    for (int i = 0; i < s.length(); i = i + 4) {
        int t = 0;
        for (int j = 0; j < 4; ++j) {
            t = t * 2 + s[i + j] - '0';
        }
        if (t < 10)
            res += t + '0';
        else
            res += t - 10 + 'A';
    }
    return res;
}

// shift left logiclly
string Cpu::ShiftLeftLogic(string s , unsigned int shamt) {
    for (int i = 0; i < shamt; ++i) {
        for (int j = 0; j < s.length() - 1; ++j) {
            s[j] = s[j + 1];
        }
        s[s.length() - 1] = '0';
    }
    return s;
}

// shift right logiclly
string Cpu::ShiftRightLogic(string s , unsigned int shamt) {
    for (int i = 0; i < shamt; ++i) {
        for (int j = s.length() - 1; j > 0; --j) {
            s[j] = s[j - 1];
        }
        s[0] = '0';
    }
    return s;
}

// shift right arithmetic
string Cpu::ShiftRightArithmetic(string s , unsigned int shamt) {
    char c = s[0];
    for (int i = 0; i < shamt; ++i) {
        for (int j = s.length() - 1; j > 0; --j) {
            s[j] = s[j - 1];
        }
        s[0] = c;
    }
    return s;
}

// execute module (core module)
void Cpu::Execute(string s) {
    int rs = BinaryToDecimalUnsigned(s.substr(6 , 5));
    int rt = BinaryToDecimalUnsigned(s.substr(11 , 5));
    int rd = BinaryToDecimalUnsigned(s.substr(16 , 5));
    int shamt = BinaryToDecimalSigned(s.substr(21 , 5));
    int imm = BinaryToDecimalSigned(s.substr(16 , 16));
    int t1 = BinaryToDecimalSigned(register_[rs]);
    int t2 = BinaryToDecimalSigned(register_[rt]);
    int t3 = BinaryToDecimalUnsigned(register_[rs]);
    int address = t3 + imm;
    string op = s.substr(0 , 6);
    // R-type instruction
    if (op == "000000") {
        string func = s.substr(26 , 6);
        // add
        if (func == "100000") {
            register_[rd] = DecimalToBinary32(t1 + t2);
        }   
        // addu
        else if (func == "100001") {
            t1 = BinaryToDecimalUnsigned(register_[rs]);
            t2 = BinaryToDecimalUnsigned(register_[rt]);
            register_[rd] = DecimalToBinary32(t1 + t2);
        }
        // sub
        else if (func == "100010") {
            register_[rd] = DecimalToBinary32(t1 - t2);
        }
        // subu
        else if (func == "100011") {
            t1 = BinaryToDecimalUnsigned(register_[rs]);
            t2 = BinaryToDecimalUnsigned(register_[rt]);
            register_[rd] = DecimalToBinary32(t1 - t2);
        }
        // and
        else if (func == "100100") {
            register_[rd] = DecimalToBinary32(t1 & t2);
        }
        // or
        else if (func == "100101") {
            register_[rd] = DecimalToBinary32(t1 | t2);
        }
        // xor
        else if (func == "100110") {
            register_[rd] = DecimalToBinary32(t1 ^ t2);
        }
        // nor
        else if (func == "100111") {
            register_[rd] = DecimalToBinary32(~(t1 | t2));
        }
        // slt
        else if (func == "101010") {
            register_[rd] = DecimalToBinary32(t1 < t2 ? 1 : 0);
        }
        // sltu
        else if (func == "101011") {
            t1 = BinaryToDecimalUnsigned(register_[rs]);
            t2 = BinaryToDecimalUnsigned(register_[rt]);
            register_[rd] = DecimalToBinary32(t1 < t2 ? 1 : 0);
        }
        // sll
        else if (func == "000000") {
            register_[rd] = ShiftLeftLogic(register_[rt] , shamt);
        }
        // srl
        else if (func == "000010") {
            register_[rd] = ShiftRightLogic(register_[rt] , shamt);
        }
        // sra
        else if (func == "000011") {
            register_[rd] = ShiftRightArithmetic(register_[rt] , shamt);
        }
        // sllv
        else if (func == "000100") {
            t1 = BinaryToDecimalUnsigned(register_[rs]);
            register_[rd] = ShiftLeftLogic(register_[rt] , t1);
        }
        // srlv
        else if (func == "000110") {
            t1 = BinaryToDecimalUnsigned(register_[rs]);
            register_[rd] = ShiftRightLogic(register_[rt] , t1);
        }
        // srav
        else if (func == "000111") {
            t1 = BinaryToDecimalUnsigned(register_[rs]);
            register_[rd] = ShiftRightArithmetic(register_[rt] , t1);
        }
        // jr
        else if (func == "001000") {
            PC_ = BinaryToDecimalUnsigned(register_[rs]);
        }
    }
    // addi
    else if (op == "001000") {
        register_[rt] = DecimalToBinary32(t1 + imm);
    }
    // addiu
    else if (op == "001001") {
        t1 = BinaryToDecimalUnsigned(register_[rs]);
        register_[rt] = DecimalToBinary32(t1 + imm);
    }
    // andi
    else if (op == "001100") {
        register_[rt] = DecimalToBinary32(t1 & imm);
    }
    // ori
    else if (op == "001101") {
        register_[rt] = DecimalToBinary32(t1 | imm);
    }
    // xori
    else if (op == "001110") {
        register_[rt] = DecimalToBinary32(t1 ^ imm);
    }
    // lw
    else if (op == "100011") {
        register_[rt] = "";
        for (int i = 0; i< 4; ++i) {
            register_[rt] += memory_[address + i];
        }
    }
    // sw
    else if (op == "101011") {
        for (int i = 0; i < 4; ++i) {
            memory_[address + i] = register_[rt].substr(8 * i , 8);
        }
    }
    // beq
    else if (op == "000100") {
        if (t1 == t2) {
            PC_ = PC_ + imm * 4;
        }
    }
    // bne
    else if (op == "000101") {
        if (t1 != t2) {
            PC_ = PC_ + imm * 4;
        }
    }
    // slti
    else if (op == "001010") {
        register_[rt] = DecimalToBinary32(t1 < imm ? 1 : 0);
    }
    // sltiu
    else if (op == "001011") {
        t1 = BinaryToDecimalUnsigned(register_[rs]);
        register_[rt] = DecimalToBinary32(t1 < imm ? 1 : 0);
    }
    // j and jal
    else if (op == "000010" || op == "000011") {
        string address = s.substr(6 , 26) + "00";
        string pc = DecimalToBinary32(PC_);
        address = pc.substr(0 , 4) + address;
        PC_ = BinaryToDecimalUnsigned(address);
        // jal
        if (op == "000011")
            register_[31] = DecimalToBinary32(PC_);
    }
}

void Cpu::Insert(string s) {
    ofstream ofs("tmp_instructor");
    ofs << s;
    ofs.close();
    MIPS m("instructor");
    m.convertToBinary("tmp_instructor" , "tmp_binary_code");
    ifstream ifs("tmp_binary_code");
    ifs >> s;
    ifs.close();
    for (int i = 0; i < 4; ++i) {
        memory_[end_ + i] = s.substr(8 * i , 8);
    }
    end_ += 4;
}