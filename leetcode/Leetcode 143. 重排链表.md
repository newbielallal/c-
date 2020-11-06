**###题目**

给定一个单链表 L：L0→L1→…→Ln-1→Ln ，

将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

- 示例 1:给定链表 1->2->3->4, 重新排列为 1->4->2->3.
- 示例 2:给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.

**###思路**

整个程序的思路分为三大步来进行：

- 1、根据链表的长度将链表分为前后两部分，偶数长度的链表前后两部分平分该链表，奇数长度的链表前面部分会比后面部分多一个节点。
- 2、将后面部分链表反转，例如将4->5反转成5->4。
- 3、将前后部分组合在一起，按照一个前面部分节点，一个后面部分节点的顺序交叉组合。

具体的实现步骤可以看代码注释，单向链表的反转以及组合一定要处理好细节，避免丢失信息，在使用前就被覆盖掉了。

**###code**

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverse(ListNode* head)//反转链表
    {//将链表中的节点一个一个的插入到新链表的头部。
        ListNode* temp=new ListNode();
        while(head){
            ListNode* temp1=temp->next;
            temp->next=head;
            head=head->next;
            temp->next->next=temp1;
            
        }
        return temp->next;
    }
    void reorderList(ListNode* head) {
        ListNode* p=head;
        int l=0;
        while(p){   
            l++;
            p=p->next;
        }
        if(l<=2)return;
        int mid=l/2;
        ListNode* qian=head;
        ListNode* hou=NULL;
        p=head;
        if(l%2!=0)//找到前后链表的分界点。
            p=p->next;
        while(--mid)
            p=p->next;
        hou=reverse(p->next);//分割链表
        p->next=NULL;
        while(qian&&hou){//组合链表。
            ListNode* temp=qian->next;
            qian->next=hou;
            hou=hou->next;
            qian->next->next=temp;
            qian=temp;
        }
        return;
    }
};
```