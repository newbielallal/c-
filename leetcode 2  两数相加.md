---
title: leetcode 2. 两数相加
tags:
  - c++ 
categories: c++ 
---
第一种办法是在原有链表更长的那个作为结果返回，虽然节约了空间，但是增加了时间复杂度，而且没有考到如何设置链表的增加与删除。

<!-- more -->

### 题目

给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

### 思路

首先计算出两个链表分别的长度，然后将长度更长的那个作为存储相加结果的链表，这样可以少掉很多操作，然后从链表头开始相加，就是注意一下进位的存储以及处理就好了。

### code

	/**
	 * Definition for singly-linked list.
	 * struct ListNode {
	 *     int val;
	 *     ListNode *next;
	 *     ListNode(int x) : val(x), next(NULL) {}
	 * };
	 */
	class Solution {
	public:
	    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	        int l1_length=0;
	        int l2_length=0;
	        ListNode *p1=l1;
	        ListNode *p2=l2;
	        while(p1)//计算两个链表的长度
	        {
	            l1_length++;
	            p1=p1->next;
	        }
	        while(p2)
	        {
	            l2_length++;
	            p2=p2->next;
	        }
	        int jinwei=0;//存储进位
	        p1=l1;
	        p2=l2;
	        if(l1_length==0)//任何一个长度为0，都可以直接返回另外一个。
	            return l2;
	        if(l2_length==0)
	            return l1;
	        if(l1_length>l2_length)l1更长
	        {
	            ListNode *lastp1=p1;
	            while(lastp1->next)//找到l1的最后一位。
	                lastp1=lastp1->next;
	            while(p1&&p2)
	            {
	                p1->val+=p2->val+jinwei;//两者相加，结果存储在l1当中。
	                jinwei=0;
	                if(p1->val>=10)//如果结果大于10,那么需要求余并且进位。
	                {
	                    jinwei=1;
	                    p1->val%=10;
	                }
	                p1=p1->next;
	                p2=p2->next;
	            }
	            while(p1)//因为是l1更长，所以只有可能最后还剩下l1的链表节点，也有可能不剩下。
	            {
	                p1->val+=jinwei;//只用和进位相加了，l2已经计算结束了。
	                jinwei=0;
	                if(p1->val==10)//同理取余。
	                {
	                    jinwei=1;
	                    p1->val=0;
	                }
	                p1=p1->next;
	            }
	            if(jinwei==1)//如果最后还多一个进位，那么需要把它加在l1的最后，这就是取l1尾部的原因，
                //因为p1肯定是已经到了l1尾部的后一个点，并且不能倒退，所以只能之前就遍历一遍。
	            {
	                ListNode *new1=new ListNode(1);
	                
	               
	                lastp1->next=new1;
	            }
	            return l1;
	        }
	        else if(l1_length<l2_length)//一样的道理，只是用l2来返回。
	        {
	            ListNode *lastp2=p2;
	            while(lastp2->next)
	                lastp2=lastp2->next;
	            while(p1&&p2)
	            {
	                p2->val+=p1->val+jinwei;
	                jinwei=0;
	                if(p2->val>=10)
	                {
	                    jinwei=1;
	                    p2->val%=10;
	                }
	                p1=p1->next;
	                p2=p2->next;
	            }
	            while(p2)
	            {
	                p2->val+=jinwei;
	                jinwei=0;
	                if(p2->val==10)
	                {
	                    jinwei=1;
	                    p2->val=0;
	                }
	                p2=p2->next;
	            }
	            if(jinwei==1)
	            {
	                ListNode *new1=new ListNode(1);
	                lastp2->next=new1;
	            }
	            return l2;
	        }
	        else//这是两者等长的情况。
	        {
	            ListNode *lastp1=l1;
	            while(lastp1->next)
	                lastp1=lastp1->next;
	            while(p1&&p2)
	            {
	                p1->val+=p2->val+jinwei;
	                
	                jinwei=0;
	                if(p1->val>=10)
	                {
	                    jinwei=1;
	                    p1->val%=10;
	                }
	                p1=p1->next;
	                p2=p2->next;
	            }
	            if(jinwei==1)
	            {
	                ListNode *new1=new ListNode(1);
	                lastp1->next=new1;
	            }
	            return l1;
	        }
	        return l1;
	    }
	};

### 思路

上面那种方法是因为最开始不熟悉链表的建立这些，所以用的很笨的方法，下面这个快一点，不过感觉真正写程序的时候要注意删除，防止内存泄漏。

### code
    
	/**
	 * Definition for singly-linked list.
	 * struct ListNode {
	 *     int val;
	 *     ListNode *next;
	 *     ListNode(int x) : val(x), next(NULL) {}
	 * };
	 */
	class Solution {
	public:
	    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	        ListNode* res=new ListNode(0);
	        ListNode* p=res;
	        int flag=0;
	        while(l1||l2)
	        {
	            int num=0;
	            if(l1)
	                num+=l1->val;
	            if(l2)
	                num+=l2->val;
	           num=num+flag;
	            flag=num/10;
	            if(l1)l1=l1->next;
	            if(l2)l2=l2->next;
	            p->next=new ListNode(num%10);
	            p=p->next; 
	        }
	        if(flag==1)
	            p->next=new ListNode(1);
	        return res->next;
	    }
	};

