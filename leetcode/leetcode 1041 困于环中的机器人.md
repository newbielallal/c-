---
title: leetcode 1041 困于环中的机器人
tags:
  - c++ 
categories: c++ 
---
这个起始就是搞清楚机器人朝每个方向的运动步数就ok了，因为没有障碍物，所以只是需要统计方向和步数就行了。
<!-- more -->

### 题目
在无限的平面上，机器人最初位于 (0, 0) 处，面朝北方。机器人可以接受下列三条指令之一：

"G"：直走 1 个单位
"L"：左转 90 度
"R"：右转 90 度
机器人按顺序执行指令 instructions，并一直重复它们。
只有在平面中存在环使得机器人永远无法离开时，返回 true。否则，返回 false。
### 思路
因为有4个方向，所以说我们最少需要对这个移动字符串进行四次，比如每次只进行前进左转两个动作，那需要进行四次左转才能回到原状态，所以我们将移动字符串进行四次，然后比较它的前进和后退，左移和右移的步数是否相等，若相等，则会一直转圈。
### code
     bool isRobotBounded(string instructions) {
         int direct = 0;
         vector<int> axis{0, 0, 0, 0};
        int i = 0;
        while(i < 4) // 4个方向转一轮，回原点
        {
            for(auto ch : instructions)
            {
                switch (ch)
                {
                    case 'G':
                        axis[direct] += 1; break; // 相反方向的位移一样说明回到了原点
                    case 'L':
                        direct = (direct + 3) % 4; break;//对应距离数组3
                    case 'R':
                        direct = (direct + 1) % 4; break;//对应距离数组1
                    default:
                        return false;
                }
            }
            i++;
        }
        return (axis[0] == axis[2] && axis[1] == axis[3]) ? true : false;
    }

