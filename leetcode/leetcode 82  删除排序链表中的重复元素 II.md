---
title:  82. 删除排序链表中的重复元素 II(C++)
tags:
  - c++ 
categories: c++ 
---

删除重复节点，可以用一个节点的next和next->next进行比较，这样跳出该节点，也好进行比较和删除。
<!-- more -->

### 题目

给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。

示例 1:

输入: 1->2->3->3->4->4->5
输出: 1->2->5
示例 2:

输入: 1->1->1->2->3
输出: 2->3

### 思路

思路也不是很难，就是遇到重复的就删除掉，具体可以看下面的注释。

### code

    ListNode* deleteDuplicates(ListNode* head) {
        ListNode*  list=new ListNode(0);
        ListNode*  list_be=list;
        list->next=head;//因为头结点也可以是重复的，所以也要进行比较。
        while(list->next!=NULL)
        {
            //找到两个相同的值了，
            if(list->next->next!=NULL&&list->next->val==list->next->next->val)
            {
                int num=list->next->val;//将这个重复数值记录下来，因为可能会有多个重复的，要多比较一下。
                while(list->next!=NULL)
                {
                    if(list->next->val==num)//进行比较，重复的就删除。
                    {
                        
                        ListNode* delete_node=list->next;
                        list->next=delete_node->next;
                        delete delete_node;
                    }
                    else//遍历到非重复节点，退出本层循环
                        break;
                }
                continue;//因为可能list->next也是重复项中的一项，所以不能直接跳过它，也要进行比较。
            }
            list=list->next;//list->next和list->next->next不相等，所以可以直接next。
        }
        ListNode*  res=list_be->next;
        delete list_be;
        return res;
    }
};


