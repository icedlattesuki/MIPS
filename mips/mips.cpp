#include"mips.h"

MIPS::MIPS(string path){
    ifstream file(path);
    string type;
    string name;
    string op , func;

    while(file >> type){
        instructor tmp;
        if(type == "R"){
            file >> name >> op >> func;
            tmp.type = type;
            tmp.instructorName = name;
            for(int i = 0;i < op.length();i++){
                tmp.op.push_back(op[i] - '0');
            }
            for(int i = 0;i < func.length();i++){
                tmp.func.push_back(func[i] - '0');
            }
        }
        else{
            file >> name >> op;
            tmp.type = type;
            tmp.instructorName = name;
            for(int i = 0;i < op.length();i++){
                tmp.op.push_back(op[i] - '0');
            }
        }
        v.push_back(tmp);
    }
    sort(v.begin() , v.end() , MIPS::cmp);
}

void MIPS::convertToBinary(string path1 , string path2){
    ifstream ifs(path1);
    ofstream ofs(path2);
    string s1 , s2;

    while(ifs >> s1 >> s2){
        vector<int> res(32);
        int index = binarySearch(s1);
        s2 += '\n';
        if(v[index].type == "R"){
            for(int i = 0;i < 6;i++){
                res[i] = 0;
                res[26 + i] = v[index].func[i];
            }
            if(s1 == "sll" || s1 == "srl" || s1 == "sra"){
                for(int i = 6;i <= 10;i++)
                    res[i] = 0;
                int flag = 0;
                for(int i = 0;i < s2.length();i++){
                    if(s2[i] == '$'){
                        string s;
                        while(s2[++i] != ','){
                            s += s2[i];
                        }
                        vector<int> tmp;
                        int n = stoi(s);
                        binary(n , tmp);
                        if(flag == 0){
                            for(int j = 0;j < 5;j++){
                                res[j + 16] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 1;
                        }
                        else{
                            for(int j = 0;j < 5;j++){
                                res[j + 11] = tmp[tmp.size() - 1 - j];
                            }
                        }
                    }
                    else{
                        string s;
                        s += s2[i];
                        while(s2[++i] != '\n'){
                            s += s2[i];
                        }
                        vector<int> tmp;
                        int n = stoi(s);
                        binary(n , tmp);
                        for(int j = 0;j < 5;j++){
                            res[21 + j] = tmp[tmp.size() - 1 - j];
                        }
                    }
                }
            }
            else if(s1 == "sllv" || s1 == "srlv" || s1 == "srav"){
                for(int i = 0;i < 5;i++){
                    res[i + 21] = 0;
                }
                int flag = 0;
                for(int i = 0;i < s2.length();i++){
                    if(s2[i] == '$'){
                        string s;
                        while(s2[++i] != ',' && s2[i] != '\n'){
                            s += s2[i];
                        }
                        int n = stoi(s);
                        vector<int> tmp;
                        binary(n , tmp);
                        if(flag == 0){
                            for(int j = 0;j < 5;j++){
                                res[j + 16] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 1;
                        }
                        else if(flag == 1){
                            for(int j = 0;j < 5;j++){
                                res[j + 11] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 2;
                        }
                        else{
                            for(int j = 0;j < 5;j++){
                                res[j + 6] = tmp[tmp.size() - 1 - j];
                            }
                        }
                    }
                }
            }
            else if(s1 == "jr"){
                string s;
                for(int j = 1;j < s2.length();j++){
                    s += s2[j];
                }
                int n = stoi(s);
                vector<int> tmp;
                binary(n , tmp);
                for(int j = 0;j < 5;j++){
                    res[6 + j] = tmp[tmp.size() - 1 - j];
                }
                for(int j = 0;j < 15;j++){
                    res[11 + j] = 0;
                }
            }
            else{
                for(int i = 0;i < 5;i++){
                    res[i + 21] = 0;
                }
                int flag = 0;
                for(int i = 0;i < s2.length();i++){
                    if(s2[i] == '$'){
                        string s;
                        while(s2[++i] != ',' && s2[i] != '\n'){
                            s += s2[i];
                        }
                        int n = stoi(s);
                        vector<int> tmp;
                        binary(n , tmp);
                        if(flag == 0){
                            for(int j = 0;j < 5;j++){
                                res[j + 16] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 1;
                        }
                        else if(flag == 1){
                            for(int j = 0;j < 5;j++){
                                res[j + 6] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 2;
                        }
                        else{
                            for(int j = 0;j < 5;j++){
                                res[j + 11] = tmp[tmp.size() - 1 - j];
                            }
                        }
                    }
                }
            }   
        }
        else if(v[index].type == "I"){
            for(int i = 0;i < 6;i++){
                res[i] = v[index].op[i];
            }
            if(s1 == "lui"){
                for(int i = 0;i < 6;i++){
                    res[6 + i] = 0; 
                }
                for(int i = 0;i < s2.length();i++){
                    if(s2[i] == '$'){
                        string s;
                        while(s2[++i] != ','){
                            s += s2[i];
                        }
                        int n = stoi(s);
                        vector<int> tmp;
                        binary(n , tmp);
                        for(int j = 0;j < 5;j++){
                            res[11 + j] = tmp[tmp.size() - 1 - j];
                        }
                    }
                    else{
                        string s;
                        s += s2[i];
                        while(s2[++i] != '\n'){
                            s += s2[i];
                        }
                        int n = stoi(s);
                        vector<int> tmp;
                        binary_16(n , tmp);
                        for(int j = 0;j < 16;j++){
                            res[16 + j] = tmp[tmp.size() - 1 - j];
                        }
                    }
                }
            }
            else if(s1 == "lw" || s1 == "sw"){
                int flag = 0;
                for(int i = 0;i < s2.length() && s2[i] != '\n';i++){
                    if(s2[i] == '$'){
                        string s;
                        while(s2[++i] != ',' && s2[i] != ')'){
                            s += s2[i];
                        }
                        int n = stoi(s);
                        vector<int> tmp;
                        binary(n , tmp);
                        if(flag == 0){
                            for(int j = 0;j < 5;j++){
                                res[11 + j] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 1;
                        }
                        else{
                            for(int j = 0;j < 5;j++){
                                res[6 + j] = tmp[tmp.size() - 1 - j];
                            }
                        }
                    }
                    else{
                        string s;
                        s += s2[i];
                        while(s2[++i] != '('){
                            s += s2[i];
                        }
                        int n = stoi(s);
                        vector<int> tmp;
                        binary_16(n , tmp);
                        for(int j = 0;j < 16;j++){
                            res[16 + j] = tmp[tmp.size() - 1 - j];
                        }
                    }
                }
            }
            else if(s1 == "beq" || s2 == "bne"){
                int flag = 0;
                for(int i = 0;i < s2.length();i++){
                    if(s2[i] == '$'){
                        string s;
                        while(s2[++i] != ','){
                            s += s2[i];
                        }
                        vector<int> tmp;
                        int n = stoi(s);
                        binary(n , tmp);
                        if(flag == 0){
                            for(int j = 0;j < 5;j++){
                                res[j + 6] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 1;
                        }
                        else{
                            for(int j = 0;j < 5;j++){
                                res[j + 11] = tmp[tmp.size() - 1 - j];
                            }
                        }
                    }
                    else{
                        string s;
                        s += s2[i];
                        while(s2[++i] != '\n'){
                            s += s2[i];
                        }
                        vector<int> tmp;
                        int n = stoi(s);
                        binary_16(n , tmp);
                        for(int j = 0;j < 16;j++){
                            res[16 + j] = tmp[tmp.size() - 1 - j];
                        }
                    }
                }
            }
            else{
                int flag = 0;
                for(int i = 0;i < s2.length();i++){
                    if(s2[i] == '$'){
                        string s;
                        while(s2[++i] != ','){
                            s += s2[i];
                        }
                        vector<int> tmp;
                        int n = stoi(s);
                        binary(n , tmp);
                        if(flag == 0){
                            for(int j = 0;j < 5;j++){
                                res[j + 11] = tmp[tmp.size() - 1 - j];
                            }
                            flag = 1;
                        }
                        else{
                            for(int j = 0;j < 5;j++){
                                res[j + 6] = tmp[tmp.size() - 1 - j];
                            }
                        }
                    }
                    else{
                        string s;
                        s += s2[i];
                        while(s2[++i] != '\n'){
                            s += s2[i];
                        }
                        vector<int> tmp;
                        int n = stoi(s);
                        binary_16(n , tmp);
                        for(int j = 0;j < 16;j++){
                            res[16 + j] = tmp[tmp.size() - 1 - j];
                        }
                    }
                }
            }
        }
        else{
            string s;
            for(int i = 0;i < s2.length() - 1;i++)
                s += s2[i];
            int n = stoi(s);
            vector<int> tmp;
            binary_26(n , tmp);
            for(int i = 0;i < 26;i++){
                res[6 + i] = tmp[tmp.size() - 1 - i];
            }
        }

        for(int i = 0;i < res.size();i++){
            ofs << res[i];
        }
        ofs << '\n';
    }
    ifs.close();
    ofs.close();
}

void MIPS::binary(int n , vector<int>& t){
    while(n != 0){
        t.push_back(n % 2);
        n /= 2;
    }
    while(t.size() < 5){
        t.push_back(0);
    }
}

void MIPS::binary_16(int n , vector<int>& t){
    while(n != 0){
        t.push_back(n % 2);
        n /= 2;
    }
    while(t.size() < 16){
        t.push_back(0);
    }
}

void MIPS::binary_26(int n , vector<int>& t){
    while(n != 0){
        t.push_back(n % 2);
        n /= 2;
    }
    while(t.size() < 26){
        t.push_back(0);
    }
}

bool MIPS::cmp(instructor a , instructor b){
    return a.instructorName < b.instructorName;
}

int MIPS::binarySearch(string s){
    int start = 0 , end = v.size() - 1;
    int mid;

    while(start <= end){
        mid = (start + end) / 2;
        if(v[mid].instructorName == s)
            return mid;
        else if(v[mid].instructorName < s)
            start = mid + 1;
        else
            end = mid - 1;
    }  
    return -1; 
}

void MIPS::print(){
    for(int i = 0;i < v.size();i++){
        cout << v[i].type << " " << v[i].instructorName << " ";
        if(v[i].type == "R"){
            for(int j = 0;j < v[i].func.size();j++)
                cout << v[i].func[j];
        }
        else{
            for(int j = 0;j < v[i].op.size();j++)
                cout << v[i].op[j];
        }
        cout << endl;
    }
}