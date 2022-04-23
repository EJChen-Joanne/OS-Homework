//610001018 RR Scheduling
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,pair<int,int>> pi;

bool cmp(const pi &a,const pi &b)
{
    return (a.second.first < b.second.first);//could allow new process enter first than the reentered one
}

int main()
{
    int quan, N,input;
    vector<int> arrival;
    vector<pi> task;
    cin >> N;
    for(int i = 0;i < N;i++)
    {
        cin >> input;
        arrival.push_back(input);
    }
    for(int i = 0;i < N;i++)
    {
        cin >> input;
        task.push_back({i,make_pair(arrival[i],input)});//<PID,<arrival time,cpu burst>>
    }
    cin >> quan;
    sort(task.begin(),task.end(),cmp);//sorted by arrival time in ascending order
    queue<pi> ReadyQueue;
    vector<int> waiting(N,0);
    vector<int> turnaround(N,0);

    int progresstime = 0, finished = 0, total_wait = 0, total_turn = 0;
    while(finished < N)
    {
        if(!task.empty())
        {
            vector<pi>::iterator it = task.begin();
            for(;it != task.end();it++)
            {
                if(it->second.first <= progresstime)
                {
                    ReadyQueue.push(*it);
                }
                else
                {
                    break;
                }
            }

            task.erase(task.begin(),it);
        }

        if(!ReadyQueue.empty())
        {
            bool check_end = (ReadyQueue.front().second.second > quan ? true : false );
            if (check_end)//cannot finish in this round
            {
                int pid = ReadyQueue.front().first;
                waiting[pid] += (progresstime - ReadyQueue.front().second.first);
                progresstime += quan;
                task.push_back({pid,make_pair(progresstime,ReadyQueue.front().second.second-quan)});
                sort(task.begin(),task.end(),cmp);
                ReadyQueue.pop();
            }
            else//can finish in this round
            {
                int pid = ReadyQueue.front().first;
                waiting[pid] += (progresstime - ReadyQueue.front().second.first);
                progresstime += ReadyQueue.front().second.second;
                turnaround[pid] += (progresstime - arrival[pid]);
                ReadyQueue.pop();
                finished++;
            }
        }
    }

    for(int i = 0;i < N;i++)
    {
        cout << waiting[i] << " " << turnaround[i] << '\n';
        total_wait += waiting[i];
        total_turn += turnaround[i];
    }
    cout << total_wait << '\n' << total_turn;

    arrival.clear();
    waiting.clear();
    turnaround.clear();

    return 0;
}
