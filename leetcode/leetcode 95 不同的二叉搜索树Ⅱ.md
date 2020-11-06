**###题目**

给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

- 输入: 3
- 输出:[[1,null,3,2],[3,2,null,1],[3,1,null,null,2],[2,1,3],[1,null,2,null,3]]
- 解释:以上的输出对应以下 5 种不同结构的二叉搜索树：

![img](https://pic4.zhimg.com/80/v2-a5ffb15d8d8a40eb4916f3e4c5d03f7f_720w.jpg)

**###思路**

利用递归进行处理，假设选定i作为一个树的根节点，根据二叉搜索树的性质，其左子树的所有节点为 ![[公式]](https://www.zhihu.com/equation?tex=1%5Csim%28i-1%29) ，其右子树的节点为 ![[公式]](https://www.zhihu.com/equation?tex=%28i%2B1%29%5Csim+n) ,这样通过递归算出每个节点的所有可能的左右子树的集合，再将这两个集合分别一一组成树，就得到了最后的结果。

**###code**

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n==0)return {};
        return ktl(1,n);
    }
    vector<TreeNode*> ktl(int l,int r)
    {
        if(l>r)return {NULL};//左右之间不存在结点。
        vector<TreeNode*>res;
        for(int i=l;i<=r;++i)
        {
            vector<TreeNode*> l_tree_all=ktl(l,i-1),r_tree_all=ktl(i+1,r);//左右可能的子树集合
            for(auto l_tree:l_tree_all)//将左右子树分别一一对应。
            {
                for(auto r_tree:r_tree_all)
                {
                    TreeNode *head=new TreeNode(i);
                    head->left=l_tree;
                    head->right=r_tree;
                    res.push_back(head);
                }
            }
        }
        return res;
    }
};
```