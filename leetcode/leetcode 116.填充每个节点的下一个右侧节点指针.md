**###题目**

定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

```cpp
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

![img](https://pic3.zhimg.com/80/v2-21aa7fba88706ee6940fd216f8c61f4e_720w.jpg)

**###思路**

看到题目要求，第一个反应就是可以利用层序遍历得到每一层的节点，再将每一层的节点按要求连接。

**###code**

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(root==NULL)return NULL;
        queue<Node*>q;
        q.push(root);
        vector<vector<Node*>>res;
        while(!q.empty())//层序遍历
        {
            int l=q.size();
            vector<Node*> temp_res;
            while(l--)
            {
                Node* temp=q.front();
                q.pop();
                temp_res.push_back(temp);
                if(temp->left)q.push(temp->left);
                if(temp->right)q.push(temp->right);
            }
            res.push_back(temp_res);
        }
        for(auto i:res)//向右连接每一层的节点
        {
            for (int j=0;j<i.size()-1;++j)
            {
                i[j]->next=i[j+1];
            }
        }
        return root;
    }
};
```

**###思路**

这个方法就是单纯的利用递归，不得不说在不考虑效率的时候，递归真的很强。其实连接规则就是将该节点的左子节点连接到它的右子节点，将它的右子节点与它右边节点的左子节点相连接，就这么递归重复这个操作就可以了，代码也是简洁易懂。

**###code**

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    void connect_l_r(Node* left,Node* right)
    {
        
        if(left)//题目说了是完美二叉树，所以左子节点存在那么右边也肯定存在
        {
            left->next=right;
            connect_l_r(left->left,left->right);
            connect_l_r(right->left,right->right);
            connect_l_r(left->right,right->left);
        }
        return;
    }
    Node* connect(Node* root) {
        if(root==NULL)return root;
        connect_l_r(root->left,root->right);
        return root;
    }
};
```