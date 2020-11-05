**1.两数之和**

给定一个整数数组和一个目标值，找出数组中和为目标值的**两个**数。

你可以假设每个输入只对应一种答案，且同样的元素不能被重复利用。

```python
class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        zidian={}
        for i,v in enumerate(nums):
            if target-v in zidian:
                return (zidian.get(target-v),i)
            zidian[v]=i
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**7.反转整数**

给定一个 32 位有符号整数，将整数中的数字进行反转。

```python
class Solution:
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        
        ans=0
        a=abs(x)
        while a :
            ans=ans*10+a%10
            a=a//10
        if ans>2**31 and -ans<-2**31:
            return 0
        return ans if x>0 else -ans
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**9.回文数**

判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

```python
class Solution:
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        if x<0:
            return False
        a=[]
        b=x
        c=0
        while b :
            a.append(b%10)
            b=b//10
        l=len(a)
        for i in range(l):
            c=c*10+a[i]
       
        return c==x
```

![点击并拖拽以移动](C:\Users\Administrator\Desktop\点击并拖拽以移动.gif)

**13.罗马数字转整数**

给定一个罗马数字，将其转换成整数。

返回的结果要求在 1 到 3999 的范围内。

```python
class Solution:
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        
        contrast={'I':1,'V':5,'X':10,'L':50,'C':100,'D':500,'M':1000}
        a=0
        l=len(s)
        for i in range(l-1):
            if contrast[s[i]]>=contrast[s[i+1]]:
                a=a+contrast[s[i]]
            if contrast[s[i]]<contrast[s[i+1]]:
                a=a-contrast[s[i]]
        a=a+contrast[s[-1]]
        return a
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**14.最长公共前缀**

编写一个函数来查找字符串数组中的最长公共前缀。

```python
class Solution:
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        res=''
        if not strs:
            return ''
        for i in range(len(strs[0])):
            for a in range(1,len(strs)):
                if i >= len(strs[a]) or strs[0][i]!=strs[a][i]:
                    return res
            res=res+strs[0][i]
        return res
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**20.有效的括号**

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串，判断字符串是否有效。

有效字符串需满足：

1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。
3. 字符串为空。

```python
class Solution:
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        a=[]
        jude=['(','[','{']
        for x in s:
            if x in jude:
                a.append(x)
            elif x==')':
                if a and a[-1]=='(':
                    a.pop()
                else :
                    return False
            elif x==']':
                if a and a[-1]=='[':
                    a.pop()
                else :
                    return False
            elif x=='}':
                if a and a[-1]=='{':
                    a.pop()
                else :
                    return False
        return len(a)==0
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**26.删除排序数组中的重复项**

给定一个排序数组，你需要在**[原地](http://baike.baidu.com/item/原地算法)**删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在**[原地](https://baike.baidu.com/item/原地算法)修改输入数组**并在使用 O(1) 额外空间的条件下完成。

```python
class Solution:
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0
        left=''
        num=0
        for i in range(len(nums)):
            if nums[i]!=left:
                
                left=nums[i]
                nums[num]=nums[i]
                num=num+1
        return num
            
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**27.移除元素**

