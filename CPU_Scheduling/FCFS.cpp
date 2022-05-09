//FCFS Scheduling
#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,pair<int,int> > pi;

int main()
{
    int N;//number of process
    int arrival,cputime;
    vector<int> arrival_time;//key=process number; value = arrival time
    vector<pi> task;
    cin >> N;
    for(int i =0;i<N;i++)
    {
        cin >> arrival;
        arrival_time.push_back(arrival);
    }

    for (int i = 0;i < N;i++)
    {
        cin >> cputime;
        task.push_back({i,make_pair(arrival_time[i],cputime)});
    }

    sort(task.begin(),task.end(),
         [](const pi &a,const pi &b){ return (a.second.first < b.second.first);});

    int progresstime = 0;
    int totalwait = 0,totalturn = 0;
    vector<int> waiting(N,0);
    vector<int> turnaround(N,0);
    for(auto &process : task)
    {
        int pid = process.first;
        waiting[pid] += (progresstime - process.second.first);
        progresstime += process.second.second;
        turnaround[pid] += (progresstime - process.second.first);
    }

    for(int i = 0;i < N;i++)
    {
        cout << waiting[i] << " " << turnaround[i]<<endl;
        totalwait+=waiting[i];
        totalturn+=turnaround[i];
    }
    cout << totalwait << endl << totalturn;

    arrival_time.clear();
    task.clear();
    waiting.clear();
    turnaround.clear();

    return 0;
}
