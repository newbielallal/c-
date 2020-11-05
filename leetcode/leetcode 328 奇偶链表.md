---
title: leetcode 328 奇偶链表
tags:
  - c++ 
categories: c++ 
---
就是链表内部的操作。
<!-- more -->

### 题目
给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。

请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。

示例 1:

输入: 1->2->3->4->5->NULL
输出: 1->3->5->2->4->NULL
示例 2:

输入: 2->1->3->5->6->4->7->NULL 
输出: 2->3->6->7->1->5->4->NULL
说明:

应当保持奇数节点和偶数节点的相对顺序。
链表的第一个节点视为奇数节点，第二个节点视为偶数节点，以此类推。
### 思路
要把奇数节点排在前面，偶数节点排在后面，而且是原地算法，那么需要新建三个节点来存储原来链表中的节点，一个存储偶数节点，一个存储奇数节点，一个存储目前正要处理的节点。
### code
     ListNode* oddEvenList(ListNode* head) {
        if(head==NULL||head->next==NULL||head->next->next==NULL)
            return head;//这三种情况不用处理，直接返回。
        int num=3;//从第三个节点开始处理
        ListNode* ou_head=head->next;//第一个偶数节点是原链表的第二个节点。
        ListNode* ou=head->next;//存储目前处理好的偶数链表的最后一个节点
        ListNode* ji=head;//存储目前处理好的奇数链表的最后一个节点
        ListNode* p=ou->next;//存储目前需要处理的节点
        while(p)
        {
            if(num%2!=0)
            {//是第奇数个节点，放在奇数链表后面，奇数链表进位
                ji->next=p;
                ji=ji->next;
                
                
            }
            else
            {//是第偶数个节点，放在偶数链表后面，偶数链表进位
                ou->next=p;
                ou=ou->next;
            }
            num++;
            p=p->next;
        }
        ou->next=NULL;//将偶数链表最后一位所指置空
        ji->next=ou_head;//将偶数放在奇数后面
        return head;
    }

