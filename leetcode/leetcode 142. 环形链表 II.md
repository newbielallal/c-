**###题目**

给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

说明：不允许修改给定的链表。

**###思路**

其实就是面试的时候经常考到的判断一个链表是否是环形链表的进阶版本吧。先说最简单的一个办法就是：

- 首先判断该链表是否是环形链表。若不是直接返回NULL。
- 若是，将链表中的环内的全部节点保存在一个数组中。
- 然后从链表的头节点开始往后遍历，如果遍历到的节点出现在上一步设置的数组中，那么说明这个节点就是环的入口。

**###code**

```cpp
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
    ListNode *detectCycle(ListNode *head) {
        if(head==NULL)
            return NULL;
        vector<ListNode *>node;
        ListNode * p1=head;
        ListNode* p2=head;
        while(p1->next&&p2->next&&p2->next->next)
        {
            p1=p1->next;
            p2=p2->next->next;
            if(p1==p2)
            {
                while(find(node.begin(),node.end(),p1)==node.end())
                {
                    node.push_back(p1);
                    p1=p1->next;
                }
                ListNode * p3=head;
                while(find(node.begin(),node.end(),p3)==node.end())
                {
                    p3=p3->next;
                }
                return p3;
            }
            
        }
        return NULL;
    }
};
```

**###思路**

上一种方法有个问题，就是耗时太长了。

在评论区找的一个快很多的方法，依然是先利用快慢指针判断是否有环。

如果链表中有环，那么快慢指针最后相遇的节点距离环的入口的长度等于链表的头节点与环的入口的长度。

所以找到快慢指针相遇的节点，然后让head节点往后走，相遇的节点也往后走，待两者相等，就到达环的入口了。

**###code**

```cpp
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
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast=head;
        ListNode* slow=head;
        ListNode* meet=NULL;
        while(fast)//判断是否有环
        {
            slow=slow->next;
            fast=fast->next;
            if(!fast)
            {
                return NULL;
            }
            fast=fast->next;
            if(fast==slow)
            {
                meet=fast;
                break;
            }

        }
        if(meet==NULL)
        {
            return NULL;
        }
        while(head&&meet)//找环的入口。
        {
            if(head==meet)
            {
                return head;
            }
            head=head->next;
            meet=meet->next;
        }
        return NULL;
    }
};
```