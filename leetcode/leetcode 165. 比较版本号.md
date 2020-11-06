**###题目**

比较两个版本号 version1 和 version2。

如果 version1 > version2 返回 1，如果 version1 < version2 返回 -1， 除此之外返回 0。

你可以假设版本字符串非空，并且只包含数字和 . 字符。

. 字符不代表小数点，而是用于分隔数字序列。

例如，2.5 不是“两个半”，也不是“差一半到三”，而是第二版中的第五个小版本。

你可以假设版本号的每一级的默认修订版号为 0。例如，版本号 3.4 的第一级（大版本）和第二级（小版本）修订号分别为 3 和 4。其第三级和第四级修订号均为 0。

**###思路**

思路挺简单的，以小数点分割这个版本号，然后比较两个版本号对应数字段的大小，举例就是a.b.c.d和1.2.3.4比较，那么就是a和1比较，b和2比较，c和3比较，d和4比较，一旦出现大小差异就直接返回1或者-1.

如果说两个版本号的小数点不一样多，那么继续比下去，不过其中版本号短的那个后面的数字全都是0，版本号长的那个的继续按小数点分割。

具体的可以看注释。

**##code**

```cpp
class Solution {
public:
    int compareVersion(string version1, string version2) {

        int index1 = 0;//用来保存比较到了第几个。
        int index2 = 0;

        while(index1<version1.size() || index2 < version2.size())//是或不是并，因为不一定一样长
        {
            int num1 = 0;//记录每个版本号每一段的值
            int num2 = 0;
            while(index1 <version1.size() && version1[index1]!='.')
            {
                num1 = num1*10 + (version1[index1] - '0');
                index1++;
            }

            while(index2 <version2.size() && version2[index2]!='.')
            {
                num2 = num2*10 + (version2[index2] - '0');
                index2++;
            }

            if(num1 > num2)//比较大小
            {
                return 1;
            }
            if(num1 < num2)
            {
                return -1;
            }
            index1++;
            index2++;
        }
        return 0;
    }
};
```