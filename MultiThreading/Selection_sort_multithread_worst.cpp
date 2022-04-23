#include<iostream>
#include<vector>
#include<pthread.h>
#include<unistd.h>
using namespace std;
vector<int> nums;

struct params
{
  int start;
  int last;
};

void selection_sort(int s,int e)
{
    int t;
    for(int i = s;i < e;i++)
    {
        for(int j = i+1;j <= e;j++)
        {
            if(nums[i] > nums[j])
            {
                t = nums[i];
                nums[i] = nums[j];
                nums[j] = t;
            }
        }
    }
}

void merging(int s,int e,int width)
{
    int n = nums.size();
    int temp[n];
    int p1,p2,e1,e2,index;
    p1 = s;
    e1 = s+width-1;
    p2 = e1+1;
    e2 = (p2+width-1) < e ? (p2+width-1) : e;
    index = s;
    while(p1 <= e && p2 <= e)
    {
        while(p1<=e1 && p2 <= e2)
        {
            if(nums[p1] <= nums[p2])
            {
                temp[index++] = nums[p1++];
            }
            else
            {
                temp[index++] = nums[p2++];
            }
        }

        while(p1 <= e1)
        {
            temp[index++] = nums[p1++];
        }

        while(p2 <= e2)
        {
            temp[index++] = nums[p2++];
        }

        p1 = e2+1;
        e1 = (p1 + width-1) < e ? (p1+width-1) : e;
        p2 = e1+1;
        e2 = (p2 + width-1) < e ? (p2+width-1) : e;
    }

    while(p1 <= e)
    {
        temp[index++] = nums[p1++];
    }
    for(int i = s;i <= e;i++)
    {
        nums[i] = temp[i];
    }
}

void *sort_begin(void *args)
{
    struct params* S = (struct params*) args;
    int s = S->start;
    int e = S->last;
    int n = (e-s+1);

    for(int i = s;i <= e;i+=100)//each 100 number as a split set
    {
        int temp = i+99 <= e ? i+99 : e;
        selection_sort(i,temp);
    }

    pthread_exit(NULL);
}

void *merge_begin(void *args)
{
    struct params* M = (struct params*) args;
    int s = M->start;
    int e = M->last;
    int temp_len = e-s+1;
    for(int i = 100;i <= temp_len;i*=2)
    {
        merging(s,e,i);
    }

    pthread_exit(NULL);
}

void merge_2(int s,int mid,int e)
{
    int p1 = s, e1 = mid,p2 = mid+1,e2 = e;
    int n = nums.size();
    int temp[n];
    int index = s;
    while(p1<=e1 && p2 <= e2)
    {
        if(nums[p1] <= nums[p2])
        {
            temp[index++] = nums[p1++];
        }
        else
        {
            temp[index++] = nums[p2++];
        }
    }  
    while(p1<=e1)
    {
        temp[index++] = nums[p1++];
    }
    while(p2<=e2)
    {
        temp[index++] = nums[p2++];
    }

    for(int i = s;i <= e;i++)
    {
        nums[i] = temp[i];
    }
}

int main()
{
    int input;
    while(cin >> input)
    {
        nums.push_back(input);
    }

    int len = nums.size();
    int p1,e1,p2,e2;
    p1 = 0;
    e1 = (int)len/2;
    p2 = e1+1;
    e2 = len-1;

    pthread_t threads[4];//two for sorting and two for merge
    struct params Args[2];
    Args[0].start = p1;
    Args[0].last = e1;
    Args[1].start = p2;
    Args[1].last = e2;

    pthread_create(&threads[0],NULL,sort_begin,&Args[0]);
    pthread_create(&threads[1],NULL,sort_begin,&Args[1]);
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    pthread_create(&threads[2],NULL,merge_begin,&Args[0]);
    pthread_create(&threads[3],NULL,merge_begin,&Args[1]);
    pthread_join(threads[2],NULL);
    pthread_join(threads[3],NULL);

    merge_2(0,e1,e2);

    //print result
    for(int i = 0;i < len;i++)
    {
        cout << nums[i] << " ";
    }

   return 0;
}