给定一个数组 *nums* 和一个值 *val*，你需要**[原地](https://baike.baidu.com/item/原地算法)**移除所有数值等于 *val* 的元素，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在**[原地](https://baike.baidu.com/item/原地算法)修改输入数组**并在使用 O(1) 额外空间的条件下完成。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素

```python
class Solution:
    def removeElement(self, nums, val):
        """
        :type nums: List[int]
        :type val: int
        :rtype: int
        """        
        i=0
        while i<len(nums):
            if val==nums[i]:
                nums.pop(i)
                i=i-1                
            i=i+1
        
        return len(nums) 
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**28.实现strstr（）**

实现 [strStr()](https://baike.baidu.com/item/strstr/811469) 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回 **-1**

```python
class Solution:
    def strStr(self, haystack, needle):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """
        
        if not needle:
            return 0
        if (not haystack) or len(haystack)<len(needle):
            return -1
        for i in range(len(haystack)-len(needle)+1):
            a=0
            for b in range(len(needle)):
                if haystack[i+a]==needle[a]:
                    a=a+1
                if a==len(needle):
                    return i
                
        return -1
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**35.搜索插入位置**

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素

```python
class Solution:
    def searchInsert(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        if  nums[0]>target:
            return 0
        if  nums[-1]<target:
             return len(nums)
        for i in range(len(nums)):
            if target==nums[i]:
                return i
            if nums[i]>target and nums[i-1]<target:
                return i
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**38.报数**

```python
class Solution(object):
    def countAndSay(self, n):
        """
        :type n: int
        :rtype: str
        """
        res = ["1"]
        for i in range(n):
            num = res[i]
            temp = num[0]#当前的值
            count = 0#计数
            ans = ""#第n+1个数字的结果
            for j in range(0,len(num)):
                if num[j] == temp:
                    count += 1
                else:
                    ans += str(count)
                    ans += str(temp)
                    temp = num[j]
                    count = 1
            ans += str(count)
            ans += str(temp)
            res.append(ans)
        return res[n-1]
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**53. 最大子序和**

```python
class Solution:
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        maxsum=nums[0]
        a=0            
        for i in range(len(nums)):
            if a>0:
                a=a+nums[i]
            else: a=nums[i]                
            if a>maxsum:
                maxsum=a
        return maxsum
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**58.最后一个单词的长度**

```python
class Solution:
    def lengthOfLastWord(self, s):
        """
        :type s: str
        :rtype: int
        """
        number=0
        if not s:
            return 0
        if ' ' not in s:
            return len(s)
        for i in range(len(s)):
            if s[-i-1]!=' ':
                number+=1
            if s[-i-1]==' ' and number>0:
                return number
        return number
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**66.加一**

```
class Solution(object):
    def plusOne(self, digits):
        """
        :type digits: List[int]
        :rtype: List[int]
        """
        a=0
        b=[]
        for i in range (len(digits)) :
            a=digits[i]+a*10
        a=a+1
        
        while a>0:
            b.append(a%10)
            a=a/10
        
        b.reverse()
        
        return b
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**67.二进制求和**

```python
class Solution(object):
  def addBinary(self, a, b):
    """
    :type a: str
    :type b: str
    :rtype: str
    """
    return bin(int(a,2)+int(b,2))[2:]
    """ 
    a, b = int('0b' + a, 2), int('0b' + b, 2)
     return bin(a + b)[2:]
     """
```

**69.Sqrt(x)**

```python
class Solution:
    def mySqrt(self, x):
        """
        :type x: int
        :rtype: int
        """
        if x==0 or x==1:
            return x
        left = 1  
        right = x//2          
        while left<=right:
            mid=(left+right)//2
            if (x>mid*mid):
                left=mid+1
                lastmid=mid
            elif (x<mid*mid):
                right=mid-1
            else :
                return mid
        return lastmid      
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**70.爬楼梯**

```python
class Solution(object):
  def climbStairs(self, n):
    """
    :type n: int
    :rtype: int
    """
    if n<= 2:
      return n
    f = 1
    s = 2
    res =0
    for i in range(2,n):
      res = f+s
      f = s
      s = res
    return res
```



**88.合并两个有序数组**

```python
class Solution:
  def merge(self, nums1, m, nums2, n):
    """
    :type nums1: List[int]
    :type m: int
    :type nums2: List[int]
    :type n: int
    :rtype: void Do not return anything, modify nums1 in-place instead.
    """
    nums1[m:]=nums2[:]
    nums1.sort()
```

**118.Pascal's Triangle**

```python
class Solution:
    def generate(self, numRows):
        """
        :type numRows: int
        :rtype: List[List[int]]
        """
        if not numRows:
            return []
        p = [1]
        r = [p]
        i = 1
        while i < numRows:
            i+=1
            s = [0] * i
            p = [0] + p + [0]
            for j in range(i):
                s[j] = p[j] + p[j+1]
            r.append(s)
            p = s 
        return r
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**119.杨辉三角 II**

```python
class Solution(object):
  def getRow(self, rowIndex):
    """
    :type rowIndex: int
    :rtype: List[int]
    """
    if rowIndex==0:
      return [1]
    a=[1]
    for i in range(1,rowIndex+1):
      c=[]
      c.append(a[0])
      if i>1:
        for b in range(1,i):
          c.append(a[b]+a[b-1])
      c.append(a[-1])
      a=c
    return c
```

122. **买卖股票的最佳时机 II**

```python
class Solution(object):
  def maxProfit(self, prices):
    """
    :type prices: List[int]
    :rtype: int
    """
    profit=0
    for i in range(1,len(prices)):
      if (prices[i]-prices[i-1])>0:
        profit+=prices[i]-prices[i-1]
    return profit
```

**121.Best Time to Buy and Sell Stock**

```python
class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        
        if len(prices) < 2:
            return 0
        maxProfit=0#最大值至少为0  
        minPurchase=prices[0]#初始化最小购买值  
        for price in prices:  
            maxProfit=max(maxProfit,price-minPurchase)#最大利润为当前值与最小购买值之差和maxProfit的比较  
            minPurchase=min(price,minPurchase)#最小购买值为当前值与minPurchase之间的比较  
        return maxProfit  
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**125.验证回文串**

```python
class Solution(object):
  def isPalindrome(self, s):
    """
    :type s: str
    :rtype: bool
    """
    a=''
    for i in s:
      if i.isalpha() or i.isdigit():
        a=a+i
    a=a.lower()
    for i in range(len(a)/2):
        if a[i]!=a[len(a)-1-i]:
            return False
        return True
```

**136.只出现一次的数字**

给定一个整数数组，除了某个元素外其余元素均出现两次。请找出这个只出现一次的元素。

```python
class Solution:
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        l=len(nums)
        print(l,nums)
        if l>1:
            for i in range(0,l-1,2):
                if nums[i]!=nums[i+1]:
                    return nums[i]
                
        else: 
            return nums[0]
        return nums[-1]
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**137 只出现一次的数字 II**

```python
class Solution(object):
  def singleNumber(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    count=sum(nums)
    a=sum(set(nums))
    return (3*a-count)/2
```

**167.两数之和2**

给定一个已按照***升序排列\*** 的有序数组，找到两个数使得它们相加之和等于目标数。

函数应该返回这两个下标值 index1 和 index2，其中 *index1* 必须小于 *index2。*请注意，返回的下标值（index1 和 index2）不是从零开始的。

你可以假设每个输入都只有一个解决方案，而且你不会重复使用相同的元素。

**输入：**数组 = {2, 7, 11, 15}, 目标数 = 9
**输出：***index1* = 1, *index2* = 2

```python
class Solution:
    def twoSum(self, numbers, target):
        """
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        """
        zidian={}
        for i,v in enumerate(numbers):
            if target-v in zidian:
                return (zidian.get(target-v)+1,i+1)
            zidian[v]=i
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**168 Excel Sheet Column Title**

```python
class Solution:
    def convertToTitle(self, n):
        """
        :type n: int
        :rtype: str
        """
        result = ""
        while n != 0:
            result = chr((n-1)%26+65) + result
            n = int((n-1)/26)
        return result
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**169 Majority Element**

```python
class Solution:
    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums)==1:
            return nums[0]
        a=[]
        nums.sort()
        for i in range(len(nums)//2+1):
            if nums[i]==nums[len(nums)//2+i]:
                return nums[i]
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**171 Excel表列序号**

```python
class Solution(object):
  def titleToNumber(self, s):
    """
    :type s: str
    :rtype: int
    """
    num=0
    for i in range(len(s)-1,-1,-1):
      num += (ord(s[i]) - 64) * 26**(len(s)-i-1)
    return num
```

**172 阶乘后的零**

```python
class Solution:
  def trailingZeroes(self, n):
    """
    :type n: int
    :rtype: int
    """
    if n==0:
      return 0
    else:
      return int(n/5)+int(self.trailingZeroes(n/5))
```

**189.旋转数组**

```python
class Solution:
  def rotate(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: void Do not return anything, modify nums in-place instead.
    """
    nums[:] = nums[-k:]+nums[:-k]
```

**190.颠倒二进制位**

```python
class Solution:
  \# @param n, an integer
  \# @return an integer
  def reverseBits(self, n):
    z=bin(n)[2:]
    z="0"*(32-len(z))+z
    z=z[::-1]
    return int(z,2)
```

​      

**191 Number of 1 Bits**

```python
class Solution(object):
    def hammingWeight(self, n):
        """
        :type n: int
        :rtype: int
        """
        return bin(n).count('1')
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**198 打家劫舍**

```python
class Solution(object):
  def rob(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    if nums==[]:
      return 0
    if len(nums)==1:
      return max(nums)
    dp = [0]*len(nums)
    dp[0] = nums[0]
    dp[1] = max(nums[1],nums[0])
    for i in range(2,len(nums)):
      dp[i] = max(dp[i-1],dp[i-2]+nums[i])
    return dp[len(nums)-1]
```

**202 快乐数**

```python
class Solution(object):
  def isHappy(self, n):
    """
    :type n: int
    :rtype: bool
    """
    the_number=[]
    test_n=n
    test_number=0
    while test_n!=1:
      test_number=0
      while test_n>0:
        test_number+=(test_n%10)**2
        test_n=test_n/10
      if  test_number in the_number :
        return False
      the_number.append(test_number)
      test_n=test_number
    return True  
```

**204 计数质数**

```python
class Solution:
  def countPrimes(self, n):
    """
    :type n: int
    :rtype: int
    """
    if n < 3:
      return 0
    prime = [1] * n
    prime[0] = prime[1] = 0
    for i in range(2, int(n**0.5) +1):
      if prime[i] == 1:
        prime[i*i:n:i] = [0]*len(prime[i*i:n:i])
    return sum(prime)
```

**205 同构字符串**

```python
class Solution(object):
  def isIsomorphic(self, s, t):
    """
    :type s: str
    :type t: str
    :rtype: bool
    """
    hashmap = {}
    for i in xrange(len(s)):
      if s[i] not in hashmap:
        hashmap[s[i]] = t[i]
      elif hashmap[s[i]] != t[i]:
        return False
    mapval = [hashmap[k] for k in hashmap]
    return len(mapval) == len(set(mapval))
```

**215 数组中的第K个最大元素**

```python
class Solution(object):
  def findKthLargest(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    nums.sort()
    return nums[-k]
```

**217  存在重复元素**

```python
class Solution:
  def containsDuplicate(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    if len(nums) == 0 or len(nums) == 1:
      return False
    d = {}
    for i in nums:
      if i in d:
        return True
      d[i] = 0
    return False
```

**219 存在重复元素 II**

```python
class Solution(object):
  def containsNearbyDuplicate(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: bool
    """
    t={}
    for i in range(len(nums)):
      if(nums[i] in t and i-t[nums[i]]<=k):
        return True
      else:
        t[nums[i]]=i
    return False
```



**231 2的幂**

```python
class Solution(object):
  def isPowerOfTwo(self, n):
    """
    :type n: int
    :rtype: bool
    """
    i=0
    while 2**i<=n:
      if 2**i==n:
        return True
      else:
        i=i+1
    return False
```

**242 有效的字母异位词**

```python
class Solution(object):
  def isAnagram(self, s, t):
    """
    :type s: str
    :type t: str
    :rtype: bool
    """
    dict_num={}
    for i in s:
      if i not in dict_num:
        dict_num[i]=1
      else:
        dict_num[i]+=1
    dict_num1={}
    for i in t:
      if i not in dict_num1:
        dict_num1[i]=1
      else:
        dict_num1[i]+=1
    print(dict_num,dict_num1)
    for i in dict_num:
      if i not in dict_num1:
        return False
      if dict_num[i]!=dict_num1[i]:
        return False
    for i in dict_num1:
      if i not in dict_num:
        return False
    return True
```

**258.各位相加**

```python
class Solution(object):
  def addDigits(self, num):
    """
    :type num: int
    :rtype: int
    """
    a=str(num)
    b=0
    for i in a:
      b=b+int(i)
    while b>9:
      a=str(b)
      b=0
      for i in a:
        b=b+int(i)
    return b
```

**263 丑数**

```python
class Solution(object):
  def isUgly(self, num):
    """
    :type num: int
    :rtype: bool
    """
    while num>0 and num%2==0:
      num/=2
    while num>0 and num%3==0:
      num/=3
    while num>0 and num%5==0:
      num/=5
    return True if num==1 else False
```

**268 Missing Number**

```python
class Solution:
    def missingNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        for i in range(len(nums)):
            if i!=nums[i]:
                return i
        return i+1
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)
**283 Move Zeroes**

```python
class Solution:
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        for i in range(len(nums)):
               if nums[i]==0:
                    nums.remove(0)
                    nums.append(0)
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**287 寻找重复数**

```python
class Solution(object):
  def findDuplicate(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    nums.sort()
    a=0
    for i in nums:
      if a==i:
        return a
      a=i
```

**290 单词模式**

```python
class Solution:
  def wordPattern(self, pattern, str):
    """
    :type pattern: str
    :type str: str
    :rtype: bool
    """
    listPattern = list(pattern)
    listStr = str.split(' ')
    if len(listPattern) != len(listStr):
      return False     
    setPattern = set()
    setTuple = set()
    setStr = set()
    for i in range(len(listPattern)):
      if listPattern[i] in setPattern or listStr[i] in setStr:
        if (listPattern[i], listStr[i]) not in setTuple:
          return False
      else:
        setTuple.add((listPattern[i], listStr[i]))
        setPattern.add(listPattern[i])
        setStr.add(listStr[i])
    return True
```



**292.nim游戏**

您和您的朋友，两个人一起玩 [Nim游戏](https://baike.baidu.com/item/Nim游戏/6737105)：桌子上有一堆石头，每次你们轮流拿掉 1 到 3 块石头。 拿掉最后一块石头的人就是胜利者。由您来开局。

你们两个都是聪明人，相信都有最佳的游戏策略。 请编写一个函数，来判断您是否可以在给定的石头数量的情况下赢得游戏。

比方说，如果堆中有4块石头，那么你永远不会赢得比赛：无论你拿走的是 1块，2块 还是 3块 石头，最后一块石头总是会被你的朋友拿走。

```python
class Solution:
    def canWinNim(self, n):
        """
        :type n: int
        :rtype: bool
        """
        if n%4==0:
            return False
        else:
            return True
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**326 3的幂**

```python
class Solution(object):
  def isPowerOfThree(self, n):
    """
    :type n: int
    :rtype: bool
    """
    if n==0:
      return False
    while n/3 :
      n=n/3
      print(n)
      if n==1:
        return True
      if n<3:
        return False
```

**342 4的幂**

```python
class Solution(object):
  def isPowerOfFour(self, num):
    """
    :type num: int
    :rtype: bool
    """
    i=0
    while 4**i<=num:
      if 4**i==num:
        return True
      else:
        i=i+1
    return False
```

**344.反转字符串**

```python
class Solution:
  def reverseString(self, s):
    """
    :type s: str
    :rtype: str
    """
    a=[]
    b=''
    for i in s:
      a.append(i)
    for i in range(len(a)):
      b=b+a[-i-1]
    return b
```

**345 反转字符串中的元音字母**

```python
class Solution:
  def reverseVowels(self, s):
    """
    :type s: str
    :rtype: str
    """
    yuanyin=['a','e','i','o','u','A','E','I','O','U']
    l=0
    r=len(s)-1
    s=list(s)
    while l<r:
      if s[l] not in yuanyin:
        l=l+1
        continue
      if s[r] not in yuanyin:
        r=r-1
        continue
      s[l],s[r]=s[r],s[l]
      l+=1
      r-=1
    return ''.join(s)
```

**349 两个数组的交集**

```python
class Solution:
  def intersection(self, nums1, nums2):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :rtype: List[int]
    """
    a=[]
    b=[]
    for i in range(len(nums1)):
      if  nums1[i] in nums2:
        a.append(nums1[i])
    for ib in a:
      if ib not in b:
        b.append(ib)
    return b
```

### 350. 两个数组的交集 II

```python
class Solution:
  def intersect(self, nums1, nums2):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :rtype: List[int]
    """
    b=[]
    for i in nums1:
      if i in nums2:
        b.append(i)
        nums2.remove(i)
    return b
```

**367 有效的完全平方数**

```python
class Solution(object):
  def isPerfectSquare(self, num):
    """
    :type num: int
    :rtype: bool
    """
    if num==1:
      return True
    if num<4:
      return False
    l,r=0,num
    while l<r:
      mid=(l+r)/2
      n=mid**2
      if n<num and (mid+1)**2>num:
        return False
      if n==num:
        return True
      if n<num:
        l=mid+1
      if n>num:
        r=mid
    return False
```

**371 两整数之和**

```python
class Solution:
  def getSum(self, a, b):
    """
    :type a: int
    :type b: int
    :rtype: int
    """
    if 0 == b:
      return a
    cor = a ^ b
    cand = a & b
    return sum([cor, cand << 1])
```

**374 猜数字大小**

```python
# The guess API is already defined for you.
# @param num, your guess
# @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
# def guess(num):

class Solution(object):
  def guessNumber(self, n):
    """
    :type n: int
    :rtype: int
    """
    l=0
    r=n
    while l<=r:
      mid=(l+r)/2
      a=guess(mid)
      if a==0:
        return mid
      elif a==1:
        l=mid+1
      else:
        r=mid-1
```

**383 赎金信**

```python
class Solution:
  def canConstruct(self, ransomNote, magazine):
    """
    :type ransomNote: str
    :type magazine: str
    :rtype: bool
    """
    dict_l={}
    for i in ransomNote:
      if i in dict_l:
        dict_l[i]+=1
      else:
        dict_l[i]=1
    dict_z={}
    for i in magazine:
      if i in dict_z:
        dict_z[i]+=1
      else:
        dict_z[i]=1
    for key in dict_l:
      if key not in dict_z:
        return False
      if dict_l[key]>dict_z[key]:
        return False
    return True
```

**387 字符串中的第一个唯一字符**

```python
class Solution(object):
  def firstUniqChar(self, s):
    """
    :type s: str
    :rtype: int
    """
    dit={}
    a=[]
    for i in s:
      if i not in dit:
        dit[i]=1
      else:
        dit[i]+=1
    for key,values in  dit.items():
      if values==1:
        a.append(s.index(key))
    if a :
      return min(a)
    else:
      return -1
```

**389 找不同**

```python
class Solution(object):
  def findTheDifference(self, s, t):
    """
    :type s: str
    :type t: str
    :rtype: str
    """
    return list(collections.Counter(t)-collections.Counter(s))[0]
```

**400 第N个数字**

```python
class Solution(object):
  def findNthDigit(self, n):
    """
    :type n: int
    :rtype: int
    """
    digit=1
    base=9
    ith=1
    while n>base*digit:
      n=n-base*digit
      digit=digit+1
      ith=ith+base
      base=base*10
    return ord(str(ith+(n-1)/digit)[(n-1)%digit])-ord('0') 
```

**401 二进制手表**

```python
class Solution(object):
  def readBinaryWatch(self, num):
    """
    :type num: int
    :rtype: List[str]
    """
    res = []
    for h in range(12):
      for m in range(60):
        if (bin(h)+bin(m)).count('1') == num:
          res.append('%d:%02d' % (h, m))
    return res
```

**405 数字转换为十六进制数**

```python
class Solution(object):
  def toHex(self, num):
    """
    :type num: int
    :rtype: str
    """
    dict={10:'a',11:'b',12:'c',13:'d',14:'e',15:'f'}
    hexRes=[]
    if num<0:
      num+=2**32#处理负数的方法
    if num==0:
      return '0'
    while num>0:
      figure=num%16
      num/=16
      if figure>=0 and figure<=9:
        hexRes.append(str(figure))
      else:
        hexRes.append(dict[figure])
    hexRes=hexRes[::-1]
    return ''.join(hexRes)
```

**409 最长回文串**

```python
class Solution(object):
  def longestPalindrome(self, s):
    """
    :type s: str
    :rtype: int
    """
    dit={}
    a=0
    b=0
    c=0
    for i in s:
      if i not in dit:
        dit[i]=1
      else:
        dit[i]+=1
    if max(dit.values())==len(s):
      return len(s)
    for key,values in dit.items():
      if values==1:
        a=1
      else: 
        if values%2==1:
          b+=values-1
          c=1
        else:
          b+=values
    if a==0:
      return b+c
    else:
      return a+b
```

**412 Fizz Buzz**

```python
class Solution(object):
  def fizzBuzz(self, n):
    """
    :type n: int
    :rtype: List[str]
    """
    a=[]
    b=[1]
    for i in range(1,n+1):
      if i%3==0 and i%5==0:
        a.append("FizzBuzz")
      elif i%3==0 :
        a.append("Fizz")
      elif i%5==0 :
        a.append("Buzz")
      else :
        b[0]=i
        a.append(str(i))
    return a
```



### 414. 第三大的数

```python
class Solution(object):
  def thirdMax(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    nums = list(set(nums))
    if len(nums)<3:
      return max(nums)
    else:
      for i  in range (2):
        nums.remove(max(nums))
    return max(nums)
```

**415 字符串相加**

```python
class Solution(object):
  def addStrings(self, num1, num2):
    """
    :type num1: str
    :type num2: str
    :rtype: str
    """
    num11=list(num1)
    num21=list(num2)
    sum1=sum2=0
    for i in num11:
      sum1=10*sum1+int(i)
    for i in num21:
      sum2=10*sum2+int(i)
    print(sum1,sum2)
    return str(sum1+sum2)
```

### 434. 字符串中的单词数

```python
class Solution:
  def countSegments(self, s):
    """
    :type s: str
    :rtype: int
    """
    return len(s.split())
```

**找到字符串中所有字母异位词**

```python
class Solution:
  def findAnagrams(self, s, p):
    """
    :type s: str
    :type p: str
    :rtype: List[int]
    """
    from collections import Counter
    s_len, p_len = len(s), len(p)
    count = p_len
    pChar = Counter(p)
    result = []
    for i in range(s_len):
      if pChar[s[i]] >= 1:
        count -= 1
      pChar[s[i]] -= 1
      if i >= p_len:
        if pChar[s[i - p_len]] >= 0:
          count += 1
        pChar[s[i - p_len]] += 1
      if count == 0:
        result.append(i - p_len + 1)

​    return result
```

**438 找到字符串中所有字母异位词**

```python
class Solution:
  def findAnagrams(self, s, p):
    """
    :type s: str
    :type p: str
    :rtype: List[int]
    """
    from collections import Counter
    s_len, p_len = len(s), len(p)
    count = p_len
    pChar = Counter(p)
    result = []
    for i in range(s_len):
      if pChar[s[i]] >= 1:
        count -= 1
      pChar[s[i]] -= 1
      if i >= p_len:
        if pChar[s[i - p_len]] >= 0:
          count += 1
        pChar[s[i - p_len]] += 1
      if count == 0:
        result.append(i - p_len + 1)

​    return result
```

**441 排列硬币**

```python
class Solution(object):
  def arrangeCoins(self, n):
    """
    :type n: int
    :rtype: int
    """
    i=1
    while n>=i:
      n=n-i
      i=i+1
    return i-1
```

**442 数组中重复的数据**

```python
class Solution(object):
  def findDuplicates(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    res = []
    length = len(nums)
    i = 0
    while i < length:
      \#调整元素位置
      if nums[i] != nums[nums[i] - 1]:
        nums[nums[i]-1], nums[i] = nums[i], nums[nums[i] - 1]
      else:
        i += 1
    \#查找重复元素
    for i in range(length):
      if  nums[i] != i + 1:
        res.append(nums[i])
    return res
```

**443 压缩字符串**

```python
class Solution(object):
  def compress(self, chars):
    """
    :type chars: List[str]
    :rtype: int
    """
    n = len(chars) 
    cur = 0 # 当前字符的索引，用以压缩原字符串
    i = 0
    while i < n:
      j = i
      while j < n - 1 and chars[j] == chars[j+1]:# 找字符连续出现的次数
        j += 1
      chars[cur] = chars[i] # 记录当前处理的字符
      cur += 1
      if i != j:
        times = str(j-i+1) # 将字符的次数写入原串中
        tLen = len(times)
        for k in range(tLen):
          chars[cur+k] = times[k]
        cur += tLen
      i = j + 1 # 处理下一个字符
    return cur
```

**447  回旋镖的数量**

```python
class Solution(object):
  def numberOfBoomerangs(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    def dis(point1, point2):
      return (point1[0] - point2[0])**2 + (point1[1] - point2[1])**2

​    result = 0
​    for i in points:
​      record = {}
​      for j in points:
​        if j != i:
​          distance = dis(i, j)
​          record[distance] = record.get(distance, 0) + 1

​      for val in record.values():
​        if val >= 2:
​          result += (val - 1)* val

​    return result
```

**448 找到所有数组中消失的数字**

```python
class Solution:
  def findDisappearedNumbers(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    return list(set(range(1, len(nums)+1)) - set(nums))
```

**453 最小移动次数使数组元素相等**

```python
class Solution:
  def minMoves(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    total=0
    min_number=min(nums)
    if len(nums)<2:
      return 0
    for i in nums:
      total+=i-min_number
    return total
```

**455.分发饼干**

假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。对每个孩子 i ，都有一个胃口值 gi ，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j ，都有一个尺寸 sj 。如果 sj >= gi ，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

**注意：**

你可以假设胃口值为正。
一个小朋友最多只能拥有一块饼干。

```python
class Solution:
    def findContentChildren(self, g, s):
        """
        :type g: List[int]
        :type s: List[int]
        :rtype: int
        """
        g.sort()
        s.sort()
        a=0
        for i in range(len(g)):
            for b in range(len(s)):
                if g[i]<=s[b]:
                    a=a+1
                    s.pop(b)
                    break
        return a
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**459 重复的子字符串**

```python
class Solution(object):
  def repeatedSubstringPattern(self, s):
    """
    :type s: str
    :rtype: bool
    """
    n=len(s)
    for i in range(1,n//2+1):
      if n%i==0:
        a=s[:i];j=i
        while j<n and s[j:j+i]==a:
          j += i
        if j==n:return True
 
    return False
```

**461 汉明距离**     

```
class Solution:
  def hammingDistance(self, x, y):
    """
    :type x: int
    :type y: int
    :rtype: int
    """
    return bin(x^y).count('1')
```

**463 岛屿的周长**

```
class Solution:
  def islandPerimeter(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    perimeter = 0
    height = len(grid)
    if height:
      width = len(grid[0])
    for i in range(height):
      for j in range(width):
        if grid[i][j]:
          if i and j and grid[i-1][j] and grid[i][j-1]:
            pass
          elif (not i or grid[i-1][j] == 0) and (not j or grid[i][j-1] == 0):
            perimeter += 4
          else:
            perimeter += 2
    return perimeter
```

**475 供暖器**

```
class Solution(object):
  def findRadius(self, houses, heaters):
    """
    :type houses: List[int]
    :type heaters: List[int]
    :rtype: int
    """
    
  
    houses.sort()
    heaters.sort()
    max_rate=0
    index=0
    for i in houses:
      while index+1<len(heaters) and abs( heaters[index]-i)>=abs(heaters[index+1]-i) :
        index+=1
      max_rate=max(max_rate,abs(heaters[index]-i))
    return max_rate
```

**461.汉明距离**

两个整数之间的[汉明距离](https://baike.baidu.com/item/汉明距离)指的是这两个数字对应二进制位不同的位置的数目。

给出两个整数 `x` 和 `y`，计算它们之间的汉明距离。

```python
class Solution:
    def hammingDistance(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        return bin(x^y).count('1')
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**476.数字的补数**

给定一个正整数，输出它的补数。补数是对该数的二进制表示取反。

```python
class Solution:
    def findComplement(self, num):
        """
        :type num: int
        :rtype: int
        """
        l=len(bin(num))
        
        
        b=0
        for i in range(l-2):
            b=b*2+1
       
        return num^b
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**479 最大回文数乘积**

```
class Solution(object):
  def largestPalindrome(self, n):
    """
    :type n: int
    :rtype: int
    """
    
    if n==1: return 9
    if n==2: return 987
    for a in xrange(2, 9*10**(n-1)):
      hi=(10**n)-a
      lo=int(str(hi)[::-1])
      if a**2-4*lo < 0: continue
      if (a**2-4*lo)**.5 == int((a**2-4*lo)**.5):
        return (lo+10**n*(10**n-a))%1337
```

**485 最大连续1的个数**

```
class Solution:
  def findMaxConsecutiveOnes(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    a=0   
    max1=0
    if 1 not in nums:
      return 0
    for i in range(1,len(nums)):
      if nums[i]==1 and nums[i-1]==1:
        a=a+1
        max1=max(max1,a)
      if nums[i]==0:
        a=0
    
    return max1+1
```

**492 构造矩形**

```
class Solution(object):
  def constructRectangle(self, area):
    """
    :type area: int
    :rtype: List[int]
    """
    x = int(math.ceil(area ** 0.5))
    while area % x != 0:
      x += 1
    y = int(area / x)
    return [x, y]
```

**496 下一个更大元素 I**

```
class Solution(object):
  def nextGreaterElement(self, findNums, nums):
    """
    :type findNums: List[int]
    :type nums: List[int]
    :rtype: List[int]
    """
    b=[]
    for i in findNums:
      a=nums.index(i)
      if a<(len(nums)-1):
        for c in range(a+1,len(nums)):
          if nums[c]>i:
            b.append(nums[c])
            break
        if (findNums.index(i)+1)!=len(b):
          b.append(-1)          
      else:
        b.append(-1)
    return b 
```

**500 键盘行**

```
class Solution:
  def findWords(self, words):
    """
    :type words: List[str]
    :rtype: List[str]
    """
    ans=[]
    keyset=['qwertyuiop','asdfghjkl','zxcvbnm']
    for keys in keyset:
      for word in words:
        line=set(word.lower())
        if line.issubset(set(keys)):
          ans.append(word)
    return ans
```

**504 七进制数**

```
class Solution(object):
  def convertToBase7(self, num):
    """
    :type num: int
    :rtype: str
    """
    if num==0:
      return str(0)
    else:
      res = ''
      n = abs(num)
      while n:
        res = str(n%7) + res
        n = n/7
      return res if num>0 else '-'+res
```

**506 相对名次**

```
class Solution(object):
  def findRelativeRanks(self, nums):
    """
    :type nums: List[int]
    :rtype: List[str]
    """
    count=len(nums)
    a=[]
    for i in nums:
      a.append(i)
    a.sort()
    b=list(range(0,len(nums)))
    for i in a:
      c=nums.index(i)
      b[c]=str(count)
      count=count-1
    for i in range(len(b)):
      if b[i]=='1':
        b[i]="Gold Medal"
      if b[i]=='2':
        b[i]="Silver Medal"
      if b[i]=='3':
        b[i]="Bronze Medal"
    return b
```

**507 完美数**

```
class Solution:
  def checkPerfectNumber(self, num):
    """
    :type num: int
    :rtype: bool
    """
    if num<6:
      return False
    temp=num-1
    if math.sqrt(num)**2==num:
      return False
    for i in range(2,int(math.sqrt(num))+1):
      if num%i == 0:
        temp=temp-i-num/i
    
    if temp==0:
      return True
    else:
      return False
```

**520 检测大写字母**

```
class Solution(object):
  def detectCapitalUse(self, word):
    """
    :type word: str
    :rtype: bool
    """
    count=0
    if 90>=ord(word[0])>=65:
      for i in range(1,len(word)):
        if 65<=ord(word[i])<=90:
          count=count+1
      if (count==len(word)-1) or (count==0):
        return True
    else:
      for i in range(1,len(word)):
        if 65<=ord(word[i])<=90:
          return False
      return True
    return False
```

**521 最长特殊序列 Ⅰ**

```
class Solution(object):
  def findLUSlength(self, a, b):
    """
    :type a: str
    :type b: str
    :rtype: int
    """
    if len(a) != len(b):
      return max(len(a),len(b))
    elif len(a) == len(b) and a == b:
      return -1
    else:
      return len(a)
```

**532 数组中的K-diff数对**

```
class Solution:
  def findPairs(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    a=[]
    b=0
    if k>0:
      return len(set(nums) & set(n+k for n in nums))
    elif k==0:
      return sum(v>1 for v in collections.Counter(nums).values())
    else:
      return 0
```

**541 反转字符串 II**

```
class Solution(object):
  def reverseStr(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    if len(s) <= k:
      return s[::-1]
    elif (k < len(s)) and (len(s) < 2*k):
      return s[0:k][::-1] + s[k:]
    else:
      return s[0:k][::-1] + s[k:2*k] + self.reverseStr(s[2*k:], k)
```

**551 学生出勤纪录 I**

```
class Solution(object):
  def checkRecord(self, s):
    """
    :type s: str
    :rtype: bool
    """
    A = 0
    L = 0
    for i in s :
      if i == 'A' : A += 1
      elif i == 'L' : 
        L += 1
        if L > 2 :
          return False
        continue
      if A > 1 : return False
      L = 0
    return True
```

​          

**557.反转字符串中的字母**

给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

```python
class Solution:
    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """
        c=''
        l=len(s)
        a=[]
        b=[]
        
        for i in range(l):
            a.append(s[i])
            
            while s[i]==' ':
                 for d in range (len(a)):
                    c=c+a[len(a)-d-2]
                    
                    if d==(len(a)-1):
                        
                        a=[]
                        i=i+1
        for d in range (len(a)):
                    c=c+a[len(a)-d-1]          
        return c
                
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**561  数组拆分 I**

```
class Solution(object):
  def arrayPairSum(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    nums.sort()
    a=0
    b=-1
    for i in range(0,len(nums),2):
      a=a+nums[i]
    return a
```

​        

**566 重塑矩阵**

```
class Solution(object):
  def matrixReshape(self, nums, r, c):
    """
    :type nums: List[List[int]]
    :type r: int
    :type c: int
    :rtype: List[List[int]]
    """
    if r*c!=len(nums)*len(nums[0]):
      return nums
    a=[]
    d=[]
    for i in nums:
      for j in i:
        a.append(j)
    for i in range(r):
      b=[]
      for j in range(c):
        b.append(a[j+i*c])
      d.append(b)
    return d
```

**575.分糖果**

给定一个**偶数**长度的数组，其中不同的数字代表着不同种类的糖果，每一个数字代表一个糖果。你需要把这些糖果**平均**分给一个弟弟和一个妹妹。返回妹妹可以获得的最大糖果的种类数。

```python
class Solution:
    def distributeCandies(self, candies):
        """
        :type candies: List[int]
        :rtype: int
        """
        candies.sort()
        nums=1
        half=(len(candies)+1)//2
        for i in range(len(candies)-1):
            if candies[i]==candies[i+1]:
                continue
            nums+=1
        if nums>=half:
            return half
        if nums<half:
            return nums
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**581 最短无序连续子数组**

```
class Solution(object):
  def findUnsortedSubarray(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    a=[]
    for i in nums:
      a.append(i)
    nums.sort()
    start=0
    end=0
    for i in range(len(a)):
      if a[i]!=nums[i]:
        start=i
        break
    for i in range(len(a)):
      if a[len(a)-i-1]!=nums[len(a)-i-1]:
        end=len(a)-i-1
        break
    if end==start :
      return 0
    return end-start+1
```

**594 最长和谐子序列**

```
class Solution(object):
  def findLHS(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    the_dict={}
    for i in nums:
      if i in the_dict:
        the_dict[i]+=1
      else:
        the_dict[i]=1
    max_number=0
    for i in nums:
      if i+1 in the_dict:
        number=the_dict[i]+the_dict[i+1]
        if number>max_number:
          max_number=number
    return max_number
```

**\598. 范围求和 II**

```
class Solution(object):
  def maxCount(self, m, n, ops):
    """
    :type m: int
    :type n: int
    :type ops: List[List[int]]
    :rtype: int
    """
    if not ops:
      return m * n
    return min([op[0] for op in ops]) * min([op[1] for op in ops])
```

**\599. 两个列表的最小索引总和**

```
class Solution(object):
  def findRestaurant(self, list1, list2):
    """
    :type list1: List[str]
    :type list2: List[str]
    :rtype: List[str]
    """
    min1=2000
    dit={}
    d=[]
    for i in list1:
      if i in list2:
        a=list1.index(i)
        b=list2.index(i)
        dit[i]=a+b
    
    a=min(dit.values())
    for key,values in dit.items():
      if values==a:
        d.append(key)
    return d
```

**\605. 种花问题**

```
class Solution:
  def canPlaceFlowers(self, flowerbed, n):
    """
    :type flowerbed: List[int]
    :type n: int
    :rtype: bool
    """
    count = 0
    for i,num in enumerate(flowerbed):
      if num : continue
      if i > 0 and flowerbed[i-1]: continue
      if i < len(flowerbed) - 1 and flowerbed[i+1]:continue
      count += 1
      flowerbed[i] = 1
    return count >= n
```

​      

**\628. 三个数的最大乘积**

```
class Solution:
  def maximumProduct(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    if len(nums)<3:
      return False
    nums.sort()
    max_number=nums[-3]*nums[-2]*nums[-1]
    max_number=max(max_number,nums[0]*nums[1]*nums[-1])

​    return max_number
```

​    

**\633. 平方数之和**

```
class Solution(object):
  def judgeSquareSum(self, c):
    """
    :type c: int
    :rtype: bool
    """
    if c<4:
      if c==3:
        return False
      else:
        return True
    if int(c**0.5) == c**0.5:
      return True
    else :
      heigh = int(c**0.5)
      low = 1
      while  low <= heigh:
        if low**2 + heigh**2 > c:
          heigh -= 1
        elif low**2 + heigh**2 <c:
          low += 1
        else :
          return True
    return False
```

​      

**\643. 子数组最大平均数 I**

```
class Solution:
  def findMaxAverage(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: float
    """
    
    i,sum_now,max_sum,n,=0,sum(nums[0:k]),sum(nums[0:k]),len(nums)
    while i<n-k:
      i += 1
      sum_now += (nums[i+k-1]-nums[i-1])
      if sum_now>max_sum:
        max_sum=sum_now
    return float(max_sum)/k
```

**\645. 错误的集合**

```
class Solution(object):
  def findErrorNums(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    dup=sum(nums)-sum(set(nums))
    l=len(nums)
    miss=l*(l+1)/2-sum(set(nums))
    return [dup, miss]
```



**657.判断路线成圈**

初始位置 (0, 0) 处有一个机器人。给出它的一系列动作，判断这个机器人的移动路线是否形成一个圆圈，换言之就是判断它是否会移回到**原来的位置**。

移动顺序由一个字符串表示。每一个动作都是由一个字符来表示的。机器人有效的动作有 `R`（右），`L`（左），`U`（上）和 `D`（下）。输出应为 true 或 false，表示机器人移动路线是否成圈。

```python
class Solution:
    def judgeCircle(self, moves):
        """
        :type moves: str
        :rtype: bool
        """
        a=0
        b=0
        for i in range(len(moves)):
            if moves[i]=='U':
                a+=1
            if moves[i]=='D':
                a-=1
            if moves[i]=='R':
                b+=1
            if moves[i]=='L':
                b-=1
        return a==b==0
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**\665. 非递减数列**

```
class Solution:
  def checkPossibility(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    if len(nums)<=2: 
      return True
    count = 0 if nums[0] <= nums[1] else 1 #判断第一个数是否小于1 
    for i in range(2,len(nums)):
      if nums[i-1] > nums[i]:#如果前一个数小于下一个数 n+1
        count += 1
        if count > 1:#如果 n>1 说明已经有两个非递减队
          return False
        if nums[i-2] > nums[i]:  #如果前两个数是否小于当前数避免[3424]这类情况情况
          nums[i] = nums[i-1]  
        else:
          nums[i-1] = nums[i-2] 
    return count <= 1 
```

**\674. 最长连续递增序列**

```
class Solution(object):
  def findLengthOfLCIS(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    if len(nums)==1:
      return 1
    max_count=0
    count=1
    for i in range(1,len(nums)):
      if nums[i]>nums[i-1]:
        count+=1
      if max_count<count:
        max_count=count
      if nums[i]<=nums[i-1]:
        count=1
    return max_count
```

**\682. 棒球比赛**

```
class Solution(object):
  def calPoints(self, ops):
    """
    :type ops: List[str]
    :rtype: int
    """
    a=[]
    for i in range(len(ops)):
      if ops[i]=='C':
        a.pop()
      elif ops[i]=='D':
        a.append(a[-1]*2)
      elif ops[i]=='+':
         a.append(a[-1]+a[-2])
      else:
         a.append(int(ops[i]))         
    return sum(a)
```


 **\686. 重复叠加字符串匹配**

```
class Solution(object):
  def repeatedStringMatch(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: int
    """
    na, nb = len(A), len(B)
    times = nb / na + 3
    for i in range(1, times):
      if B in A * i:
        return i
    return -1


```

**\690. 员工的重要性**

```
"""
\# Employee info
class Employee:
  def __init__(self, id, importance, subordinates):
    \# It's the unique id of each node.
    \# unique id of this employee
    self.id = id
    \# the importance value of this employee
    self.importance = importance
    \# the id of direct subordinates
    self.subordinates = subordinates
"""
class Solution:
  def getImportance(self, employees, id):
    """
    :type employees: Employee
    :type id: int
    :rtype: int
    """
    \# emps = {employee.id: employee for employee in employees}
    \# def dfs(id):
    \#   subordinates_importance = sum([dfs(sub_id) for sub_id in emps[id].subordinates])
    \#   return subordinates_importance + emps[id].importance
    \# return dfs(id)
    idt={}
    im=0
    for i in employees:
      idt[i.id]=(i.importance,i.subordinates)
    subordinates=idt[id][1]
    im+=idt[id][0]
    for i in subordinates:
      im+=idt[i][0]
      subordinates+=idt[i][1]
    return im
```

**\693. 交替位二进制数**

```
class Solution(object):
  def hasAlternatingBits(self, n):
    """
    :type n: int
    :rtype: bool
    """
    a=bin(n)
    for i in range(len(a)-1):
      if a[i]==a[i+1]:
        return False
    return True
```

**\697. 数组的度**

```
class Solution(object):
  def findShortestSubArray(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    from collections import Counter, defaultdict

​    degree = max(Counter(nums).values())
​    so_far = defaultdict(int)
​    min_size = len(nums)
​    start, end = 0, len(nums) - 1
​    for end, num in enumerate(nums):
​      so_far[num] += 1
​      while start <= end and so_far[num] == degree:
​        min_size = min(min_size, end - start + 1)
​        so_far[nums[start]] -= 1
​        start += 1
​    return min_size
```

​    

**\695. 岛屿的最大面积**

```
class Solution(object):
  def maxAreaOfIsland(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    mx = 0
    n = len(grid)
    m = len(grid[0])
    for i in range(0, n):
      for j in range(0, m):
        if grid[i][j] == 1:
          mx = max(mx, self.dfs(grid, i,j))
    return mx
  def dfs(self, grid, x0, y0):
    s = 1
    n = len(grid)
    m = len(grid[0])

​    grid[x0][y0] = 0
​    dire = [[0,1],[0,-1],[1,0],[-1,0]]
​    for i in range(0,4):
​      x = x0 + dire[i][0]
​      y = y0 + dire[i][1]
​      if x>=0 and x<n and y>=0 and y<m and grid[x][y] == 1:
​        s = s + self.dfs(grid, x, y)
​    return s
```

**\696. 计数二进制子串**

```
class Solution(object):
  def countBinarySubstrings(self, s):
    """
    :type s: str
    :rtype: int
    """
    L = list(map(len, s.replace('01', '0 1').replace('10', '1 0').split(' ')))
    return sum(min(a,b) for a,b in zip(L, L[1:]) )
```

​     

**\704. 二分查找**

```
class Solution(object):
  def search(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: int
    """
    l=0
    r=len(nums)-1

​    while l<=r:
​      mid=(l+r)/2
​      if nums[mid]==target:
​        return  mid
​      elif nums[mid]<target:
​        l=mid+1
​      else :
​        r=mid-1
​    return -1
```

**\709. 转换成小写字母**

```
class Solution:
  def toLowerCase(self, str):
    """
    :type str: str
    :rtype: str
    """
    return str.lower()
```

**\717. 1比特与2比特字符**

```
class Solution(object):
  def isOneBitCharacter(self, bits):
    """
    :type bits: List[int]
    :rtype: bool
    """
    a=[]
    for i in bits:
      if i==0:
        if a:
          a.pop()
      if i==1:
        a.append(i)
      if len(a)==2:
        a.pop()
        a.pop()
    return False if a else True
```

**\720. 词典中最长的单词**

```
class Solution(object):
  def longestWord(self, words):
    """
    :type words: List[str]
    :rtype: str
    """
    words.sort()
    res = set([''])
    longestWord = ''
    for word in words:
      if word[:-1] in res:
        res.add(word)
        if len(word) > len(longestWord):
          longestWord = word
    return longestWord
```

**\724. 寻找数组的中心索引**

```
class Solution(object):
  def pivotIndex(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    res = sum(nums)
    lsum = 0
    for i, j in enumerate(nums):
      if lsum * 2 + j == res:
        return i
      lsum += j
    return -1
```

728 **自除数**

```
class Solution(object):
  def selfDividingNumbers(self, left, right):
    """
    :type left: int
    :type right: int
    :rtype: List[int]
    """
    answer=[]
    for i in xrange(left,right+1):
      flag=0
      b=i
      while b :
        a=b%10
        if a==0 or i%a!=0:
          flag=1
          break
        b=b/10
      if flag==0:
        answer.append(i)
    return answer
```

​    

**733 图像渲染**

```python
class Solution:
  def floodFill(self, image, sr, sc, newColor):
    """
    :type image: List[List[int]]
    :type sr: int
    :type sc: int
    :type newColor: int
    :rtype: List[List[int]]
    """
    oldColor = image[sr][sc]
    image[sr][sc] = newColor
    mark =[[sr,sc]]       # 用于标记去过的点
    return self.dfs(image, sr, sc, oldColor, newColor, mark)
  
  def dfs(self, image, i, j, oldColor, newColor, mark):
    h = len(image)
    w = len(image[0])    
    direction = [[1,0], [0,1], [-1,0], [0,-1]]
    for d in direction:
      x = i + d[0]
      y = j + d[1]
      if x>=0 and x<h and y>=0 and y<w and image[x][y]==oldColor and [x,y] not in mark:   # 最后的条件防止回退陷入死循环
        mark += [[x,y]]   # 新加入当前的点
        image[x][y] = newColor
        image = self.dfs( image, x, y, oldColor, newColor, mark )
        
    return image 
```

**744 寻找比目标字母大的最小字母**

```python
class Solution(object):
  def nextGreatestLetter(self, letters, target):
    """
    :type letters: List[str]
    :type target: str
    :rtype: str
    """
    for i in letters:
      if ord(i)>ord(target):
        return i
    return letters[0]
```

**746 使用最小花费爬楼梯**

```python
class Solution(object):
  def minCostClimbingStairs(self, cost):
    """
    :type cost: List[int]
    :rtype: int
    """
    dp = {}
    dp[0] = cost[0]
    dp[1] = cost[1]
    for i in range(2,len(cost)):
      dp[i] = min(dp[i-2]+cost[i],dp[i-1]+cost[i])
    return min(dp[len(cost)-1],dp[len(cost)-2])
```

**747 至少是其他数字两倍的最大数**

```python
class Solution(object):
  def dominantIndex(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    if len(nums)==1:
      return 0
    max_number=max(nums)
    index=nums.index(max_number)

​    nums.remove(max_number)
​    nex=max(nums)

​    if  max_number>=2*nex:
​      return index
​    else:
​      return -1
```

**762 二进制表示中质数个计算置位**

```python
class Solution(object):
  def countPrimeSetBits(self, L, R):
    """
    :type L: int
    :type R: int
    :rtype: int
    """
    a=[]
    b=0
    for i in range(L,R+1):
      c=bin(i)
      a.append(c.count('1'))
    for i in a:
      if i==1:
        b=b+1
      else:
        for c in range(2,i):
          if i%c==0:
            b=b+1
            break
    return len(a)-b
```



### 766. 托普利茨矩阵

```python
class Solution(object):
  def isToeplitzMatrix(self, matrix):
    """
    :type matrix: List[List[int]]
    :rtype: bool
    """
    n = len(matrix)
    m = len(matrix[0])

​    for i in range(0, n - 1):
​      for j in range(0, m - 1):
​        if matrix[i][j] != matrix[i + 1][j + 1]: return False
​    return True
```



**771.宝石与石头**

 给定字符串`J` 代表石头中宝石的类型，和字符串 `S`代表你拥有的石头。 `S` 中每个字符代表了一种你拥有的石头的类型，你想知道你拥有的石头中有多少是宝石。

`J` 中的字母不重复，`J` 和 `S`中的所有字符都是字母。字母区分大小写，因此`"a"`和`"A"`是不同类型的石头。

```python
class Solution:
    def numJewelsInStones(self, J, S):
        """
        :type J: str
        :type S: str
        :rtype: int
        """
        a=0
        for i in range(len(S)):
            if S[i] in J :
                a+=1
        return a
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**784 字母大小写全排列**

```python
class Solution(object):
  def letterCasePermutation(self, S):
    """
    :type S: str
    :rtype: List[str]
    """
    \# 记录当前所有的分支
    cur_s =[S]
    \# 每次都从上一轮记录的位置的下一位开始计算
    for i in range(len(S)):
      next_s = []
      for s in cur_s:
        \# 如果是数字，则当前分支直接加入下轮的分支
        if s[i].isdigit():
          next_s.append(s)
        \# 如果是字母，则当前分支分为大小写两种加入下轮的分支
        else:
          next_s.append(s[0:i] + s[i].lower() + s[i + 1:])
          next_s.append(s[0:i] + s[i].upper() + s[i + 1:])
      cur_s = next_s
    return cur_s
```

**788 旋转数字**

```python
class Solution(object):
  def rotatedDigits(self, N):
    """
    :type N: int
    :rtype: int
    """
    \# if N<=10:
    \#   if N<2:
    \#     return 0
    \#   if N<5:
    \#     return 1
    \#   if N<6:
    \#     return 2
    \#   if N<9:
    \#     return 3
    \#   return 4
    \# number=0
    \# for i in range(1,N+1):
    \#   count=0
    \#   for a in str(i):
    \#     if (int(a)==3) or (int(a)==4) or (int(a)==7) :
    \#       count=0
    \#       break
    \#     if (int(a)==2) or (int(a)==5) or (int(a)==6) or (int(a)==9):
    \#       count=1
    \#   number=number+count
    \# return number
    counts = 0
    for num in range(1, N+1):
      number = str(num)
      if '3' in number or '7' in number or '4' in number: # This will be an invalid number upon rotation
        continue # Skip this number and go to next iteration
      if '2' in number or '5' in number or '6' in number or '9' in number:
        counts += 1
    return counts
```

**796 旋转字符串**

```python
class Solution:
  def rotateString(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: bool
    """
    if A==B:
      return True
    if len(A)!=len(B):
      return False
    for i in range(len(A)):
      if A==B:
        return True
      A=A[1:]+A[0]
    return False
```


**804 唯一摩尔斯密码词**

```python
class Solution:
  def uniqueMorseRepresentations(self, words):
    """
    :type words: List[str]
    :rtype: int
    """
    ref=[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]     
    return len(set("".join(ref[ord(s) - 97] for s in word) for word in words))
```

**806 写字符串需要的行数**

```python
class Solution(object):
  def numberOfLines(self, widths, S):
    """
    :type widths: List[int]
    :type S: str
    :rtype: List[int]
    """
    base=ord('a')    
    lines=1       
    count=0
    for index in range(len(S)-1):
      aph=S[index]  #取字母
      pianyi=ord(aph)-base
      count+=widths[pianyi]
      if count+widths[ord(S[index+1])-base] >100:  
        count=0
        lines+=1
    count+=widths[ord(S[len(S)-1])-base]
    return [lines,count]
```


**811 子域名访问计数**

```python
class Solution(object):
  def subdomainVisits(self, cpdomains):
    """
    :type cpdomains: List[str]
    :rtype: List[str]
    """
    domain_counts = collections.defaultdict(int)
    for cpdomain in cpdomains:
      times, domains = cpdomain.split()
      times = int(times)
      domain_counts[domains] += times
      while '.' in domains:
        domains = domains[domains.index('.') + 1:]
        domain_counts[domains] += times
    return [str(v) + ' ' + d for d, v in domain_counts.items()]
```

**812 最大三角形面积**

```python
class Solution(object):
  def largestTriangleArea(self, points):
    """
    :type points: List[List[int]]
    :rtype: float
    """
    def f(p1, p2, p3):
      (x1, y1), (x2, y2), (x3, y3) = p1, p2, p3
      return 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2))
    return max(f(a, b, c) for a, b, c in itertools.combinations(points, 3))
```

**819.最常见的单词**

```python
class Solution(object):
  def mostCommonWord(self, paragraph, banned):
    """
    :type paragraph: str
    :type banned: List[str]
    :rtype: str
    """
    list1=[]
    listout=[]
    paragraph=paragraph.lower()
    for i in paragraph:
      if(not i.isalpha() and i!=' '):
        paragraph=paragraph.replace(i,'')
        \#paragraph.lower()
    list1=paragraph.split()
    length=len(list1)
    k=0
    while(k<length):
      if(banned.count(list1[k])!=0):
        list1.pop(k)
        length-=1
        continue
      k+=1  
    for j in list1:
      listout.append(list1.count(j))
    return list1[listout.index(max(listout))]  
```

**821 字符的最短距离**

```python
class Solution(object):
  def shortestToChar(self, S, C):
    """
    :type S: str
    :type C: str
    :rtype: List[int]
    """
    b=[]
    a=[]
    for i in range(len(S)):
      if S[i] ==C:
        b.append(i)
    for i in range(len(S)):
      min_number=10000
      for number in b:
        if abs(number-i)<min_number:
          min_number=abs(number-i)
      a.append(abs(min_number))
    return a
```

**824 山羊拉丁文**

```python
class Solution(object):
  def toGoatLatin(self, S):
    """
    :type S: str
    :rtype: str
    """
    dic = {'A','E','I','O','U'}
    words = S.split(' ')
    for index , word in enumerate(words):
      if word.capitalize()[0] in dic:
        words[index] += 'ma' + 'a'*(index+1)
      else:
        words[index] = word.replace(word[0],'',1) + word[0] + 'ma' + 'a'*(index+1)
    return ' '.join(words)
```

**830 较大分组的位置**

```python
class Solution(object):
  def largeGroupPositions(self, S):
    """
    :type S: str
    :rtype: List[List[int]]
    """
    return_list=[]
    i,j,n=0,0,len(S)
    while i<n-1:
      while i<n-1 and S[i+1]==S[i]:
        i += 1
      if i-j>=2:
        return_list.append([j,i])
      i=i+1;j=i
    return return_list
```

**832 翻转图像**

```python
class Solution:
  def flipAndInvertImage(self, A):
    """
    :type A: List[List[int]]
    :rtype: List[List[int]]
    """
    for i in A:
      for a in range(len(i)):
        i[a]=i[a]^1
      i.reverse()
    return A
```

**836 矩形重叠**

```python
class Solution(object):
  def isRectangleOverlap(self, rec1, rec2):
    """
    :type rec1: List[int]
    :type rec2: List[int]
    :rtype: bool
    """
    rec1_x1, rec1_y1, rec1_x2, rec1_y2 = rec1
    rec2_x1, rec2_y1, rec2_x2, rec2_y2 = rec2
    return not (rec1_x1 >= rec2_x2 or rec1_x2 <= rec2_x1 or rec1_y1 >= rec2_y2 or rec1_y2 <= rec2_y1)
```

**844 比较含退格的字符串**

```python
class Solution(object):
  def backspaceCompare(self, S, T):
    """
    :type S: str
    :type T: str
    :rtype: bool
    """
    s1=[]
    s2=[]
    for i in S:
      if i=='#':
        if s1:s1.pop()
      else:
        s1.append(i)
    for i in T:
      if i=='#':
        if s2:s2.pop()
      else:
        s2.append(i)
    return s1==s2
```

**849 到最近的人的最大距离**

```python
class Solution:
  def maxDistToClosest(self, seats):
    """
    :type seats: List[int]
    :rtype: int
    """
    c=0
    d=0
    if len(seats)<=2:
      return 1
    a=[]
    count=0
    for i in seats:
      if i ==0:
        count+=1
      if i==1:
        a.append(count)
        count=0
    if seats[0]==0:
      c=a[0]
    if seats[-1]==0:
      d=count
    b=max(a)
	return max(int(b/2)+b%2,c,d)
```

**852 山脉数组的峰顶索引**

```python
class Solution(object):
  def peakIndexInMountainArray(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    the_max=0
    for i in range(len(A)):
      if A[i]>A[the_max]:
        the_max=i
    return the_max
```

 **859 亲密字符串**

```python
class Solution(object):
  def buddyStrings(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: bool
    """
    a=[]
    b={}
    
    if len(A)!=len(B) or len(A)<1:
      return False
    for i in range(len(A)):
      if A[i] in b:
        b[A[i]]+=1
      else:
        b[A[i]]=1
      if A[i]!=B[i]:
        a.append(A[i])
        a.append(B[i])
    if len(a)==0:
      if max(b.values())>1:
        return True
      else:
        return False
      
    if len(a)==4 and a[0]==a[3] and a[2]==a[1]:
      return True
    return False
```

**860 柠檬水找零**

```python
class Solution(object):
  def lemonadeChange(self, bills):
    """
    :type bills: List[int]
    :rtype: bool
    """
    five=0
    ten=0
    
    for i in range(len(bills)):
      if bills[i]==5:
        five+=1
      elif bills[i]==10:
          if five==0:
            return False
          else:
            five-=1
            ten+=1
      else:
        if ten==0:
          if five<3:
            return False
          else:
            five=five-3
        else:
          if five==0:
            return False
          else:
            five-=1
            ten-=1
    return True
```

**867 转置矩阵**

```python
class Solution(object):
  def transpose(self, A):
    """
    :type A: List[List[int]]
    :rtype: List[List[int]]
    """
    hang,lie=len(A),len(A[0])
    res = [[0] * hang for _ in range(lie)]
    for i in range(hang):
      for j in range(lie):
        res[j][i] = A[i][j]
    return res
```

**868 二进制间距**

```python
class Solution(object):
  def binaryGap(self, N):
    """
    :type N: int
    :rtype: int
    """
    res, last = 0, None  # res 保存结果， last 记录上个一个1出现的位置。
    for i in range(32):
      if (N >> i) & 1:
        if last is not None:  # 现在的 i，表示1 出现的位置
          res = max(res, i - last)  # 更新结果
        last = i
    return res
```

**883 三维形体投影面积**

```python
class Solution(object):
  def projectionArea(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    N = len(grid)
    ans = 0

    for i in xrange(N):
​      best_row = 0  # max of grid[i][j]
​      best_col = 0  # max of grid[j][i]
​      for j in xrange(N):
​        if grid[i][j]: ans += 1  # top shadow
​        best_row = max(best_row, grid[i][j])
​        best_col = max(best_col, grid[j][i])

​      ans += best_row + best_co

return ans
```

**884 两句话中的不常见单词**

```python
class Solution(object):
  def uncommonFromSentences(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: List[str]
    """
    a=A.split()
    b=B.split()
    c=[]
    for i in a:
      alone=0
      alone1=0
      if i not in b:
        alone=1
      if a.count(i)==1:
        alone1=1
      if (alone==1) and (alone1==1) :
        c.append(i)
    for i in b:
      alone=0
      alone1=0
      if i not in a:
        alone=1
      if b.count(i)==1:
        alone1=1
      if (alone==1) and (alone1==1) :
        c.append(i)
    return c   
```

**888 公平的糖果交换**

```python
class Solution:
  def fairCandySwap(self, A, B):
    """
    :type A: List[int]
    :type B: List[int]
    :rtype: List[int]
    """
    suma=sum(A)
    sumb=sum(B)
    setb=set(B)
    for i in A:
      if i+(sumb-suma)/2 in setb:
        return [i,i+(sumb-suma)//2]
```

**896 单调数列**

```python
class Solution(object):
  def isMonotonic(self, A):
    """
    :type A: List[int]
    :rtype: bool
    """
    a=[]
    for i in A:
      a.append(i)
    a.sort()
    if A==a:
      return True
    a.sort(reverse = True)
    if A==a:
      return True
    return False
```

