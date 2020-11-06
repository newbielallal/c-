\### 题目

给定一个单词数组和一个长度 maxWidth，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。

你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。

要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入额外的空格。

说明:

单词是指由非空格字符组成的字符序列。
每个单词的长度大于 0，小于等于 maxWidth。
输入单词数组 words 至少包含一个单词。
示例:

输入:
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
输出:
[
  "This   is   an",
  "example  of text",
  "justification.  "
]
示例 2:

输入:
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
输出:
[
 "What  must  be",
 "acknowledgment  ",
 "shall be     "
]
解释: 注意最后一行的格式应为 "shall be   " 而不是 "shall   be",
   因为最后一行应为左对齐，而不是左右两端对齐。    
   第二行同样为左对齐，这是因为这行只包含一个单词。
示例 3:

输入:
words = ["Science","is","what","we","understand","well","enough","to","explain",
     "to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
输出:
[
 "Science  is  what we",
 "understand    well",
 "enough to explain to",
 "a  computer.  Art is",
 "everything  else  we",
 "do          "
]


\### 思路

​    这个题目没意思是真的麻烦，要考虑每个情况，把情况都考虑清楚就基本没什么难度了，第一步先确定每一行最多能放多少个单词，第二步确定每行可以放的单词数目是不是只有一个或者是最后一行（两者的处理方法是一样的），第三步再根据两种情况分别处理。

\### code

```cpp
class Solution {
public:
vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string>res;
    int i=0;
    while(i<words.size()){
        int residue_wid=0;
        int begin=i;
        while(i<words.size() && residue_wid+words[i].size()<=maxWidth){//每一行添加最多的单词。
            residue_wid+=words[i].size()+1;
            ++i;
        }
        if(i==words.size()){//判断是否是最后一行。
            res.push_back(packagestring(words,begin,i-1,residue_wid-1,maxWidth,false));
            break;
        }
        res.push_back(packagestring(words,begin,i-1,residue_wid-1,maxWidth,true));
    }
    return res;
}

string packagestring(vector<string>& words, int starter, int ender, int strlen,int maxWidth,bool tail){
    string res="";
    if(tail && starter<ender){
        int cnt=ender-starter;//代表有几个空格位(空格个数等于字符串数-1)
        int blk=(maxWidth-strlen)/cnt+1;//每个位置最少放几个空格
        string spc=string(blk,' ');//n个空格
        int ofst=(maxWidth-strlen)%cnt;//剩下的空格。
        for(int i=starter;i<ender;++i)//左边要比右边多，但是不需要是绝对大于，直接从左往右都分配一个。
        {
            res+=words[i]+spc;//加上最少空格
            if(i-starter<ofst)res+=' ';//还有剩下的空格就加上。
        }
        res+=words[ender];
    }
    else//只有一个字符串或者最后字符串，方法是一样的，都是左对齐。
        {
        string spc=string(maxWidth-strlen,' ');//每个空格位只放一个空格，剩下的全部添加到后面。
        for(int i=starter;i<ender;++i){
            res+=words[i]+' ';
        }
        res+=words[ender]+spc;//直接添加到最后。
    }
    return res;
}
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



![img](https://img-blog.csdnimg.cn/20200105215502872.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)