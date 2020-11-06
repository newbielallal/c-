**###题目**

反转从位置 *m* 到 *n* 的链表。请使用一趟扫描完成反转。

**说明:**1 ≤ *m* ≤ *n* ≤ 链表长度。

- **输入:** 1->2->3->4->5->NULL, *m* = 2, *n* = 4
- **输出:** 1->4->3->2->5->NULL

**###思路**

- 首先找到第m-1个结点，如果m为1，那么m-1的结点为我们新建的一个结点。
- 然后利用pm指向第m个结点，pre指向第m-1个节点，cur指向pre的下一个结点，接下来开始反转。
- 反转的循环做n-m+1次，每次的反转规则是首先将cur的指向的结点保存下来，用于下次循环，然后再将pre指向的结点作为cur指向的结点，再将pre指向的结点更换为cur，再将开始保存的cur指向的结点赋给cur。
- 上述过程完成了一个操作，就是将从m到n的结点，从前往后的依次插入到pre结点的后面，所以叫做头插法，因为每次都是插入在首部。
- 最后让原来的第m结点指向第n+1个结点，反转结束。

因为是一次遍历，所以是0ms。

![img](https://pic1.zhimg.com/80/v2-b5fc33475647af5f6ba1cdfe01ba75fc_720w.jpg)

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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* res=new ListNode(0);
        res->next=head;
        ListNode *pre=res;
        //找到第m-1个结点
        for(int i=1;i<m;++i)
        {
            pre=pre->next;
        }
        //找到第m个结点
        ListNode* cur=pre->next,*pm=pre->next;
        //利用头插法进行反转
        for(int i=m;i<=n;++i)
        {
            ListNode *temp=cur->next;
            cur->next=pre->next;
            pre->next=cur;
            cur=temp;
        }
        //第m个节点指向n+1个结点
        pm->next=cur;
        return res->next;
    }
};
```