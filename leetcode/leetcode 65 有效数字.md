\### 题目

验证给定的字符串是否可以解释为十进制数字。

例如:

"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3  " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

说明: 我们有意将问题陈述地比较模糊。在实现代码之前，你应当事先思考所有可能的情况。这里给出一份可能存在于有效十进制数字中的字符列表：

数字 0-9
指数 - "e"
正/负号 - "+"/"-"
小数点 - "."
当然，在输入中，这些字符的上下文也很重要。

更新于 2015-02-10:
C++函数的形式已经更新了。如果你仍然看见你的函数接收 const char * 类型的参数，请点击重载按钮重置你的代码。


\### 思路

​    这个题目翻译巨坑，上面的例子覆盖不够完全，总结起来应该是这样的，只有一个e或者没有e，并且e前后判断规则不一样，前面可以存在小数点，但是只能有一个，正负号必须在第一位，并且必须有数字，后面不能存在小数点，也必须有数字，正负号必须在第一位，总的来说就是细节很麻烦，因为没有用状态机，所以注意每个位置就ok了，小数点也只能有一位，但是小数点分割判断可能要复杂一点，就选的e来分割，第一次困难做到超过100%，估计是运气，但是也很开心，具体细节注释上写了。

\### code

```cpp
class Solution {
public:
    bool isNumber(string s) {
        int tail=s.size()-1;
        int head=0;
        while(tail>=0)
        {
            if(s[tail]==' ')
                --tail;
            else
                break;
        }
        while(head<=tail)
        {
            if(s[head]==' ')
                ++head;
            else
                break;
        }
        if(head>tail)
            return false;
        s = s.substr(head, tail-head+1);//去头去尾的空格
        int index = s.find('e');//只会有一个e。
        if(index == string::npos) return judgea(s);//代表不存在e
        else return judgea(s.substr(0, index)) && judgeb(s.substr(index + 1));//分成两部分处理
    }
    bool judgea(string s)
    {
        bool  have_num=false;//有没有数字
        bool have_pointed = false;//有没有小数点
        for(int i = 0; i < s.size(); i++)
        {
            if (s[i]>='0'&&s[i]<='9')//出现数字
                have_num=true;
            else if(s[i] == '+' || s[i] == '-')//可以有正负号,必须在第一位
            {
                if(i != 0) return false;
            }
            else if(s[i] == '.')//只能由一个小数点，并且只能在e的前面
            {
                if(have_pointed) return false;
                have_pointed = true;
            }
            else 
               return false;//出现其他字符

        }
        return have_num;
    }
    
    bool judgeb(string s)
    {
        bool  have_num=false;
        for(int i = 0; i < s.size(); i++)
        {
            if (s[i]>='0'&&s[i]<='9')//出现数字
                have_num=true;
           else if(s[i] == '-' || s[i] == '+')//可以有正负号,必须在第一位
            {
                if(i != 0) return false;
            }
            else //不能有小数点。
                return false;
        }
        return have_num;
    }
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



![img](https://img-blog.csdnimg.cn/20200105132954484.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)