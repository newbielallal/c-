**###题目**

对链表进行插入排序。

插入排序算法：

- 插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
- 每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
- 重复直到所有输入数据插入完为止。

**###思路**

就是将插入排序的思想用在链表上，不过需要注意几个点：

因为链表不是随机迭代器，所以需要用一个pre节点来保存链表的头部的位置，一个tail来保存已经排好序的链表节点的最后一位，一个now来存储当前待排序的节点。

剩下的就和插入排序一样了，首先比较now节点的值与tail节点的值的大小，如果now节点的值更大，那么代表从head节点到now节点是有序的，直接将now和tail同时往后走。

如果now节点的值小于tail节点的值，从pre节点开始往后遍历，找到第一个大于now值的节点，将now插入到它的前面，然后tail不变，now重新赋值为tail->next，这里面注意赋值的顺序，不然容易丢失节点信息。

**###code**

```cpp
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(head==NULL||head->next==NULL)
            return head;
        ListNode* pre=new ListNode(0);
        ListNode* tail=head;
        ListNode* now=tail->next;
        pre->next=head;
        while(now)
        {
            if(now->val>=tail->val)//直接接在最后面
            {
                now=now->next;
                tail=tail->next;
            }
            else
            {
                ListNode* temp=pre;//找出第一个大于now节点值得节点。
                while(temp->next&&temp->next->val<=now->val)
                {
                    temp=temp->next;
                }//排好序得节点中插入now节点。
                tail->next=now->next;
                now->next=temp->next;
                temp->next=now;
                now=tail->next;
            }
        }
        return pre->next;
    }
};
```