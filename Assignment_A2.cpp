#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

vector<string> split(string line){
    vector<string> result;
    stringstream st(line);
    string token;
    while(st >> token){
        result.push_back(token);
    }
    return result;
}

class MNTEntry
{
public:
    string name;
    int pp;
    int kp;
    int mdtp;
    int kpdtp;
    MNTEntry(string s="",int p=0,int k=0,int m=0,int kp=0){
        name = s;
        pp = p;
        kp = k;
        mdtp = m;
        kpdtp = kp;
    }
    int getPp() 
    {
        return pp;
    }
    int getKp()
    {
        return kp;
    }
    int getMdtp(){

        return mdtp;
    }
    int getKpdtp()
    {
        return kpdtp;
    }

};

int main()
{
    ifstream irb("intermediate.txt"),mdtb("mdt.txt"),mntb("mnt.txt"),kpdtb("kpdt.txt");
    ofstream out("pass2.txt");
    if(!irb.is_open() || !mdtb.is_open() || !mntb.is_open() || !kpdtb.is_open()){
        cerr << "Error in opening file " << endl;
        return 1;
    }
    vector<string>mdt,kpdt;
    unordered_map<string,MNTEntry> mnt;
    unordered_map<int,string> aptab;
    unordered_map<string,int> aptabInverse;
    string line;
    while (getline(mdtb,line))
    {
        mdt.push_back(line);
    }
    while (getline(kpdtb,line))
    {
        kpdt.push_back(line);
    }
    while (getline(mntb,line)) //mnt ka seperate
    {
        stringstream st(line);
        string name;
        int pp,kp,mdtp,kpdtp;
        st >> name >> pp >> kp >> mdtp >> kpdtp;
        mnt[name] = MNTEntry(name,pp,kp,mdtp,kpdtp);
    }
    while (getline(irb,line)) // remeber this chu
    {
        vector<string> parts = split(line);
        if(mnt.count(parts[0])){
            MNTEntry &entry = mnt[parts[0]];
            int kp = entry.getKp();
            int pp = entry.getPp();
            int kpdtp = entry.getKpdtp();
            int mdtp = entry.getMdtp();
            int paramno = 1;

            for (int i = 1; i <= pp && i < parts.size(); i++)
            {
                aptab[paramno] = parts[i];
                aptabInverse[parts[i]] = paramno++;
            }

            for(int i = kpdtp-1; i < kpdtp-1+kp && i < kpdt.size(); i++){
                stringstream st(kpdt[i]);
                string paramname,paramvalue;
                st >> paramname >> paramvalue;
                aptab[paramno] = paramvalue;
                aptabInverse[paramname] = paramno++;
            }
            for (int i = pp+1; i < parts.size(); i++)
            {
                if(parts[i].find("=") != string::npos){
                    int pos = parts[i].find("=");
                    string name = parts[i].substr(0,pos);
                    string value = parts[i].substr(pos+1);
                    if(aptabInverse.count(name)){
                        aptab[aptabInverse[name]] = value;
                    }
                }
            }
            for (int i = mdtp-1; i < mdt.size() && mdt[i] != "MEND"; i++)
            {
                stringstream st(mdt[i]);
                string token;
                out << "+";
                while (st >> token)
                {
                    if(token.find("(p,") != string::npos){ //small p remember here boi
                        int len = stoi(token.substr(3,token.find(")") - 3));
                        out << aptab[len] << " ";
                    }
                    else{
                        out << token << " ";
                    }
                }
                out << "\n";
            }
            aptab.clear();
            aptabInverse.clear();
        }
        else{
            out << line << endl;
        }
    }
    cout << "Pass 2 Completed !! " << endl;
    
    return 0;
}