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

    while(p1 <= e)//there is still left
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
    int n = nums.size();
    struct params* S = (struct params*) args;
    int s = S->start;
    int e = S->last;
    int len = (e-s+1);
    for(int i = s;i <= e;i+=2)//each 2 number as a split set
    {
        int temp = i+1 <= e ? i+1 : e;
        selection_sort(i,temp);
    }
    
    pthread_exit(NULL);
}

void *merge_begin(void *args)
{
    int n = nums.size();
    struct params* M = (struct params*) args;
    int s = M->start;
    int e = M->last;
    int temp_len = e-s+1;
    for(int i = 2;i <= temp_len;i*=2)
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
    int width = len/4;

    pthread_t threads[8];//four for sorting and four for merge
    struct params Args[4];
    Args[0].start = 0;
    Args[0].last = width-1;
    Args[1].start = Args[0].last+1;
    Args[1].last = 2*width-1;
    Args[2].start = Args[1].last+1;
    Args[2].last = 3*width-1;
    Args[3].start = Args[2].last+1;
    Args[3].last = len-1;
    
    for(int i = 0;i < 4;i++)
    {
        pthread_create(&threads[i],NULL,sort_begin,&Args[i]);
    }
    for(int i = 0;i < 4;i++)
    {
        pthread_join(threads[i],NULL);
    }

    for(int i = 4;i < 8;i++)
    {
        pthread_create(&threads[i],NULL,merge_begin,&Args[i-4]);
    }
    for(int i = 4;i < 8;i++)
    {
        pthread_join(threads[i],NULL);
    }

    merge_2(Args[0].start,Args[0].last,Args[1].last);
    merge_2(Args[2].start,Args[2].last,Args[3].last);
    merge_2(Args[0].start,Args[1].last,Args[3].last);

    //print result
    for(int i = 0;i < len;i++)
    {
        cout << nums[i] << " ";
    }

   return 0;
}
