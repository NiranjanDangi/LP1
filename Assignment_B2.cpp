#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
#include<queue>
using namespace std;

void FCFS(vector<vector<int>> &process){
    int n = process.size();
    int currentTime = 0;
    sort(process.begin(),process.end(),[](const vector<int>&a, const vector<int>&b){
        return a[0] < b[0];
    });
    if(currentTime < process[0][0]) currentTime = process[0][0];
    process[0][2] = currentTime + process[0][1];
    process[0][3] = process[0][2] - process[0][0];
    process[0][4] = process[0][3] - process[0][1];
    currentTime = process[0][2];
    double avgT = process[0][3];
    double avgW = process[0][4];

    for (int i = 1; i < n; i++)
    {
        if(currentTime < process[i][0]) currentTime = process[i][0];
        process[i][2] = currentTime + process[i][1];
        process[i][3] = process[i][2] - process[i][0];
        process[i][4] = process[i][3] - process[i][1];
        currentTime = process[i][2];
        avgT += process[i][3];
        avgW += process[i][4];  
    }
    
    cout << "ProcessNo\tArrival Time\tBurst Time\tCompletion Time\tTurnAroundTime\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Process[" << i << "]" << "\t\t" << process[i][0] << "\t\t" << process[i][1] << "\t\t" << process[i][2] << "\t\t" << process[i][3] << "\t\t" << process[i][4] << endl;
    }

    cout << "Average Turnaround Time : " << avgT/n << endl;
    cout << "Average Waiting Time : " << avgW/n << endl;
    
}

void SJF(vector<vector<int>> &process){
    int n = process.size();
    vector<int> remainingBurst(n);
    vector<bool> isCompleted(n,false);
    int currentTime = 0;
    int completedProcess = 0;

    for (int i = 0; i < n; i++)
    {
        remainingBurst[i] = process[i][1];
    }

    while (completedProcess < n)
    {
        int burstIndex = -1;
        int minRemainingTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if(process[i][0] <= currentTime && !isCompleted[i] && remainingBurst[i] < minRemainingTime){
                minRemainingTime = remainingBurst[i];
                burstIndex = i;
            }
        }

        if(burstIndex == -1)
        {
            currentTime++;
            continue;
        }

        remainingBurst[burstIndex]--;
        currentTime++;

        if(remainingBurst[burstIndex] == 0){
            isCompleted[burstIndex] = true;
            completedProcess++; // Remember this one
            
            //Also these 3 in if and this sequence 1st line has only currentTime
            process[burstIndex][2] = currentTime;
            process[burstIndex][3] = process[burstIndex][2] - process[burstIndex][0];
            process[burstIndex][4] = process[burstIndex][3] - process[burstIndex][1];
        }
        
    }

    double avgT = 0;
    double avgW = 0;

    for (int i = 0; i < n; i++)
    {
        avgT += process[i][3];
        avgW += process[i][4];
    }

    cout << "ProcessNo\tArrival Time\tBurst Time\tCompletion Time\tTurnAroundTime\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Process[" << i << "]" << "\t\t" << process[i][0] << "\t\t" << process[i][1] << "\t\t" << process[i][2] << "\t\t" << process[i][3] << "\t\t" << process[i][4] << endl;
    }

    cout << "Average Turnaround Time : " << avgT/n << endl;
    cout << "Average Waiting Time : " << avgW/n << endl; 
 
}

void Priority(vector<vector<int>> &process){
    int n = process.size();
    vector<bool> completed(n,false);
    int currentTime = 0,completedProcess = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the Priority for Process No : [" << i << "] :" << endl;
        cin >> process[i][5];
    }

    while (completedProcess < n)
    {
        int minPriorityIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if(!completed[i] && process[i][0] <= currentTime){
                if(minPriorityIndex == -1 || process[i][5] < process[minPriorityIndex][5]){
                    minPriorityIndex = i;
                }
            }
        }

        if(minPriorityIndex == -1){
            currentTime++;
            continue;
        }

        int i = minPriorityIndex;
        completed[i] = true;
        completedProcess++;

        //Do remeber this sequence and also the sequence of SJF
        //This sequence is same as that of FCFS Loop from 1
        if(currentTime < process[i][0]) currentTime = process[i][0];
        process[i][2] = currentTime + process[i][1];
        process[i][3] = process[i][2] - process[i][0];
        process[i][4] = process[i][3] - process[i][1];
        currentTime = process[i][2];
        cout << "Process P[" << i << "] running at " << currentTime << endl; 
        
    }

    double avgT = 0;
    double avgW = 0;

    for (int i = 0; i < n; i++)
    {
        avgT += process[i][3];
        avgW += process[i][4];
    }

    cout << "ProcessNo\tArrival Time\tBurst Time\tCompletion Time\tTurnAroundTime\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Process[" << i << "]" << "\t\t" << process[i][0] << "\t\t" << process[i][1] << "\t\t" << process[i][2] << "\t\t" << process[i][3] << "\t\t" << process[i][4] << endl;
    }

    cout << "Average Turnaround Time : " << avgT/n << endl;
    cout << "Average Waiting Time : " << avgW/n << endl; 
    

}

