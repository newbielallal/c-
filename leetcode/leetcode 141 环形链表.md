---
title: leetcode 141 环形链表
tags:
  - c++ 
categories: c++ 
---
这也是一个利用双指针就能很好的解决的问题，两个指针利用不同的速度遍历链表。
<!-- more -->

### 题目
给定一个链表，判断链表中是否有环。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
### 思路
如果链表中存在环，那么肯定不可能遍历到NULL，所以出现NULL，直接输出false，我们将两个指针一个一次移动一步，一个一次移动两步，这样如果存在一个环，并且在循环一段时间后两个指针都会入环，因为是在一个圆环中，所以前后其实是相对的，那么一个节点每次移动两个，一个移动一个，这样就在往前追另一个节点，在环中就肯定可以追上，所以加个判定两个指针相同，就算找到环了。
### code
    bool hasCycle(ListNode *head) {
        if(head ==NULL)
            return false;
        ListNode *p1=head;
        ListNode *p2=head;
        while(p1->next&&p2->next&&p2->next->next)
        {
            p1=p1->next;
            p2=p2->next->next;
            if(p1==p2)
                return true;
        }
        return false;
    }

