#include<iostream>
#include<string>
#include<pthread.h>
#include<unistd.h>
using namespace std;
long long counts[3] = {0};//count the number of values [0,1,2]
string input;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct helper
{
    int start;
    int end;
};

void* count_fun(void* args)
{
    pthread_mutex_lock(&lock);
    helper* h = (helper*)args;
    int s = h->start, e = h->end;
    for(int j = s; j <= e;j++)
    {
        if((input[j]-'0') == 0) counts[0]++;
        else if((input[j]-'0') == 1) counts[1]++;
        else if((input[j]-'0') == 2) counts[2]++;
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    int th_num, num,error;
    cin >> th_num >> num >> input;
    pthread_t tid[th_num];//create threads
    helper H[th_num];
    int part = num/th_num;
    for(int i = 0;i < th_num;i++)
    {
        H[i].start = i*part;
        H[i].end = (i < th_num-1 ? (H[i].start+part-1) : num-1);
        error = pthread_create(&(tid[i]),NULL,&count_fun,&H[i]);
        if(error != 0) cout << "thread cannot create!" << endl;
    }

    for(int i = 0; i < th_num;i++)
    {
        pthread_join(tid[i],NULL);
    }

    for(int i = 0;i < 3;i++)
    {
        cout << i << ": " << counts[i] << '\n';
    }

    return 0;
}
