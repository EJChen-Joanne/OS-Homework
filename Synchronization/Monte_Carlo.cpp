#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<time.h>
#include<cmath>
using namespace std;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
long long counts = 0;
long long points_per_thread;

void* count_fun(void* args)
{
    pthread_mutex_lock(&lock);
    double rand_x,rand_y,dist;
    unsigned int rand_state = rand();
    for(long long k = 0;k < points_per_thread;k++)
    {
        rand_x = rand_r(&rand_state) / ((double)RAND_MAX+1.0);
        rand_y = rand_r(&rand_state) / ((double)RAND_MAX+1.0);
        dist = rand_x*rand_x + rand_y*rand_y;
        if(dist < 1)
        {
            counts++;
        }
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    long long th_num, total_points;
    cin >> th_num >> total_points;
    points_per_thread = total_points / th_num;
    pthread_t tid[th_num];
    srand((unsigned int)time(NULL));
    for(int i = 0;i < th_num;i++)
    {
        pthread_create((&tid[i]),NULL,count_fun,(void*)NULL);
    }

    for(int i = 0;i < th_num;i++)
    {
        pthread_join(tid[i],NULL);
    }

    double pi = (4.0 * (double)counts) / (double)total_points;

    cout << "get: " << counts << '\n' << "Pi: " << pi << '\n';

    return 0;
}