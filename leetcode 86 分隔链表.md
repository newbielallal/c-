---
title: leetcode 86 分隔链表
tags:
  - c++ 
categories: c++ 
---
本来是用一个新数组存储数值，然后重新赋给链表，后来觉得可以试试直接用两个链表组合。
<!-- more -->

### 题目
给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。

你应当保留两个分区中每个节点的初始相对位置。

示例:

输入: head = 1->4->3->2->5->2, x = 3
输出: 1->2->2->4->3->5

### 思路
这个就是新建了两个节点，然后遍历链表，如果链表节点的值大于X，则我们将此节点放在before链表中，否则放在after链表中，最后再将两个链表结合起来，这个方法要特别注意两个链表最后的连接，容易出问题，有一点绕。
### code
    ListNode* partition(ListNode* head, int x) {
        ListNode* pre=new ListNode(-1);
        pre->next=head;
        ListNode* before=new ListNode(-1);
        ListNode* after=new ListNode(-1);
        ListNode* before_head=before;
        ListNode* after_head=after;
        while(head!=NULL){
            if(head->val<x){
                before->next=head;
                before=before->next;
            }
            else{
                after->next=head;
                after=after->next;
            }
            head=head->next;
        }
        after->next=NULL;//需要先设置下一个指向NULL
        before->next=after_head->next;//注意是next等于，不然会被覆盖。
        return  before_head->next;
    }
### 思路
这个就是建立了两个vector，相当简单，遍历链表，节点的值就是大于x的存到一个vector中，小于x的存在一个vector中，最后我们再遍历链表，先将小于x的vector中的值赋给链表，再将大于x的vector的值赋给链表。
### code
    ListNode* partition(ListNode* head, int x) {
        ListNode* p1=head;
        vector<int>nums1;
        vector<int>nums2;
        while(p1)
        {
            
            if(p1->val>=x)
                nums2.push_back(p1->val);
            else
                nums1.push_back(p1->val);
                
            p1=p1->next;
        }
        p1=head;
        int i=0;
        while(p1&&i<nums1.size())
        {
            p1->val=nums1[i++];
            p1=p1->next;
        }
        i=0;
        while(p1)
        {
            p1->val=nums2[i++];
            p1=p1->next;
        }
        return head;
        
    }

