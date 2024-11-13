#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

int count_pp = 0,count_kp =0, mdtp = 1, kpdtp = 1, macro_count = 0;
string mdt = "",mnt = "",pntab = "",kpdt = "",ic = "";

void createAndWriteToFile(const string&filename, const string& content){
    ofstream outfile(filename,ios::out);
    if(outfile.is_open()){
        outfile << content;
        outfile.close();
    }
    else{
        cerr << "Error in opening file : " << filename << endl;
    }
}

vector<string> split(const string& str, const char delimiter){
    vector<string>ans;
    stringstream st(str);
    string word;
    while (getline(st,word,delimiter))
    {
        ans.push_back(word);
    }
    return ans;
}

void process()
{
    bool IS_START = false,IS_MACRO = false;
    ifstream file("source.txt");
    if(!file.is_open()){
        cerr << "Error in opening source file !! " << endl;
        return;
    }
    string line;
    while(getline(file,line)){
        if(line.find("START") != string::npos || IS_START){
            ic += line + "\n";
            IS_START = true;
        }
        else
        {
            stringstream iss(line);
            vector<string>words;
            string word;

            while(iss >> word){
                word.erase(remove(word.begin(),word.end(),'&'),word.end());
                words.push_back(word);
            }

            if(IS_MACRO)
            {
                count_pp = 0;
                count_kp = 0;
                string macroname = words[0];
                pntab += macroname + "\t";
                vector<string>parameterList;

                for(size_t i = 1; i < words.size(); i++){
                    if(words[i].find("=") != string::npos)
                    {
                        count_kp++;
                        string parameter = words[i].substr(0,words[i].find("="));
                        string value = words[i].substr(words[i].find("=") + 1);
                        kpdt += parameter + "\t" + value + "\n";
                        pntab += parameter + "\t";
                        parameterList.push_back(parameter);
                    }
                    else{
                        count_pp++;
                        pntab += words[i] + "\t";
                        parameterList.push_back(words[i]);
                    }
                }

                pntab += "\n";

                string kpdt_value = (count_kp == 0) ? "----" : to_string(kpdtp);
                mnt += macroname + "\t" + to_string(count_pp) + "\t" + to_string(count_kp) + "\t" + to_string(mdtp) + "\t" + kpdt_value + "\n";
                kpdtp += count_kp;
                IS_MACRO = false; //remember this

            }
            else if(words[0] == "MACRO"){
                macro_count++;
                IS_MACRO = true;
            }
            else{
                string mdt_entry = words[0] + "\t";

                string parameter_str = split(pntab,'\n')[macro_count-1];
                vector<string>parameters = split(pntab,'\t');

                for(size_t i = 1; i < words.size(); i++){
                    auto it = find(parameters.begin() + 1,parameters.end(),words[i]);
                    if(it != parameters.end()){
                        int index = distance(parameters.begin(),it);
                        mdt_entry += "(P," + to_string(index) + ")\t"; 
                    }
                    else{
                        mdt_entry += words[i] + "\t";
                    }
                }
                mdtp++;
                mdt_entry += "\n";
                mdt += mdt_entry;
            }

        }
    }
    file.close();

    createAndWriteToFile("MDT.txt",mdt);
    createAndWriteToFile("MNT.txt",mnt);
    createAndWriteToFile("KPDT.txt",kpdt);
    createAndWriteToFile("PNTAB.txt",pntab);
    createAndWriteToFile("IC.txt",ic);

    cout << "Program for Pass 1 of Macro executed Successfully !! " << endl;
}

int main()
{
    process();
    return 0;
}