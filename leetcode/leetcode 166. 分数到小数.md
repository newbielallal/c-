**###题目**

给定两个整数，分别表示分数的分子numerator和分母denominator，以字符串形式返回小数。

如果小数部分为循环小数，则将循环的部分括在括号内。

- **输入:** numerator = 1, denominator = 2
  **输出:** "0.5"
- **输入:** numerator = 2, denominator = 3
  **输出:** "0.(6)"

**###思路**

结果分为两种情况：

1. 可以除尽，这个就不说了，一直除下去就好了。
2. 循环小数（不可能有无限不循环小数的），循环小数需要找出它的循环部分，怎么判断已经进入循环部分了呢？直接看这次除法之后的余数是否出现过，如果出现过，那么分母一直不变的，那么后续的情况肯定又是一个循环。所以余数中第二次出现某个数字，那么肯定就是开始循环了。

细节部分的处理可以看代码注释，主要注意如下几个方面：

- 正负判断
- 溢出判断
- 分母分子是否为0
- 插入括号

**##code**

```cpp
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if(numerator == 0)
        {
            return "0";
        }
        if(0 == denominator)
        {
            return "";
        }

        long long llNumerator = abs(numerator);
        long long llDenominator = abs(denominator);
        string res = "";
        unordered_map<int,int> record;
        long long remainder = 0;
        int resIndex;

        /*处理正负*/
        if((numerator > 0) ^ (denominator > 0))
        {
            res += '-';
        }
        
        /*整数部分*/
        res += to_string(llNumerator/llDenominator);

        /*小数部分*/
        remainder = llNumerator % llDenominator;
        if(0 == remainder)
        {
            return res;
        }
        res += '.';
        resIndex = res.size();
        while(0 != remainder && 0 == record.count(remainder))
        {
            record[remainder] = resIndex++;
            remainder = remainder * 10;
            res += to_string(remainder / llDenominator);
            remainder = remainder % llDenominator;
        }

        /*判断是否是因为循环才出的while*/
        if(1 == record.count(remainder))
        {
            res.insert(record[remainder],"(");
            res += ')';
        }
        return res;
    }
};
```