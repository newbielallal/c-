**###数组中的字符串匹配**

给你一个字符串数组 words ，数组中的每个字符串都可以看作是一个单词。请你按任意顺序返回words 中是其他单词的子字符串的所有单词。

如果你可以删除 words[j] 最左侧或最右侧的若干字符得到 word[i] ，那么字符串 words[i] 就是 words[j] 的一个子字符串。

- 输入：words = ["mass","as","hero","superhero"]
- 输出：["as","hero"]

**题目数据保证每个 words[i] 都是独一无二的。**

**###思路**

一开始没想过暴力法能过，结果过了，那还能怎么说呢，当然是暴力法真香了。首先建立一个flag数组作为该字符串是否是其它字符串的子串的标志，这样可以减少计算，比如有 asss、as、ss、b。这样就可以知道as和ss都作为asss的子串了，那么b在未能匹配上asss的时候就不需要再对as和ss进行匹配了，肯定是匹配不上的。 用find函数判断某字符串是否为其它字符串的子串，因为题目说了是没有相同的字符串，所以可以用find判断，否则肯定是不行的。 这样用待处理的字符串和其它字符串进行比较，可以判断它是否为子串。

**###code**

```cpp
class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string>res;
        if(words.size()==0||words.size()==1)return res;//特殊情况返回
        vector<bool>flag(words.size(),false);//是否作为子串被放在res中过
        for(int i=0;i<words.size();++i)
        {
            for(int j=0;j<words.size();++j)
            {//两重循环的暴力法，
                if(i==j||flag[j]) continue;//减少计算量
                if(words[j].find(words[i])!=string::npos)
                {//能得到这个字符串
                    res.push_back(words[i]);
                    flag[i]=true;
                    break;
                }
            }
        }
        return res;
    }
};
```

**###查询带键的排列**

给你一个待查数组queries，数组中的元素为1到m之间的正整数。 请你根据以下规则处理所有待查项queries[i]：

一开始，排列 P=[1,2,3,...,m]。请你找出当前待查项 queries[i] 在排列 P 中的位置（下标从 0 开始），然后将其从原位置移动到排列 P 的起始位置（即下标为 0 处）。

注意，queries[i] 在 P 中的位置就是 queries[i] 的查询结果。

请你以数组形式返回待查数组 queries 的查询结果。

- 输入：queries = [3,1,2,1], m = 5
- 输出：[2,1,2,1]
- 解释：待查数组 queries 处理如下：对于 i=0: queries[i]=3, P=[1,2,3,4,5], 3 在 P 中的位置是 2，接着我们把 3 移动到 P 的起始位置，得到 P=[3,1,2,4,5] 。对于 i=1: queries[i]=1, P=[3,1,2,4,5], 1 在 P 中的位置是 1，接着我们把 1 移动到 P 的起始位置，得到 P=[1,3,2,4,5] 。 对于 i=2: queries[i]=2, P=[1,3,2,4,5], 2 在 P 中的位置是 2，接着我们把 2 移动到 P 的起始位置，得到 P=[2,1,3,4,5] 。对于 i=3: queries[i]=1, P=[2,1,3,4,5], 1 在 P 中的位置是 1，接着我们把 1 移动到 P 的起始位置，得到 P=[1,2,3,4,5] 。 因此，返回的结果数组为 [2,1,2,1] 。

**###思路**

在没看解释之前，我是真的没懂这个题目的意思。感觉这个中等题目有点水，就是一个查找和移动元素就可以了。

**###code**

```cpp
class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int>P(m,0);
        vector<int>res;
        for(int i=0;i<m;++i)P[i]=P[i]+i+1;//得到P数组
        for(int i=0;i<queries.size();++i)
        {
            for(int j=0;j<m;++j)
            {
                if(P[j]==queries[i])//找queries[i]的位置。
                {
                    res.push_back(j);
                    int temp=P[j];
                    for(int k=j;k>0;--k)//移动P内元素的位置。
                        P[k]=P[k-1];
                    P[0]=temp;
                    break;
                }
            }
        }
        return res;
    }
};
```

**###HTML实体解析器**

「HTML 实体解析器」是一种特殊的解析器，它将 HTML 代码作为输入，并用字符本身替换掉所有这些特殊的字符实体。

HTML里这些特殊字符和它们对应的字符实体包括：

- 双引号：字符实体为 " ，对应的字符是 " 。
- 单引号：字符实体为 ' ，对应的字符是 ' 。
- 与符号：字符实体为 & ，对应对的字符是 & 。
- 大于号：字符实体为 > ，对应的字符是 > 。
- 小于号：字符实体为 < ，对应的字符是 < 。
- 斜线号：字符实体为 ⁄ ，对应的字符是 / 。

给你输入字符串 text ，请你实现一个 HTML 实体解析器，返回解析器解析后的结果。

**###思路**

一直超时，搞的我都炸了，后来就没时间管了。逻辑挺简单的，直接找出每个&和；组成的字符串，再去对应表里面找，能找到换成对应的符号，不能就直接添加，一些特殊情况比如两个&就直接把之前的字符存入结果中，也算暴力法吧。

**###code**

```cpp
class Solution {
public:
    string entityParser(string text) {
        unordered_map<string,string>html={{"&quot;", "\""},{"&apos;", "'"},{"&amp;", "&"},{"&gt;", ">"},{"&lt;", "<"},{"&frasl;", "/"}};
         string res;
         string temp;
         for(auto i:text){
            if(i=='&'){
                if(!temp.empty())
                {
                    res=res+temp;
                    temp="";
                }
                temp.push_back(i);
            }
            else if(i==';'){
                temp.push_back(i);
                if(html.find(temp)!=html.end())res=res+html[temp];
                else res=res+temp;;
                temp="";
            }
            else temp.push_back(i);
        }
        if(!temp.empty())res=res+temp;;
        return res;
    }
};
```

**###给 N x 3 网格图涂色的方案数**

你有一个 n x 3 的网格图 ，你需要用 红，黄，绿 三种颜色之一给每一个格子上色，且确保相邻格子颜色不同（也就是有相同水平边或者垂直边的格子颜色不同）。给你网格图的行数 n 。请你返回给 grid 涂色的方案数。由于答案可能会非常大，请你返回答案对 10^9 + 7 取余的结果。

**###思路**

一看就知道，肯定是有规律的，就看找不找得出来，然后就去百度出来了，算作弊吧尴尬。假设三种颜色是r、y、g。一行的色块直接可能组成的情况是三种不同的颜色，那么是ABC，或者说两种颜色的ABA，那么ABC可能的情况是6种(3*2*1)，ABA可能的情况是6种(3*2)。所以一行的时候是12中情况，那么两行的时候呢，第一行为ABC的时候，第二行可以是CAB、CAC、BAB、BCB、BAC。那么就是每种ABC都对应5种情况，ABA对应了CAB、BAC、BAB、BCB。每种ABA的情况都对应4种情况，两行的时候是5*6+4*6=54种。到第三层的时候， 又是一样的道理，所以最后的结果=两种颜色的情况*5+三种颜色的情况*4，但是两种颜色和三种颜色的情况也在随着行数的增加而增加，这个题就是个数学题。。。。。。

**###code**

```cpp
class Solution {
public:
    int numOfWays(int n) {
            if (n == 0)return n;
            long long two= 6;
            long long thre = 6;
            for(int i = 2; i <=n; i++)
            {
                long long temp1= two*3% 1000000007+thre* 2 % 1000000007;
                long long temp2 = 2*(two+thre)%1000000007 ;
                two=temp1;
                thre=temp2;
            }
            return (int)((two + thre)%1000000007);
    }
};
```