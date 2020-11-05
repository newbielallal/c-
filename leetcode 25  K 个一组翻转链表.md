---
title: leetcode 25 K 个一组翻转链表
tags:
  - c++ 
categories: c++ 
---
链表问题还是思路要清晰就可以了。
<!-- more -->

### 题目

给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

示例 :

给定这个链表：1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5

说明 :

你的算法只能使用常数的额外空间。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

### 思路

一样的道理，思路一定要清晰，注意几个问题：
1、链表剩下的未交换节点不足k个怎么处理
2、交换过程中怎么判断已经交换结束
3、交换过程中怎么注意不要丢失节点信息
4、交换完之后怎么更新申请的辅助节点的信息

申请的是一个辅助节点auxiliary放在待交换的节点的前面，例如要交换的k个节点为1->2->3，那就申请一个auxiliary节点放在1的前面，便于后面的交换工作，针对上面的四个问题，按照题目的意思，不足k个就不交换了，其次判断是否结束交换，判断方法是auxiliary后一个节点是否是待交换节点的最后一位（具体后面会解释），不要丢失节点信息就只能靠自己写节点的交换顺序了，可以自行推导这个过程，看是否能交换成功，辅助节点更新也是要根据节点交换完成之后具体来判断，下面就说采取的更新的方法：

假设k=4,链表为1->2->3->4->5->6->7->8->9
首先申请一个auxiliary节点指在前方，然后申请一个节点tail存储待交换k个节点的末尾，再申请一个cur节点存储下一个待交换的节点，
具体流程如下：
auxiliary->1->2->3->4->5->6->7->8->9,其中tail存储4，cur存储1，交换过程就是将1放在4的后面，然后更新cur的位置。
auxiliary->2->3->4->1->5->6->7->8->9，tail依然存储4，但是cur存储2了（这就是申请auxiliary的原因，这样可以正确的找到2的位置，只需要让cur=auxiliary->next就可以了），然后同样的，又将cur放在tail的后面，tail往前移动。
auxiliary->3->4->2->1->5->6->7->8->9,同样的道理，继续进行移动。
auxiliary->4->3->2->1->5->6->7->8->9，此时已经交换结束，就是如何判断是否交换结束呢？因为tail是存储待交换k个节点的最后一个节点的，所以只需要判断auxiliary->next是否是tail就可以了，如果是代表交换结束。
结束之后如果更改节点信息，同理，依然需要构造出一个和上一次交换相同的场景，所以针对这个例子，需要让auxiliary节点存储1就可以了，这样它就相当于也是在待交换的k个节点的前一个节点，然后tail存储8，代表最后一个，cur存储5，代表待交换的第一个。
这次交换完之后结果是auxiliary->4->3->2->1->8->7->6->5->9，然后剩下一个9，判断出不满k个，直接结束交换，具体代码可以看下面的程序。

### code
  
     class Solution {
	public:
	    ListNode* reverseKGroup(ListNode* head, int k) {
	        ListNode* res=new ListNode(0);//auxiliary会跟着变化，head也会变化，所以用res来输出结果
	        res->next=head;
	        ListNode* tail=res;
	        ListNode* auxiliary=res;
	        ListNode* cur=head;
	        while(1)
	        {
	            
	            int cout=0;
	            while(tail!=NULL&&cout<k)//判断是否满足k个剩下节点
	            {
	                tail=tail->next;
	                cout++;
	            }
	            if(tail==NULL)//如果不满足，tail==NULL，直接返回。
	                return res->next;
	            while(auxiliary->next!=tail)//这里就是交换k次
	            {
	                cur=auxiliary->next;//每次更新cur的值。
	                auxiliary->next=cur->next;//下面三条语句就是在交换这些节点。
	                cur->next=tail->next;
	                tail->next=cur;
	            }
	            auxiliary=head;//重新更新三个辅助节点的值，再完成下一次交换。
	            tail=head;
	            cur=auxiliary->next;
	            head=head->next;
	            
	        }
	        return res->next;
	    }
	};