**###题目**

给定一个字符串，逐个翻转字符串中的每个单词。

- 输入: "the sky is blue"
- 输出: "blue is sky the"



- 输入: " hello world! "
- 输出: "world! hello"
- 解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。



- 输入: "a good example"
- 输出: "example good a"
- 解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

**###思路**

第一反应就是用栈就可以了。因为每个字符串只有相对顺序是逆序的，字符串内部的单词并没有变化，所以只要将每个单词压入栈中，待全部压入栈中之后再弹出就可以了，思路比较简单，主要是要注意一些细节上的地方。不过对进阶要求就是要去原地解法了。在解法二里面介绍吧。

**###code**

```cpp
class Solution {
public:
string reverseWords(string s) {
    stack<string>temp;
    string temp_str;
    for(auto i:s)
    {
        if(i==' ')//如果遇到空格
        {
            if(temp.empty()&&temp_str=="")continue;//字符串首部的空格直接删除
            if(temp_str!="")//字符串中间的空格，代表此时一个单词结束了。
            {
                temp.push(temp_str);
                temp_str="";
                continue;
            }
            else continue;//多个重复的空格
        }   
        temp_str+=i;//一个单词没完，继续添加。
    }
    if(temp_str!="")temp.push(temp_str);//最后可能有单词未被添加到栈中
    s="";
    while(!temp.empty())//将栈中的单词按照" "+单词的形式重新排列
    {
        s=s+' ';
        s=s+temp.top();
        temp.pop();
    }
    if(s=="")return s;//字符串为空的情况下直接返回。
    s.erase(s.begin(), s.begin()+1);//删除第一个多余的空格。
    return s;
}
};
```

**###思路**

原地算法是不使用额外的内存空间，原理上可能比上一个算法更好理解，就是代码实际写的时候难度大一点。

1. 首先将字符串整个翻转，这样字符串就从相对逆序变成正序了，只是每个单词自身是逆序的。
2. 找到字符串中每个单词的起点和终点，然后将起点和终点范围内的字符翻转。
3. 删除掉前后两端多余的空格。

大概的一个思路流程是上面那样，不过代码具体实现细节不同，可以看注释。

**###code**

```cpp
class Solution {
public:
    string reverseWords(string s) {
        int start=0,end=0,index=0;//index指向正常调整好顺序的单词，
        //start、end分别代表一个单词的起点和终点。

        reverse(s.begin(),s.end());//翻转
        for(;start<s.size();++start)
        {
            if(s[start]==' ')continue;//跳过多余空格
            if (index!=0) s[index++] = ' ';//从第二个单词开始每个单词头部插入空格
            end = start;//start和end此时都指向待处理单词的第一个字符
            while(end<s.size()&&s[end]!=' ')//将它往前移，肯定不会覆盖。
            {
                s[index++]=s[end++];
            }
            //上述循环遇到空格停止，代表找到一个单词了，翻转这个单词
            reverse(s.begin()+index-end+start,s.begin()+index);
            start=end;//更新下新单词的起点。
        }
        s.erase(s.begin()+index,s.end());//由于有多余的空格，所以删除掉多余的空格和多余的字符。
        return s;
    }
};
```