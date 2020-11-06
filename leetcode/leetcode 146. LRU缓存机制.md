**###题目**

运用你所掌握的数据结构，设计和实现一个 LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。

写入数据 put(key, value) - 如果密钥已经存在，则变更其数据值；如果密钥不存在，则插入该组「密钥/数据值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

- 输入：["LRUCache","put","put","get","put","get","put","get","get","get"]
- [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
- 输出：[null,null,null,1,null,-1,null,-1,3,4]

**###思路**

最近不想动脑子，又用的暴力法来做，具体思路还是比较清晰易懂的：

设置一个rq数组，它里面的数据是pair形式的，其中first存储的是每个数据的key，second存储的是每个数据的value，然后设置一个index代表当前存储了多少个数据，用一个time数组表示rq数组中每个元素的何时使用的，time[i]的值为0代表rq[i]才使用过，time[i]的值越大代表使用的时间离现在越远。

然后就是get(key)函数，直接遍历rq的first，如果有等于key的，直接输出相应的value即可，然后修改优先级数组time，假设rq[i].first==key，那么相应的将time[i]设为0，time数组的其它元素加一。

然后是put函数，首先寻找rq里面是否已有key。如果有，那么直接覆盖并且修改time数组，修改规则和get函数一样。如果没有，那么先检查index的值，看rq数组中是否还存在没有使用的存储空间，在有未使用的空间的情况下，直接赋值并且按照一样的规则修改time数组。如果没有未使用过的空间，那么通过time数组找出最久未使用的数据，将其覆盖了，然后再修改time数组。

更具体的就是代码注释里面的了。

**###code**

```cpp
class LRUCache {
public:
int index=0;//数组中存了多少个数据
vector<pair<int,int>>rq;//first存key，second存value
vector<int>time; //优先级
LRUCache(int capacity) {
    //先设置好两个数组的大小
    for(int i=0;i<capacity;++i)
    {
        rq.push_back(make_pair(-1,-1));
        time.push_back(0);
    }
    return;
}

int get(int key) {
    int capacity=rq.size();
    //找key是否在rq中，如果在，输出value并更新优先级数组time
    for(int i=0;i<capacity;++i)
    {
        if(rq[i].first==key&&rq[i].second!=-1)
        {
            for(int j=0;j<capacity;++j)
                time[j]=time[j]+1;
            time[i]=0;
            return rq[i].second;
        }
    }
    return -1;
}

void put(int key, int value) {
    int capacity=rq.size();
    //如果rq中存在key。
    for(int i=0;i<capacity;++i){
        if(rq[i].first==key) {
            rq[i].second = value;
            for(int j=0;j<capacity;++j)
                time[j]=time[j]+1;
            time[i]=0;
            return;
        }
    }
    //不存在key且rq没有装满。
    if(index<capacity)
    {
        //直接装入rq中并且更新优先级数组time。
        rq[index].first=key;
        rq[index].second= value;
        for(int j=0;j<capacity;++j)
                time[j]=time[j]+1;
        time[index]=0;
        index++;
    }
    //不存在且rq装满了。
    else{

        int temp1=-1;
        int temp2 =0;
        //找出最久没使用的
        for(int i =0;i<capacity;++i){
            if (temp1<time[i]) {
                temp1=time[i];
                temp2 =i;
            }
        }
        //覆盖掉该数据并且更新优先级数组time
        rq[temp2].first=key;
        rq[temp2].second=value;
        for(int j=0;j<capacity;++j)
                time[j]=time[j]+1;
        time[temp2]=0;
    }
    return;
}
};
```