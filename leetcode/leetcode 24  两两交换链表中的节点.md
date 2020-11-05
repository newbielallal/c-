---
title: leetcode 24 两两交换链表中的节点
tags:
  - c++ 
categories: c++ 
---
链表问题还是思路要清晰就可以了。
<!-- more -->

### 题目

给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 

示例:

给定 1->2->3->4, 你应该返回 2->1->4->3.

### 思路

还是一样的说法，链表的问题只要思路清晰，并且保证没有访问到错误的值，比如NULL，或者对NULL求next，一般没有多大的问题，下面这个问题因为是每两个节点交换，所以最后是有一个额外的节点，用来辅助交换，保存节点信息，下面就具体举例：

要将链表1->2->3->4->5两两进行交换，首先申请一个辅助节点ahead,将其的后继节点设为1，将辅助节点后面节点称为p1节点，将p1后面的那个节点称为nex，这样原链表变成了res->1->2->3->4->5,1其中p1指向1，nex指向2，其后将p1和nex进行交换。

交换的步骤要注意顺序，否则会丢失掉节点信息，首先将ahead的后继节点换成nex，然后将p1的后继节点换成nex的后继节点，最后将nex的后继节点换成p1，这样原来的ahead->p1->nex->(nex->next)就变成了ahead->nex->p1->(nex->next)，交换结束然后再调整ahead、p1、nex指向的节点，这里要注意，如果说后面剩下的节点个数只有1个，那么就不用继续交换了，如果说还有大于1个节点，就继续进行交换。将ahead指向交换之后的后一个节点，也就是ahead->nex->p1->(nex->next)中的p1，然后将p1指向ahead->next，nex指向ahead->next->next，这样又进行新一轮的交换，直到最后交换结束。


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
	    ListNode* swapPairs(ListNode* head) {
	        ListNode* ahead=new ListNode(0);
	        ListNode* res=ahead;
	        if(!(head&&head->next))
	        {
	            return head;
	        }
	        ListNode* p1=head;
	        ListNode* nex=head->next;
	        while(1)
	        {
	            ahead->next=nex;
	            p1->next=nex->next;
	            nex->next=p1;
	            ahead=p1;
	            if(ahead->next&&ahead->next->next)
	            {
	                p1=p1->next;
	                nex=p1->next;
	            }
	            else
	                break; 
	            
	        }
	        return res->next;
	    }
	};