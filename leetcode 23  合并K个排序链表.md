---
title: leetcode 23 合并K个排序链表
tags:
  - c++ 
categories: c++ 
---
利用归并排序。
<!-- more -->

### 题目

合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。

示例:

输入:
[
  1->4->5,
  1->3->4,
  2->6
]
输出: 1->1->2->3->4->4->5->6



### 思路

因为这些数组都是排好序的，这就是很明显可以利用归并排序了，只写了一个简单的二路归并，示例如下：
｛
｛1，2，3，4｝，
｛2，2，6，7｝，
｛4，5，12，67｝，
｛1，2，2，3｝
｝
首先将第一条链表p1和第二条链表p2进行归并，为了方便归并，所以先申请一个新的临时节点res,
1，2，3，4与2，2，6，7进行比较，首先选出p1、p2中最小的节点1，将其放在res后面，然后p1往后移动，res往后移动，然后再选p1、p2中的最小节点，最后结果是res->1->2->2->3->4->6->7,再将res->next赋给lists[0]，这样其实已经将两条链表连在一起了，最后记得删除res，防止内存泄漏，然后再将第一条链表和第三条链表进行归并，同理最后得到结果是：
res->1->2->2->3->4->4->5->6->7->12->67,再将res->next赋给lists[0]，这样将第三条链表加在第一条链表中，三条链表连在了一起，同样最后记得删除res。
再将第四条链表加入其中，同理得到结果：
res->1->1->2->2->2->2->3->3->4->4->5->6->7->12->67
严格来说不算归并，只是每次将一条链表（从第二条开始）有序加入已经排序好的第一条链表中，最后其实就是所有链表的排序结果，用上归并排序的两两归并，速度应该会更快，相当与log(n)和n的区别嘛。


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
	    void guibing(ListNode* &p1,ListNode* &p2,vector<ListNode*>& lists)
	    {
	         ListNode* res=new ListNode(0);
	        ListNode* temp=res;
	        while(p1&&p2)
	        {
	            if(p1->val<p2->val)
	            {
	                temp->next=p1;
	                temp=temp->next;
	                p1=p1->next;
	            }
	            else
	            {
	                temp->next=p2;
	                temp=temp->next;
	                p2=p2->next;
	            }
	        }
	        while(p1)
	        {
	                temp->next=p1;
	                temp=temp->next;
	                p1=p1->next;
	        }
	        while(p2)
	        {
	                temp->next=p2;
	                temp=temp->next;
	                p2=p2->next;
	        }
	        lists[0]=res->next;
			delete res;
	        return ;
	    }
	    ListNode* mergeKLists(vector<ListNode*>& lists) {
	        if(lists.size()==0)
	            return NULL;
	        for(int i=1;i<lists.size();++i)
	        {
	            ListNode* p2=lists[i];
	            ListNode* p1=lists[0];
	            
	            guibing(p2,p1,lists);
	            
	        }
	        return lists[0];
	    }
	};

     