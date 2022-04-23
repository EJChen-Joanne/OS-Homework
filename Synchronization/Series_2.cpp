#include<iostream>
#include<string>
#include<pthread.h>
#include<unistd.h>
using namespace std;
string input;
long long counts[3] = {0};
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER, lock2 = PTHREAD_MUTEX_INITIALIZER,
                lock3 = PTHREAD_MUTEX_INITIALIZER, lock4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockArray[3];
int done = 0;

struct  helper
{
    int start;
    int end;
    int part_num;
};

void* count_fun(void* args)
{
    pthread_mutex_lock(&lock1);
    helper* idx = (helper*)args;
    int thread_num = idx->part_num;
    for(int t = idx->start;t <= idx->end;t++)
    {
        if((input[t]-'0') == 0) counts[0]++;
        else if((input[t] - '0') == 1) counts[1]++;
        else if((input[t] - '0') == 2) counts[2]++;
    }
    done++;
    pthread_mutex_unlock(&lock1);
    if(done == 3)
    {
        pthread_mutex_unlock(&LockArray[0]);
    }

    pthread_mutex_lock(&LockArray[thread_num]);
    cout << thread_num << ": " << counts[thread_num] << '\n';
    pthread_mutex_unlock(&LockArray[thread_num+1]);

    return NULL;
}

int main()
{
    int num;
    cin >> num >> input;
    int error;
    pthread_t tid[3];
    helper H[3];
    LockArray[0] = lock2;
    LockArray[1] = lock3;
    LockArray[2] = lock4;
    int part = num/3;
    for(int i = 0; i < 3;i++)
    {
        pthread_mutex_lock(&LockArray[i]);
    }

    for(int i = 0;i < 3;i++)
    {
        H[i].start = i*part;
        H[i].end = (i < 2 ? (H[i].start+part-1) : num-1);
        H[i].part_num = i;
        error = pthread_create((&tid[i]), NULL, &count_fun,&H[i]);
    }
    for(int i = 0 ; i < 3;i++)
    {
        pthread_join(tid[i],NULL);
    }

    return 0;
}