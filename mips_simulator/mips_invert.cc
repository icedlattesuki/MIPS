#include"mips_invert.h"

MipsInvert::MipsInvert(string path){
    ifstream ifs(path);
    info tmp;
    while (!ifs.eof()) {
        ifs >> tmp.type >> tmp.name >> tmp.op;
        if (tmp.type == "R")
            r_.push_back(tmp);
        else if (tmp.type == "I")
            i_.push_back(tmp);
        else
            j_.push_back(tmp);
    }
    ifs.close();
    sort(r_.begin() , r_.end() , cmp);
    sort(i_.begin() , i_.end() , cmp);
    sort(j_.begin() , j_.end() , cmp);
}

void MipsInvert::Convert(string path1 , string path2){
    ifstream ifs(path1);
    ofstream ofs(path2);
    while (!ifs.eof()) {
        string s;
        ifs >> s;
        string op = s.substr(0 , 6);
        if (op == "000000") {
            string instructor_name = BinarySearch(r_ , s.substr(26 , 6));
            string rs , rt , rd , shamt;
            rs = s.substr(6 , 5);
            rt = s.substr(11 , 5);
            rd = s.substr(16 , 5);
            shamt = s.substr(21 , 5);
            ofs << instructor_name << " $";
            if (instructor_name == "sll" || instructor_name == "srl" || instructor_name == "sra")
                ofs << BinaryStringToInt(rd) << ",$" << BinaryStringToInt(rt) << "," << BinaryStringToInt(shamt) << endl;
            else if (instructor_name == "sllv" || instructor_name == "srlv" || instructor_name == "srav")
                ofs << BinaryStringToInt(rd) << ",$" << BinaryStringToInt(rt) << ",$" << BinaryStringToInt(rs) << endl;
            else if (instructor_name == "jr")
                ofs << BinaryStringToInt(rs) << endl;
            else
                ofs << BinaryStringToInt(rd) << ",$" << BinaryStringToInt(rs) << ",$" << BinaryStringToInt(rt) << endl;
        }
        else if (op == "000010" || op == "000011") {
            string instructor_name = BinarySearch(j_ , op);
            string address = s.substr(6 , 26);
            ofs << instructor_name << " " << BinaryStringToInt(address) << endl;
        }
        else {
            string instructor_name = BinarySearch(i_ , op);
            string rs , rt , immediate;
            rs = s.substr(6 , 5);
            rt = s.substr(11 , 5);
            immediate = s.substr(16 , 16);
            ofs << instructor_name << " $";
            if (instructor_name == "lui")
                ofs << BinaryStringToInt(rt) << "," << BinaryStringToInt(immediate) << endl;
            else if (instructor_name == "lw" || instructor_name == "sw")
                ofs << BinaryStringToInt(rt) << "," << BinaryStringToInt(immediate) << "($" << BinaryStringToInt(rs) << ")" << endl;
            else if (instructor_name == "beq" || instructor_name == "bne")
                ofs << BinaryStringToInt(rs) << ",$" << BinaryStringToInt(rt) << "," << BinaryStringToInt(immediate) << endl;
            else
                ofs << BinaryStringToInt(rt) << ",$" << BinaryStringToInt(rs) << "," << BinaryStringToInt(immediate) << endl;
        }
    }

    ifs.close();
    ofs.close();
}

bool MipsInvert::cmp(info a , info b){
    return a.op < b.op;
}

string MipsInvert::BinarySearch(const vector<info> &v , string s){
    int start = 0 , end = v.size() - 1;
    while(start <= end){
        int mid = (start + end) / 2;
        if (v[mid].op == s)
            return v[mid].name;
        else if (v[mid].op < s)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return "";
}

int MipsInvert::BinaryStringToInt(string s){
    int res = 0;
    for (int i = 0; i < s.length();++i){
        res = res * 2 + (s[i] - '0');
    }
    return res;
}


