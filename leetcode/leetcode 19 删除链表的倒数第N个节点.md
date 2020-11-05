---
title: leetcode 19 删除链表的倒数第N个节点
tags:
  - c++ 
categories: c++ 
---
思路清晰就没啥问题，但是这个解法问题很大，存在内存泄漏。
<!-- more -->

### 题目

给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：

给定的 n 保证是有效的。


### 思路

首先先将倒数的第N个节点找出正序时候的位置，很明显倒数的第N个节点在正序中的位置是l+1-N，其中l是链表的总长度，题目已经说过了N是有效数字。其次开始删除了，因为是单向链表，所以为了方便，另外定义一个ahead来保存指针遍历到的节点的前向节点。
当删除正序第一个节点的时候，直接返回头结点的next节点就可以了。
当删除第N个节点的时候，将第N-1个节点的next指针指向N+1（当为第N个节点为最后一个节点时，N+1是null,也可以正确运行），然后删除第N个节点，所以也没有问题。
但是这是一个两次遍历了。

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
	    ListNode* removeNthFromEnd(ListNode* head, int n) {
	       ListNode* p1=head;
	        int l=0;
	        while(p1)
	        {
	            p1=p1->next;
	            l++;
	        }
	        int del=l+1-n;
	        if(del==1)
	            return head->next;
	        p1=head;
	        ListNode* ahead=new ListNode(0);
	        ahead->next=p1;
	        while(1)
	        {
	            if(del==1)
	            {
	               ahead->next=p1->next;
	                delete p1;
	                return head;
	            }
	            else
	            {
	                del--;
	                ahead=p1;
	                p1=p1->next;
	            }
	            
	        }
	        return head;
	    }
	};


### 思路

下面的代码就是一个一次遍历的，用了一个双指针，p1、p2最开始都是指向头结点的，但是因为要删除的是倒数第N个节点，所以第一个指针p1首先向前走N-1步，第二个指针p2才开始出发往前遍历，这样当指针p1->next指向NULL的时候，p2指针就正好指向要删除的节点，然后删除掉p2所指的这个节点就可以了，删除方法有点low，因为没有存储下来p2的前面一个节点，所以就将p2->next->val赋给了p2->val，然后删除掉p2->next，所以严格来说是删除了p2->next，也就是说严格来说是删除了倒数第N+1个节点。

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
		    ListNode* removeNthFromEnd(ListNode* head, int n) {
		        ListNode* p1=head;
		        ListNode* p2=head;
		        if(p1->next==NULL)
		            return NULL;
		        for(int i=1;i<n;i++)
		        {
		            p1=p1->next;
		        }
		        if(n==1)
		        {
		            while(p1->next->next)
		            {
		                p1=p1->next;
		                
		            }
		            p2=p1->next;
		            p1->next=NULL;
		            p2=NULL;
		            
		        }
		        else
		        {
					while(p1->next)
			        {
			            p1=p1->next;
			            p2=p2->next;
			        }
			        p1=p2->next;
			        p2->val=p1->val;
			        p2->next=p1->next;
			        p1=NULL;
				}
			        return head;
		    }
		};