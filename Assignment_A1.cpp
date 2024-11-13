#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    map<string, pair<string, string>> opcode;
    opcode["STOP"] = {"IS", "00"};
    opcode["ADD"] = {"IS", "01"};
    opcode["SUB"] = {"IS", "02"};
    opcode["MUL"] = {"IS", "03"};
    opcode["MOVER"] = {"IS", "04"};
    opcode["MOVEM"] = {"IS", "05"};
    opcode["COMP"] = {"IS", "06"};
    opcode["BC"] = {"IS", "07"};
    opcode["DIV"] = {"IS", "08"};
    opcode["READ"] = {"IS", "09"};
    opcode["PRINT"] = {"IS", "10"};

    opcode["START"] = {"AD", "01"};
    opcode["END"] = {"AD", "02"};
    opcode["ORIGIN"] = {"AD", "03"};
    opcode["EQU"] = {"AD", "04"};
    opcode["LTORG"] = {"AD", "05"};

    opcode["DC"] = {"DL", "01"};
    opcode["DS"] = {"DS", "02"};

    opcode["AREG"] = {"1", ""};
    opcode["BREG"] = {"2", ""};
    opcode["CREG"] = {"3", ""};
    opcode["DREG"] = {"4", ""};

    opcode["LT"] = {"1", ""};
    opcode["LE"] = {"2", ""};
    opcode["EQ"] = {"3", ""};
    opcode["GT"] = {"4", ""};
    opcode["GE"] = {"5", ""};
    opcode["ANY"] = {"6", ""};

    string line, word;
    map<string, pair<int, string>> symtab;
    vector<pair<string, int>> littab;
    vector<string> pooltab;

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int lc = -1;
    int litindex = 0;
    while (getline(fin, line))
    {
        stringstream st(line);
        st >> word;
        string label = "";

        if (opcode.count(word) == 0)
        {
            if (symtab.count(word) == 0)
            {
                symtab[word] = {lc, to_string(symtab.size() + 1)};
            }
            else
            {
                symtab[word].first = lc;
            }
            label = word;
            st >> word;
        }

        string operation = word;
        if (operation == "START")
        {
            fout << "";
            fout << "(" << opcode[word].first << "," << opcode[word].second << ") ";
            st >> word;

            if (!word.empty() && all_of(word.begin(), word.end(), ::isdigit))
            {
                fout << "(C," << word << ") ";
                lc = stoi(word);
            }
            else
            {
                cout << "Error : Invalid input format for START Operation " << endl;
                return 1;
            }
        }
        else if (operation == "END")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << "," << opcode[word].second << ") ";
            fout << endl;
            pooltab.push_back("#" + to_string(litindex + 1));
            for (; litindex < littab.size(); litindex++)
            {
                fout << lc << " ";
                fout << "(" << opcode["DC"].first << "," << opcode["DC"].second << ") ";
                littab[litindex].second = lc;
                string literal = littab[litindex].first;
                fout << "(C," << literal.substr(2, literal.length() - 3) << ")\n";
                lc++;
            }
        }
        else if (operation == "LTORG")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << "," << opcode[word].second << ") ";
            fout << endl;
            pooltab.push_back("#" + to_string(litindex + 1));
            for (; litindex < littab.size(); litindex++)
            {
                fout << lc << " ";
                fout << "(" << opcode["DC"].first << "," << opcode["DC"].second << ") ";
                littab[litindex].second = lc;
                string literal = littab[litindex].first;
                fout << "(C," << literal.substr(2, literal.length() - 3) << ")\n";
                lc++;
            }
        }
        else if (operation == "EQU")
        {
            fout << "    ";
            fout << "No IC Generated";
            fout << endl;
            st>> word; // next word lo priye
            int plusminusIndex = 0;
            for (int i = 0; i < word.length(); i++)
            {
                if (word[i] == '+' || word[i] == '-')
                {
                    plusminusIndex = i;
                    break;
                }
            }
            char plusminus = '0';
            string before;
            string after;
            if (plusminusIndex != 0)
            {
                plusminus = word[plusminusIndex];
                before = word.substr(0, plusminusIndex);
                after = word.substr(plusminusIndex + 1);
            }
            else
            {
                before = word.substr(0, word.length());
            }
            symtab[label].first = symtab[before].first;
            if (!after.empty() && all_of(after.begin(), after.end(), ::isdigit))
            {
                if (plusminus == '+')
                {
                    symtab[label].first += stoi(after);
                }
                else if (plusminus == '-')
                {
                    symtab[label].first -= stoi(after);
                }
            }
        }
        else if (operation == "ORIGIN")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << "," << opcode[word].second << ") ";
            int plusminusIndex = 0;
            st >> word; //next word lo priye
            for (int i = 0; i < word.length(); i++)
            {
                if (word[i] == '+' || word[i] == '-')
                {
                    plusminusIndex = i;
                    break;
                }
            }
            char plusminus = '0';
            string before;
            string after;
            if (plusminusIndex != 0)
            {
                plusminus = word[plusminusIndex];
                before = word.substr(0, plusminusIndex);
                after = word.substr(plusminusIndex + 1);
            }
            else
            {
                before = word.substr(0, word.length());
            }
            lc = symtab[before].first;
            fout << "(S," << symtab[before].second << ") "; //remeber here boy before
            if (!after.empty() && all_of(after.begin(), after.end(), ::isdigit)) //also after here
            {
                if (plusminus == '+')
                {
                    lc += stoi(after); //yaha pein lc hein priye
                    fout << "+" << after << endl;
                }
                else if (plusminus == '-')
                {
                    lc -= stoi(after); //yaha pein lc hein priye
                    fout << "-" << after << endl;
                }
            }
        }
        else
        {
            fout << lc << " ";
            fout << "(" << opcode[word].first << "," << opcode[word].second << ") ";
            int increment = 1;

            while (st >> word)
            {
                if (operation == "DC")
                {
                    word = word.substr(1, word.length() - 2);
                    cout << "(C," << word << ") "; // No spaces
                }
                else if (operation == "DS")
                {
                    cout << "(C," << word << ") ";
                    increment = stoi(word); //here incremenet my boi not lc
                }
                else if (word[0] == '=')
                {
                    littab.push_back({word, lc});
                    fout << "(L," << littab.size() << ") "; // littab size here
                }
                else if (opcode.count(word) > 0)
                {
                    fout << opcode[word].first << " ";
                }
                else
                {
                    if (symtab.count(word) == 0)
                    {
                        symtab[word] = {lc, to_string(symtab.size() + 1)};
                    }
                    fout << "(S," << symtab[word].second << ") ";
                }
            }

            lc += increment;
        }
        fout << endl;
    }
    fin.close();
    fout.close();

    ofstream sout("symbol_table.txt");
    for (auto i : symtab)
    {
        sout << i.second.second << " " << i.first << " " << i.second.first << " ";
        sout << endl;
    }
    sout.close();

    ofstream lout("littab.txt");
    for (auto i : littab)
    {
        lout << i.first << " " << i.second << " ";
        lout << endl;
    }
    lout.close();

    ofstream pout("pool.txt");
    for (auto i : pooltab)
    {
        pout << i;
        pout << endl;
    }
    pout.close();

    cout << "Program for Pass 1 executed Successfully !! " << endl;

    return 0;
}