void Roundrobin(vector<vector<int>> &process){
    int n = process.size();
    int currentTime = 0;
    int timeQuantum;
    cout << "Enter the time Quantum :" << endl;
    cin >> timeQuantum;

    vector<int>completionTime(n,0);
    queue<vector<int>>readyQueue;

    for (int i = 0; i < n; i++)
    {
        process[i][5] = process[i][1];
        vector<int> temp = process[i];
        temp[2] = i;
        readyQueue.push(temp);
    }

    while (!readyQueue.empty())
    {
        vector<int> currentProcess = readyQueue.front();
        readyQueue.pop();

        int processNo = currentProcess[2];
        int remainingBurst = currentProcess[5];
        int arrivalTime = currentProcess[0];

        if(arrivalTime <= currentTime)
        {
            if(remainingBurst <= timeQuantum)
            {
                currentTime += remainingBurst;
                cout << currentTime << "Process P[" << processNo << "] completed" << endl;
                currentProcess[5] = 0;
                completionTime[processNo] = currentTime;
            }
            else
            {
                currentTime += timeQuantum;
                cout << currentTime << "Process P[" << processNo << "]" << endl;
                currentProcess[5] -= timeQuantum;
                readyQueue.push(currentProcess);

            }
        }
        else
        {
            readyQueue.push(currentProcess);
            if(readyQueue.front()[0] > currentTime){
                currentTime = readyQueue.front()[0];
            }
        }
        
    }
    
    double avgT = 0,avgW = 0;
    for (int i = 0; i < n; i++)
    {
        process[i][2] = completionTime[i];
        process[i][3] = process[i][2] - process[i][0];
        process[i][4] = process[i][3] - process[i][1];
        avgT += process[i][3];
        avgW += process[i][4];
    }

    cout << "ProcessNo\tArrival Time\tBurst Time\tCompletion Time\tTurnAroundTime\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Process[" << i << "]" << "\t\t" << process[i][0] << "\t\t" << process[i][1] << "\t\t" << process[i][2] << "\t\t" << process[i][3] << "\t\t" << process[i][4] << endl;
    }

    cout << "Average Turnaround Time : " << avgT/n << endl;
    cout << "Average Waiting Time : " << avgW/n << endl;  
    

}

int main()
{
    int n;
    cout << "Enter the number of processes " << endl;
    cin >> n;

    vector<vector<int>> process(n,vector<int>(6));
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the arrival time and burst time for Process [P :" << i << "]" << endl;
        cin >> process[i][0];
        cin >> process[i][1]; 
    }

    int ch;
    char c = 'y';
    while (c == 'y')
    {
        cout << "==============MENU====================" << endl;
        cout << "1. First Come First Serve" << endl;
        cout << "2. Shortest Job First" << endl;
        cout << "3. Priority Scheduling" << endl;
        cout << "4. Round Robin" << endl;
        cout << "5. Exit" << endl;
        cout << "==============MENU====================" << endl;
        cin >> ch;
        if(ch == 1)
        {
            FCFS(process);
        }
        else if(ch == 2)
        {
            SJF(process);
        }
        else if(ch == 3)
        {
            Priority(process);
        }
        else if(ch == 4)
        {
            Roundrobin(process);
        }
        else if(ch == 5)
        {
            cout << "Thank you !! " << endl;
            break;
        }
        else{
            cout << "Enter a Valid Choice !!" << endl;
        }
        cout << "Do you want to continue(y/n) ?" << endl;
        cin >> c;
    }
    
    return 0;
}