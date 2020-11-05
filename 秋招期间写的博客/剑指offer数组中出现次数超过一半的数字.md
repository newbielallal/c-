---
title: 数组中出现次数超过一半的数字
tags:
  - c++ 
categories: 剑指offer
---
可以直接先排序，然后直接找最中间那个位置的元素作为结果，因为出现次数是超过一半的，但是这是nlogn的复杂度，完全可以降低到n复杂度。
<!-- more -->
题目描述
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
#思路
因为元素出现的次数超过了一半，所以很明显，可以先排序，然后数组的中间的元素就是要找的出现超过一半的元素，然后进行检验，如果没有一半，则输出0。
#code

    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.size()==0)
            return 0;
         sort(numbers.begin(),numbers.end());
        int num=numbers[numbers.size()/2];
        int count=0;
        for(int i=0;i<numbers.size();i++)
        {
            if(num==numbers[i])
                count++;
        }
        if(count>=(numbers.size()/2+1))
            return num;
        return 0;
    }

#思路
已经说过了，上面那个是ologn的，可以将复杂度降低到n，怎么做呢，很简单，因为如果满足条件的元素存在，那么它的出现次数肯定是大于一半的，无论对于奇数个数数组还是偶数个数数组来说，出现次数大于一半，那么它都比其它元素出现的次数加起来还要多，所以设置两个值，一个用来保存数组中的值，一个用来保存次数。然后如果下一个遍历到的数字与之前保存的数字相同，那么次数加一，否则次数减一，当次数为0的时候，保存当前遍历到的数字，将count置为1，如果存在满足条件的数字，那么最后可你的那个是该数字将count置为1，只需要检验count是否为1，不为1，输出0，为一继续进行检验，看该元素是否满足条件，满足则输出该数字，不满足输出0。
#code

	class Solution {
	public:
	    int MoreThanHalfNum_Solution(vector<int> numbers) {
	        if(numbers.size()==0)
	            return 0;
	         int num=numbers[0];
	         int count=1;
	         for(int i=1;i<numbers.size();i++)
	         {
	             if(count==0)
	             {
	                 num=numbers[i];
	                 count++;
	             }
	              else
	              {
	                  if(num==numbers[i])
	                      count++;
	                  else
	                      count--;
	              }
	         }
	        if(count==0)
	            return 0;
	        else
	        {
	            count=0;
	            for(int i=0;i<numbers.size();i++)
	            {
	                if(num==numbers[i])
	                    count++;
	            }
	            if(count>=(numbers.size()/2+1))
	                return num;
	            return 0;
	                
	        }
	        return 0;
	    }
	};

#思路
第三种则是利用快排的思想，如上面所说，出现次数超过一半，肯定是中位数，根据快排的思想，随机选择一个数，比它大的放在右边，比它小的放在左边，那么如果选中的数字刚好下标为n/2,那么肯定就是要找的中位数，如果下标小于n/2，那么往右边接着寻找，否则往左边接着寻找，利用一个递归的过程，肯定是可以找到n/2下标这个元素的，然后将其作为结果进行检验。
#code

	class Solution {
	public:
    int slecet(vector<int>&a,int l,int r)
    {
        int mid=l+((r-l)>>1);
        if ( a[ l ] > a[ mid ] )
            swap( a[ l ], a[ mid ] );
        if ( a[ l ] > a[ r ] )
            swap( a[ l ], a[ r ] );
        if ( a[ mid ] > a[ r ] )
            swap( a[ mid ], a[ r ] );
        /* A[ Left ] <= A[ Center ] <= A[ Right ] */
        swap( a[ mid ], a[ r-1 ] ); /* 将pivot藏到右边，节约一次比较，反正都比过了 */
        /* 只需要考虑 A[ Left+1 ] … A[ Right–2 ] */
        return a[ r-1 ]; /* 返回 pivot */
    }
    int partition(vector<int>&a,int l,int r,int mid)
    {
        if(l>=r)
            return mid;
        if(r-l==1)//一定要加上这一个判断条件，因为我们用了slecet函数选择元素，会导致只有两个元素的时候归并失效。
        {
            if(a[r]>=a[l])
                return mid;
            else
                swap(a[l],a[r]);
            return mid;
        }
        int num=slecet(a,l,r);
        int i=l+1;
        int j=r-2;
        while(i<j)
        {
            while(i<j&&a[i]<=num)//
                i++;
            while(j>i&&a[j]>=num)//可以往
                j--;
            if(i<j)
            {
                swap(a[i],a[j]);
            }
            else
                break;
        }
        swap(a[r-1],a[i]);
        return i;
    }
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.size()==0)
            return 0;
        int mid=numbers.size()>>1;
        int start=0;
        int end=numbers.size()-1;
        int index=partition(numbers,start,end,mid);
        while(index!=mid)
        {
            if(index>mid)
            {
                end=index-1;
                index=partition(numbers,start,end,mid);
            }
            else
            {
                start=index+1;
                index=partition(numbers,start,end,mid);
            }
        }
        int num=numbers[mid];
        int count=0;
        for(int i=0;i<numbers.size();i++)
        {
            if(num==numbers[i])
                count++;
        }
        if(count>=(numbers.size()/2+1))
            return num;
        return 0;
    }
	};