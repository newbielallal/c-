**###题目**

在 ![[公式]](https://www.zhihu.com/equation?tex=O%28n+log+n%29+) 时间复杂度和常数级空间复杂度下，对链表进行排序。

- 输入：4->2->1->3
- 输出：1->2->3->4

**###思路**

这个题目其实就难在题目要求是![[公式]](https://www.zhihu.com/equation?tex=O%28n+log+n%29+) 时间复杂度和常数级空间复杂度。就把很多简单的方法都限制了，好久没写了，后来看了评论区才写出来的。

采用的归并排序，但是因为空间复杂度的要求，所以是一个逆序的归并排序，即先相邻两个进行排序，再两两进行排序，再四个四个进行排序。在链表原来的空间上进行排序，只不过修改了每个节点的指向而已，可以看如下示意图：

- 11 11 11 11 11 11 11 11
- 1111 1111 1111 1111
- 11111111 11111111
- 1111111111111111

思路很简单，链表处理难点在于链表节点的处理。用两个函数来解决：cut函数用于链表分割，merge函数用于链表的归并。

**ListNode\* cut (ListNode\* head,int i)**

首先输入head代表的是目前未分段的链表节点的第一个节点，然后i代表的是分段长度。cut的作用就是从链表中按照给定长度i分割出一段，并返回分割出的链表段的后一个节点，也就是未分割的第一个节点，如果剩下的未分割节点不足长度i，返回空。具体如下：

链表：1->2->3->4->5->6->7 i=2

- 输入 cut(1,2) 返回3，链表变为 1->2 3->4->5->6->7
- 输入 cut(3,2) 返回5，链表变为 1->2 3->4 5->6->7
- 输入 cut(5,2) 返回7，链表变为 1->2 3->4 5->6 7
- 输入 cut(7,2) 返回NULL(长度不足)，链表变为 1->2 3->4 5->6 7

**ListNode\*merge(ListNode\* temp1,ListNode\* temp2)**

最常用的归并函数，没什么好说的，就是按照大小将两个链表合并起来。

具体的看注释吧。

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
ListNode* sortList(ListNode* head) {
    ListNode temp(0);//用于最后返回结果
    temp.next=head;
    ListNode * p=head;
    int length=0;

    while (p)//统计链表长度
    {
        length++;
        p=p->next;
    }

    for (int i=1;i<length;i=i<<1)//i的大小从1..2..4..8
    {
        ListNode* temp1=temp.next;//从链表的第一个节点开始分割
        ListNode* temp2=&temp;//temp.next一定要指向每次归并后的第一个节点

        while(temp1)//判断是否分割完
        {
            ListNode* temp3=temp1;
            ListNode* temp4=cut(temp3,i);
            temp1=cut(temp4,i);

            temp2->next=merge(temp3,temp4);//将分割完的两个归并
            while(temp2->next)
            {
                temp2=temp2->next;
            }
        }

    }
    return temp.next;
    }

ListNode* cut(ListNode* head,int i)
{
    ListNode *p=head;
    while(--i&&p)
    {
        p=p->next;
    }

    if(p==NULL)return NULL;
    ListNode* next = p->next;
    p->next = NULL;
    return next;
}

ListNode* merge(ListNode* temp1,ListNode* temp2)
{
    ListNode temp(0);
    ListNode *p=&temp;
    while(temp1&&temp2)
    {
        if(temp1->val > temp2->val)
        {
            p->next=temp2;
            temp2=temp2->next;
            p=p->next;
        }
        else
        {
            p->next=temp1;
            temp1=temp1->next;
            p=p->next;
        }
    }
    p->next=temp1 ? temp1:temp2;
    return temp.next;
} 
};
```