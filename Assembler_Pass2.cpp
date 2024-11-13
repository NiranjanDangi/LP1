#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
    
int main()
{
    ifstream sin("symbol_table.txt");
    ifstream lin("littab.txt");
    ifstream fin("testcase2.txt");
    ofstream fout("machineCode.txt");

    string line,word;
    vector<pair<string,int>>symtab;
    vector<pair<string,int>>littab;

    while (getline(sin,line))
    {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        symtab.push_back({label,stoi(word)}); 
    }
    sin.close();

    while (getline(lin,line))
    {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        littab.push_back({label,stoi(word)});
    }
    lin.close();

    int lc = -1;
    while (getline(fin,line))
    {
        stringstream st(line);
        st >> word;
        string cls = word.substr(1,2); // eg like : (AD,01) (DL,01)
        string mnemonic = word.substr(4,2);// eg like :    - this

        if(cls == "AD"){
            fout << "No Machine Code " << endl;
            if(mnemonic == "01"){ // START e.g : (AD,01) (C,100)
                st >> word;
                lc = stoi(word.substr(3,word.size()-4));
            }
            else if(mnemonic == "03"){ //ORIGIN e.g : (AD,03) (S,02)
                st >> word;
                int index = stoi(word.substr(4,1))-1;
                lc = symtab[index].second;

                size_t plus_pos = word.find('+');
                if(plus_pos != string::npos){
                    int icr = stoi(word.substr(plus_pos + 1));
                    lc += icr;
                }
            }
            continue;
        }

        if(cls == "IS"){ // (IS,01) (1) (S,02)
            fout << lc << " " << mnemonic << " ";
            lc++;

            if(mnemonic == "00"){
                fout << "0 000" << endl;
                continue;
            }

            st >> word;
            if(word[1] != 'S' && word[1] != 'L'){
                fout << word.substr(1,1) << " ";
                st >> word;
            }
            else{
                fout << "0 ";
            }

            int num = stoi(word.substr(4,1))-1;
            if(word[1] == 'S'){
                fout << symtab[num].second << endl;
            }
            else if(word[1] == 'L'){
                fout << littab[num].second << endl;
            }

        }
        else if(cls == "DL"){ //(DL,01) (C,1)
            fout << lc << " ";
            lc++;

            if(mnemonic == "01"){
                fout << "00 0" << " ";
                st >> word;
                fout << "00" << word.substr(3,1) << endl;
            }
            else if(mnemonic == "02"){
                fout << "No Machine Code " << endl;
            }

        }
    }
    fin.close();
    fout.close();
    cout << "Program for Pass 1 executed Successfully !! " << endl;
    return 0;
}