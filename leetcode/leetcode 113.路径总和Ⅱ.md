***###题目\***

给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。**说明:** 叶子节点是指没有子节点的节点。

- **输入：**sum = 22

![img](https://pic1.zhimg.com/80/v2-09e1038e57abbb24cd0fad1db530ab00_720w.jpg)

- **输出：**[[5,4,11,2],[5,8,4,5]]

***###思路\***

利用递归的方法解决这个问题，原理就是暴力计算了每一条从根节点到叶子节点的路径，然后计算路径的和是否为sum，因为路径中的值有正有负，所以只有到达叶子节点的时候才能够确定此条路径和是否为sum，整个流程如下：

- 此节点不为空，将节点值放入数组temp中。
- 判断是否为叶子节点？如果是，计算temp的和，看是否为sum。
- 如果不是叶子节点，若节点左节点存在，那么对递归对左子节点做相同的操作。
- 若节点右节点存在，那么对递归对右子节点做相同的操作。

***###code\***

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
    void solve(TreeNode* root, int sum,vector<vector<int>>&res,vector<int>temp)
    {
        temp.push_back(root->val);
        if(root->left==NULL&&root->right==NULL)
        {
            if(accumulate(temp.begin(),temp.end(),0)==sum)
                res.push_back(temp);
            return;
        }
        if(root->left)solve(root->left,sum,res,temp);
        if(root->right)solve(root->right,sum,res,temp);
        return ;

    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>>res;
        vector<int>temp;
        if(root==NULL)return {};
        solve(root,sum,res,temp);
        return res;
    }
};
```

***###思路\***

利用循环代替递归，这里遍历节点的顺序是中序遍历，更改上一篇文章里面讲到的循环实现中序遍历实现。

具体步骤如下：

- 从根节点出发，一直向左遍历，直到遍历到的节点无左节点为止。
- 如遍历到的左边最深的节点为叶节点，计算这条路径是否满足情况。
- 然后开始遍历该节点的右节点，如果右节点不存在或者此结点是由它的右节点返回来的，那么向上回溯，若右节点不存在，如果该节点为根节点，那么上一步已经判断过这个路径了，所以需要回溯，若此节点是由它的右节点返回来的，那么代表没有找到新的路径，应该继续回溯。
- 否则一直向遍历该节点的右节点。

***###code\***

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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root) return {};

        vector<vector<int>>res; 
        vector<int> temp; //记录所有满足条件的路径、某一条满足条件的路径
        stack<TreeNode*> s; TreeNode *pre = NULL;
        while (root||!s.empty()) { 
            while (root) {
                s.push(root); 
                sum -= root->val; 
                temp.push_back(root->val); //入栈、更新sum及路径
                root = root->left;
            }//递归访问左节点

            root = s.top(); //到达最左了，此时往右
            //root是叶子结点且路径和为sum
            if (!root->left && !root->right && (sum == 0)) { 
                res.push_back(temp); //满足条件，保存路径
            }

            if (!root->right || root->right == pre) { //右结点不存在或已经访问
                s.pop(); sum += root->val; temp.pop_back(); //出栈、更新sum及路径
                pre = root; //标记已访问
                root = NULL; //用于回溯到上一级
            }
            else { //递归访问右节点
                root = root->right;
            }
        }
        return res;
    }
};
```