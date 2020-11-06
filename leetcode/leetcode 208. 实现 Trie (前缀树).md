**###题目**

实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。

示例:

```cpp
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 true
trie.search("app");     // 返回 false
trie.startsWith("app"); // 返回 true
trie.insert("app");   
trie.search("app");     // 返回 true
```

**你可以假设所有的输入都是由小写字母 a-z 构成的。**

**保证所有输入均为非空字符串。**

**###思路**

定义一个类，有这两个元素，分别是一个isStringEnd代表这个字母是否是一个字符串的结尾，然后有一个26长度的数组，这个数组的元素为空，代表没有接这个字符，如果不为空，那么就代表字符串后面可以接这个字符。

如果一个树中插入了app、apple、you、young，那么树的示意图为：

![img](https://pic4.zhimg.com/80/v2-97badd6f49333eb88290e6178b9ff437_720w.jpg)

从图中的树就可以看出apple、app、you、young是true，其他的单词组合要么是isStringEnd为false，要么就是直接为null，没有记录。

**###code**

```cpp
class Trie {
private:
    bool isStringEnd = false;
    Trie* next[26] = {NULL};
public:
    /** Initialize your data structure here. */
    Trie() {}
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie * temp = this;
        for(char ch : word)
        {
            if(temp->next[ch - 'a'] == NULL)
            {
                temp->next[ch - 'a'] = new Trie();
            }
            temp = temp->next[ch - 'a'];
        }
        temp->isStringEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* temp = this;
        for (char ch : word) {
            temp = temp->next[ch - 'a'];
            if (temp == NULL) {
                return false;
            }
        }
        return temp->isStringEnd ;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* temp = this;
        cout<<1;
        for (char ch : prefix) {
            temp = temp->next[ch - 'a'];
            if (temp == NULL) {
                return false;
            }
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```