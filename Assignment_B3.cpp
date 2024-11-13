#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct Block{
    int size;
    int process;
    bool allocated;
};

void display(vector<Block> &memory){
    cout << "Displaying Memory Blocks : " << endl;
    for (int i = 0; i < memory.size(); i++)
    {
        cout << memory[i].size << " ";
    }
    cout << endl;

    cout << "Displaying Available Memory Blocks : " << endl;
    for (int i = 0; i < memory.size(); i++)
    {
        cout << memory[i].process << " ";
    }
    cout << endl;
    
}

void FirstFit(vector<Block> &memory,int requestSize,int &lastIndex){

    for (int i = 0; i < memory.size(); i++)
    {
        if(!memory[i].allocated && memory[i].size >= requestSize){
            memory[i].allocated = true;
            memory[i].process = requestSize;
            lastIndex = i;
            cout << "First Fit : Memory of size " << requestSize << " allocated at block " << i << endl;
            return;
        }    
    }
    cout << "First Fit : Memory allocation failed for " << requestSize << endl;
 
}

int NextFit(vector<Block> &memory,int requestSize,int &lastIndex){

    for (int i = lastIndex; i < memory.size(); i++)
    {
        if(!memory[i].allocated && memory[i].size >= requestSize){
            memory[i].allocated = true;
            memory[i].process = requestSize;
            lastIndex = i;
            cout << "Next Fit : Memory of size " << requestSize << " allocated at block " << i << endl;
            return i;
        }    
    }

    for (int i = 0; i < lastIndex; i++)
    {
        if(!memory[i].allocated && memory[i].size >= requestSize){
            memory[i].allocated = true;
            memory[i].process = requestSize;
            lastIndex = i;
            cout << "Next Fit : Memory of size " << requestSize << " allocated at block " << i << endl;
            return i;
        }    
    }
    cout << "Next Fit : Memory allocation failed for " << requestSize << endl;
    return -1;
}

void BestFit(vector<Block> &memory,int requestSize,int &lastIndex){
    int bestFitIndex = -1;
    int minFragmentation = INT_MAX;

    for (int i = 0; i < memory.size(); i++)
    {
        if(!memory[i].allocated && memory[i].size >= requestSize){
            int fragementation = memory[i].size - requestSize;
            if(fragementation < minFragmentation){
                minFragmentation = fragementation;
                bestFitIndex = i;
            }
        }
    }

    if(bestFitIndex != -1){
        memory[bestFitIndex].allocated = true;
        memory[bestFitIndex].process = requestSize;
        lastIndex = bestFitIndex;
        cout << "Best Fit : Memory of size " << requestSize << " allocated at block " << bestFitIndex << endl;
    }
    else{
        cout << "Best Fit : Memory allocation failed for " << requestSize << endl;
    }
    
}

void WorstFit(vector<Block> &memory,int requestSize,int &lastIndex){
    int worstFitIndex = -1;
    int maxFragmentation = INT_MIN;

    for (int i = 0; i < memory.size(); i++)
    {
        if(!memory[i].allocated && memory[i].size >= requestSize){
            int fragementation = memory[i].size - requestSize;
            if(fragementation > maxFragmentation){
                maxFragmentation = fragementation;
                worstFitIndex = i;
            }
        }
    }

    if(worstFitIndex != -1){
        memory[worstFitIndex].allocated = true;
        memory[worstFitIndex].process = requestSize;
        lastIndex = worstFitIndex;
        cout << "Worst Fit : Memory of size " << requestSize << " allocated at block " << worstFitIndex << endl;
    }
    else{
        cout << "Worst Fit : Memory allocation failed for " << requestSize << endl;
    }
}

int main(){

    int numBlocks;
    cout << "Enter number of memory blocks" << endl;
    cin >> numBlocks;

    vector<Block>memory(numBlocks);
    cout << "Enter size of each memory block" << endl;
    for (int i = 0; i < numBlocks; i++)
    {
        cin >> memory[i].size;
        memory[i].allocated = false;
    }

    int ch,lastIndex = 0;
    char c = 'y';

    while (c == 'y')
    {
        cout << "===================================" << endl;
        cout << "1. First Fit" << endl;
        cout << "2. Next Fit" << endl;
        cout << "3. Best Fit" << endl;
        cout << "4. Worst Bit" << endl;
        cout << "5. Exit" << endl;
        cout << "===================================" << endl;
        cout << "Enter your choice : " << endl;
        cin >> ch;

        if(ch == 1){
            int requestSize;
            cout << "Enter size of process to allocate " << endl;
            cin >> requestSize;
            FirstFit(memory,requestSize,lastIndex);
            display(memory);
        }
        else if(ch == 2){
            int requestSize;
            cout << "Enter size of process to allocate " << endl;
            cin >> requestSize;
            lastIndex = NextFit(memory,requestSize,lastIndex);
            display(memory);

        }
        else if(ch == 3){
            int requestSize;
            cout << "Enter size of process to allocate " << endl;
            cin >> requestSize;
            BestFit(memory,requestSize,lastIndex);
            display(memory);
        }
        else if(ch == 4){
            int requestSize;
            cout << "Enter size of process to allocate " << endl;
            cin >> requestSize;
            WorstFit(memory,requestSize,lastIndex);
            display(memory);
        }
        else if(ch == 5){
            cout << "Thank you !! " << endl;
            break;
        }
        else{
            cout << "Inavlid Input !! " << endl;
        }
        cout << "Do you want to continue(y/n) ?" << endl;
        cin >> c;
    }
    
    

    return 0;
}