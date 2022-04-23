#include<iostream>
#include<vector>
using namespace std;
vector<int> nums;

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

void merging(int len,int width)
{
    int temp[len];
    int p1,p2,e1,e2,index;
    p1 = 0;
    e1 = p1+width-1;
    p2 = e1+1;
    e2 = (p2+width-1) < (len-1) ? (p2+width-1) : (len -1);
    index = 0;
    while(p1 < len && p2 < len)
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
        e1 = (p1 + width-1) < (len-1) ? (p1+width-1) : (len-1);
        p2 = e1+1;
        e2 = (p2 + width-1) < (len-1) ? (p2+width-1) : (len-1);
    }

    while(p1 < len)//there is one left
    {
        temp[index++] = nums[p1++];
    }
    for(int i = 0;i < len;i++)
    {
        nums[i] = temp[i];
    }
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

    int n = nums.size();

    for(int i = 0;i<n;i+=100)
    {
        int temp = i+99 < n ? i+99 : n-1;
        selection_sort(i,temp);
    }
    for(int i = 100;i < n;i*=2)
    {
        merging(n,i);
    }
    int more = n%100;
    if(more){merge_2(0,n-more-1,n-1);}

    for(int i = 0;i < n;i++)
    {
        cout << nums[i] << " ";
    }

   return 0;
}
