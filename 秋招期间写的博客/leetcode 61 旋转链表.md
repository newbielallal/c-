---
title: leetcode 61 旋转链表
tags:
  - c++ 
categories: c++ 
---
通过找到目标节点，然后开始旋转，因为链表不能后退，所以需要多个链表节点保存特殊节点。
<!-- more -->

### 题目
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL


### 思路
首先应该得出k和链表长度的关系，因为整数倍链表长度的旋转链表不变，所以k应当改成k除余链表的长度。因为向右移动一位相当于让最后一个节点往前循环移动来当头结点，移动两位相当于让倒数第二个节点来做头结点，所以我们将k改为k=链表长度-k，通过这样找到应该为新的头结点的节点p1，然后保存下此节点p1的前一个节点p1_last，并将它的下一位置为NULL，然后再对p1向下遍历，找到某一个节点p1_next，此节点的下一个节点为NULL，将它的下一个节点改为最初的头结点head。再将p1作为头结点输出。
### code
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==NULL)
            return head;
        int i=0;
        ListNode* p1_last;
        ListNode* p1=head;
        while(p1)
        {
            i++;
            p1=p1->next;
        }
        k=k%i;
        p1=head;
        k=i-k;
        if(k==0||k==i)
            return head;
        while(k!=0)
        {
            if(k==1)
            {
                 p1_last=p1;   
            }
            p1=p1->next;
            k--;
        }
        
        p1_last->next=NULL;
        ListNode* p1_next=p1;
        while(p1_next->next!=NULL)
            p1_next=p1_next->next;
        p1_next->next=head;
        return p1;

