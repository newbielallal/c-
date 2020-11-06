\### 题目

以 Unix 风格给出一个文件的绝对路径，你需要简化它。或者换句话说，将其转换为规范路径。

在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..） 表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。更多信息请参阅：Linux / Unix中的绝对路径 vs 相对路径

请注意，返回的规范路径必须始终以斜杠 / 开头，并且两个目录名之间必须只有一个斜杠 /。最后一个目录名（如果存在）不能以 / 结尾。此外，规范路径必须是表示绝对路径的最短字符串。



示例 1：

输入："/home/"
输出："/home"
解释：注意，最后一个目录名后面没有斜杠。
示例 2：

输入："/../"
输出："/"
解释：从根目录向上一级是不可行的，因为根是你可以到达的最高级。
示例 3：

输入："/home//foo/"
输出："/home/foo"
解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。
示例 4：

输入："/a/./b/../../c/"
输出："/c"
示例 5：

输入："/a/../../b/../c//.//"
输出："/c"
示例 6：

输入："/a//b////c/d//././/.."
输出："/a/b/c"

\### 思路

​    利用栈来进行处理，最后将栈中的元素存到res中，因为栈是只能先进后出慢慢弹出，而且每次弹出的都是一个目录一个目录弹出，所以需要先将目录逆序放到最后的结果字符串中，最后再将整个字符串逆序就得到结果了。

\### code

```cpp
class Solution {
public:
string simplifyPath(string path) { 
    stack<string> res;
    string temp;
    for (int  i=0;i<path.size();++i) {
        if (path[i] == '/')//如果是/那么就进行处理，斜杠不需要保存在栈里面。 
        {
            if (!res.empty()&&temp=="..")res.pop();//两个.就返回上一层
            else if(temp!=".."&&temp!="."&&!temp.empty())res.push(temp);//代表是一个目录
            temp.clear();//没有其它情况了，因为/是不会保存进temp的。
        } 
        else//将每个目录保存下来 
        {
            temp += path[i] ;
        }
    }
    if(!temp.empty())//最后一个目录没有/可能不会被保存进res中，要再做一次处理。
    {
            if (!res.empty()&&temp=="..")res.pop();
            else if(temp!=".."&&temp!="."&&!temp.empty())res.push(temp);
    }  
    if (res.empty())return "/";//没有目录直接返回
    string l_res;
    while (!res.empty())//不为空进行处理 
    {
        temp = res.top();
        res.pop();
        l_res += string(temp.rbegin(), temp.rend())+"/";//因为栈只能从后往前弹出
                                                       //所以最后需要翻转
    }
    reverse(l_res.begin(),l_res.end());//翻转之后就是结果。
    return l_res;
}
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)