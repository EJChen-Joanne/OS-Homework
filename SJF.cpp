//Non-preemptive Shortest-job-first
#include<iostream>
#include<utility>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<int,int> p;
typedef pair<int,p> pii;

struct MyCmp
{
    constexpr bool operator()(pii const &a,pii const &b)
    const noexcept
    {
        return (a.second.second > b.second.second);
    }
};

bool cmp(pii &a,pii &b)
{
    return (a.second.first < b.second.first);
}

int main()
{
    int N;
    cin >> N;
    int input;
    vector<int> arrival;
    vector<pii> task;

    for (int i = 0;i < N;i++)
    {
        cin >> input;
        arrival.push_back(input);//index = PID
    }

    for (int j = 0;j < N;j++)
    {
        cin >> input;
        task.push_back({j,make_pair(arrival[j],input)});//j = PID
    }

    sort(task.begin(),task.end(),cmp);//sorted by arrival time in ascending order

    priority_queue<pii,vector<pii>,MyCmp> Ready_queue;//sorted by cpu burst time in ascending order
    int progresstime = 0, finished = 0;
    int total_wait = 0,total_turn = 0;
    vector<int> waiting(N,0);
    vector<int> turnaround(N,0);

    while(finished < N)
    {
        if(!task.empty())
        {
            vector<pii>::iterator it = task.begin();
            for(;it != task.end();++it)
            {
                if (it->second.first <= progresstime)//it is arrived
                {
                    Ready_queue.push(*it);
                }
                else
                    break;
            }
            task.erase(task.begin(),it);
        }


        if( !Ready_queue.empty())
        {
            finished++;//pick one to run
            int pid = Ready_queue.top().first;
            waiting[pid] += (progresstime - Ready_queue.top().second.first);
            progresstime += Ready_queue.top().second.second;
            turnaround[pid] += (progresstime - Ready_queue.top().second.first);
            Ready_queue.pop();
        }
    }

    for (int i = 0;i < N;i++)
    {
        cout << waiting[i] << " " << turnaround[i] << '\n';
        total_wait+=waiting[i];
        total_turn+=turnaround[i];
    }
    cout << total_wait << '\n' << total_turn;

    arrival.clear();
    waiting.clear();
    turnaround.clear();
    return 0;
}
