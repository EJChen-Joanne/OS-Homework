//610001018 MFQs Scheduling
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;
typedef pair<int,pair<int,int>> pi;
struct MyCmp
{
    constexpr bool operator()(pi const &a,pi const &b)
    const noexcept
    {
        return (a.second.second > b.second.second);
    }
};
queue<pi> Q0;
priority_queue<pi,vector<pi>,MyCmp> Q1;

bool cmp(const pi &a,const pi &b)
{
    return (a.second.first < b.second.first);//sorted by arrival time in ascending order
}

void RR(int &ptime,const int pid,int burst,vector<int> &waiting)
{
    waiting[pid] += (ptime - Q0.front().second.first);
    ptime += burst;
}

void SRTF(int &ptime,const int pid,int burst,vector<int> &waiting)
{
    waiting[pid] += (ptime - Q1.top().second.first);
    ptime += burst;
}

int main()
{
    int N,quan;
    vector<int> arrival;
    vector<pi> task;
    cin >> N;
    int input;
    for(int i = 0;i < N;i++)
    {
        cin >> input;
        arrival.push_back(input);
    }
    for(int i = 0;i < N;i++)
    {
        cin >> input;
        task.push_back({i,make_pair(arrival[i],input)});
    }
    sort(task.begin(),task.end(),cmp);
    cin >> quan;
    int progresstime = 0, finished = 0;
    vector<int> waiting(N,0);
    vector<int> turnaround(N,0);

    while(finished < N)
    {
        if(!task.empty())
        {
            vector<pi>::iterator it = task.begin();
            for(;it != task.end();++it)
            {
                if(it->second.first <= progresstime)
                {
                    Q0.push(*it);
                }
                else
                    break;
            }
            task.erase(task.begin(),it);
        }

        if(!Q0.empty())
        {
            int pid = Q0.front().first;
            bool check_finished = (Q0.front().second.second <= quan ? true : false);
            if(check_finished)
            {
                RR(progresstime,pid,Q0.front().second.second,waiting);
                turnaround[pid] += (progresstime - arrival[pid]);
                Q0.pop();
                finished++;
            }
            else
            {
                RR(progresstime,pid,quan,waiting);
                Q0.front().second.second -= quan;
                Q0.front().second.first = progresstime;
                Q1.push(Q0.front());
                Q0.pop();
            }
        }
        else//Q0 is empty
        {
            if(!Q1.empty())
            {
                int pid = Q1.top().first;
                bool check_newp;
                if(!task.empty())
                    check_newp = ((progresstime + Q1.top().second.second) > task.begin()->second.first ? true : false);
                else
                    check_newp = false;

                if(check_newp)//new process preempts Q1
                {
                    int temp_burst = task.begin()->second.first - progresstime;
                    SRTF(progresstime,pid,temp_burst,waiting);//Q1.front hasn't finished
                    pi temp_p = Q1.top();
                    Q1.pop();
                    Q1.push({pid,make_pair(progresstime,temp_p.second.second - temp_burst)});
                }
                else//Q1 won't be preemptive
                {
                    SRTF(progresstime,pid,Q1.top().second.second,waiting);
                    turnaround[pid] += (progresstime - arrival[pid]);
                    Q1.pop();
                    finished++;
                }
            }
        }
    }

    int total_wait = 0, total_turn = 0;

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
