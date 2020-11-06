**###题目**

给定一个二维网格和一个单词，找出该单词是否存在于网格中。单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

**###思路**

利用回溯法，从二维网格的每一个字符出发，从上下左右四个方向看是否能够找到最后组成word的相邻字母，注意的就是一点，用过的字母我们将其设置为空格，如果此路不通，那么回溯的时候记得将用过的字母从空格还原成原来那个字符。

**###code**

```

class Solution {
public:
bool hs(vector<vector<char>>& board, string& word,int i,int j,int l)
{
    if(board[i][j]!=word[l])return false;
    if(l+1==word.size())return true;//达成要求返回true
    char temp=board[i][j];//将用过的保存起来
    board[i][j]=' ';
    //四个方回溯
    if( (i-1>=0 && hs(board, word, i-1, j, l+1)) 
    || (j+1<=board[0].size()-1 && hs(board, word, i, j+1, l+1))
    || (i+1<=board.size()-1 && hs(board, word, i+1, j, l+1))
    || (j-1>=0 && hs(board, word, i, j-1, l+1)) ) return true;
    board[i][j]=temp;//回溯失败，将其重置
    return false;
} 
bool exist(vector<vector<char>>& board, string word) {
    for(int i=0;i<board.size();++i)//尝试从每一个字母开始回溯。
    {
        for(int j=0;j<board[0].size();++j)
            if(hs(board,word,i,j,0))return true;
    }
    return false;
}
};
```

