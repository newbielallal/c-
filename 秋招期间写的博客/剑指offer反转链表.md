---
title: 反转链表
tags:
  - c++ 
categories: 剑指offer
---
链表的操作比较繁琐和麻烦，所以觉得这个题目比较能考察。
<!-- more -->
题目描述
定义一个函数，输入一个链表的头结点，反转该链表并输出反转后的链表头结点。
#思路
因为要遍历一遍就实现反转，所以每遍历一个节点，就应该将它的next指针指向它的前一个节点，因为是单向的，所以必须需要一个节点来存储它的前一个节点，不然无法找到，当将待处理的节点next指向它的前一个节点之后，那么就丢失了它原本的next指向的那个节点，所以需要另外一个节点来保存处理节点的下一个节点，综上，在整个处理过程中，一共需要三个节点，一个是正在处理的节点，两个用来分别保存正在处理节点的前向节点以及后向节点。
#code

		struct ListNode {
		int val;
		struct ListNode *next;
		ListNode(int x) :
				val(x), next(NULL) {
		}
		};*/
		class Solution {
		public:
		    ListNode* ReverseList(ListNode* pHead) {
		        ListNode* res=NULL;//用来保存后向节点，也是最后的输出结果，因为原链表的最后一个节点肯定是新链表的第一个节点
		        ListNode* p=pHead;//从头结点开始往后处理
		        ListNode* pqian=NULL;//头结点的前向节点必然为空
		        while(p)
		        {
		            ListNode* pnext=p->next;
		            if(pnext==NULL)
		                res=p;
		            p->next=pqian;//更改处理节点的指向
		            pqian=p;//向后移动
		            p=pnext;//向后移动
		        }
		        return res;
		    }
		};