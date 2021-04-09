/*
缓存的相关实验。
分为两个部分：
1、模拟cache运行的过程，统计LRU策略下，cache的hit、miss、eviction三个值。
2、实现三种规模的矩阵的转置，需要尽可能的提高cache的命中率，最后根据代码的miss值大小打分。
*/

//第一部分部分需要修改csim.c文件，初始文件如下：
#include "cachelab.h"
int mian()
{
  printSummary(0, 0, 0);
  return 0;
}
/*
输入到printSummary的三个数就是统计的miss、hit、eviction。
接下来就开始介绍需要用的内容。
一个用于保存cache状态的结构，由于表明cache中这一行的状态，最近一次使用时间，标志位。
*/
typedef struct
{
  int vaild;
  int tag;
  int time;
}LINE;
//结构体存储cache的hit、miss、eviction。
typedef struct
{
  int hitCount;
  int missCount;
  int evictionCount;
}RESULT;

//定义缓存初始化函数.
LINE **initCache(int s, int E)
{
  int S = 1<<s;/* 计算cache中一共有多少组 */
  LINE** cache = NULL;/* 用于存储每组内存起始地址 */
  
  cache = (LINE**)malloc(S * sizeof(LINE*));
  if(NULL == cache)
  {
    return NULL;
  }
  
  for(int i = 0; i < S; ++i)
  {
    cache[i] = (LINE*)malloc(E * sizeof(LINE));
    if(NULL == cache[i])
    {
      return NULL;
    }
    memset(cache[i], 0, E * sizeof(LINE));
  }
  
  return cache;
}

//主程序
int main(int argc, char** argv)
{
  RESULT res;
  res.hitCount = 0;
  res.missCount = 0;
  res.evictionCount = 0;
  int opt, s, E, b, saveIndex;
  int S, time, tag;
  char *fileName = NULL;
  LINE** cache = NULL;
  FILE* pFlie = NULL;
  char operation;         /* 命令开头的 I L M S */
  unsigned int address;   /* 地址参数 */
  int size;               /* 大小*/
  LINE line;
  int index;
  int hitFlag;
  int timeStamp = 0;
  int eviFlag = 0;
  
  /* 读取cache规模 */
  while(-1 != (opt = getopt(argc, argv, "s:E:b:t:")))
  {
    switch(opt)
    {
      case 's':
        s = atoi(optarg);
        break;
      case 'E':
        E = atoi(optarg);
        break;
      case 'b':
        b = atoi(optarg);
        break;
      case 't':
        fileName = (char*)optarg;
        break;
      default:
        printf("INPUT ERROR!\n");
        break;
    }
  }
  
  cache = initCache(s, E);
  if(NULL == cache)
  {
    printf("malloc error");
    exit(-1);
  }
  
  pFlie = fopen(fileName, "r");
  if(pFlie == NULL)
  {
    printf("open error");
    exit(-1);
  }
  
  /*根据相信指令对缓存做处理*/
  /* 指令格式为：I 0400d7d4,8 */
  /* 分别为操作 地址 访问的数据大小 */
  /* 其中操作有I表示加载指令，L表示加载数据，S表示保存数据，M表示加载数据后再保存数据*/
  while(fscanf(pFlie, " %c %xu,%d\n", &operation, &address, &size) > 0)
  {
    if('I' == operation)continue;/*不考虑指令读取*/
    
    /*获取组号和标志位*/
    address = address >> b; /*先左移块偏移位*/
    S = address & ~(~0 << s); /*再取出组索引位*/
    tag = address >> s;/*再左移s位，渠道标志位 */
    time = INT_MAX;
    hitFlag = 0;
    eviFlag  = 0;
    
    for(index = 0; index < E; ++index)
    {
      line = cache[S][index];
      if(0 == line.vaild)/* 先找一个位置存储起来，此时time最小，不可能去抢占*/
      {
        saveIndex = index;
        time = INT_MIN;
        eviFlag = 0;
        continue;
      }
      if(tag != line.tag)/* 未命中，那么可能需要抢占，先假设抢占此行*/
      {
        if(time > line.time)
        {
          time = line.time;
          saveIndex = index;
          eviFlag = 1;
        }
        continue;
      }
      if(tag == line.tag)/* 命中了 */
      {
        saveIndex = index;
        res.hitCount ++;
        hitFlag = 1;
        break;
      }
    }
    if('M' == operation)/* M为先L再S，L的时候已经加载到内存，所以S的时候可以命中*/
    {
      res.hitCount++;
    }
    cache[S][saveIndex].time = timeStamp++;/*先更新时间，避免continue跳过*/
    if(hitFlag)/*命中了*/
    {
      continue;
    }
    res.missCount++;/*未命中*/
    if(eviFlag)/*未命中且驱逐了其他缓存*/
    {
      res.evictionCount++；
    }
    /* 更新相关信息 */
    cache[S][saveIndex].vaild = 1;
    cache[S][saveIndex].tag = tag;
  }
  /*防止内存泄漏 */
  fclose(pFlie);
  for(int i = 0; i < S; ++i)
    free(cache[i]);
  free(cache);            // malloc 完要记得 free 并且关文件
  printSummary(res.hitCount, res.missCount, res.evictionCount);
  return 0;
}
/*
测试结果如下：

                        Your simulator     Reference simulator
Points (s,E,b)    Hits  Misses  Evicts    Hits  Misses  Evicts
     3 (1,1,1)       9       8       6       9       8       6  traces/yi2.trace
     3 (4,2,4)       4       5       2       4       5       2  traces/yi.trace
     3 (2,1,4)       2       3       1       2       3       1  traces/dave.trace
     3 (2,1,3)     167      71      67     167      71      67  traces/trans.trace
     3 (2,2,3)     201      37      29     201      37      29  traces/trans.trace
     3 (2,4,3)     212      26      10     212      26      10  traces/trans.trace
     3 (5,1,5)     231       7       0     231       7       0  traces/trans.trace
     6 (5,1,5)  265189   21775   21743  265189   21775   21743  traces/long.trace
    27

TEST_CSIM_RESULTS=27
*/
/*
###partB
此部分需要修改trans.c文件中的transpose_submit函数，使得矩阵转在置时的不命中次数尽可能小，
分别对三个矩阵进行处理，代码也是不同的，不通用，采用分块技术。
*/
/*
32*32
要想降低缓存不命中次数，那么就要考虑局部性了，故利用分块技术。(cache的规格是s=5，E=1, b=5)
由cache的大小可知，可以存储在缓存中的一个数据块为2的五次方，即32字节，也就是8个int型数据，刚好有32组，故分块长度为8*8，
可以将一次缓存的B数组全部使用之后再将其换出，但是因为还需要缓存A的数据，所以还是会存在A将B驱逐，
B又将A驱逐的情况，所以用八个变量把A数组的值保存下来。理论上的miss的最低次数是4 * 4 *16=256次。
如下代码的不命中次数应该为32*8*2+8*4=288，实际计算结果是287次miss。
还未到达256，可以继续优化，但是没时间去弄了。
代码如下：
*/
int i, j, k, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
    for (i = 0; i < 32; i += 8)
      for(j = 0; j < 32; j++)
        {
          temp1 = A[j][i]; /*先读取A的内容*/
          temp2 = A[j][i+1];
          temp3 = A[j][i+2];
          temp4 = A[j][i+3];
          temp5 = A[j][i+4];
          temp6 = A[j][i+5];
          temp7 = A[j][i+6];      
          temp8 = A[j][i+7];
          B[i][j] = temp1; /*再处理B的内容*/
          B[i+1][j] = temp2;
          B[i+2][j] = temp3;
          B[i+3][j] = temp4;
          B[i+4][j] = temp5;
          B[i+5][j] = temp6;
          B[i+6][j] = temp7;
          B[i+7][j] = temp8;
        }
		/*
2、64*64

对 64 x 64 的矩阵来说，每行有 64 个 int，则 cache 只能存矩阵的 4 行了，所以再用8×8的块，前面4行可以缓存，后面4行会在Cache中发生冲突，
导致miss次数增加，改成使用4*4的块。但是最后结果不是满分，但是没时间去优化了。
*/
int i, j, k, temp1, temp2, temp3, temp4;
    for (i = 0; i < M; i += 4)
      for(j = 0; j < M; j += 4)
        for(k = i; k < (i + 4); ++k)
        {
          temp1 = A[k][j];
          temp2 = A[k][j+1];
          temp3 = A[k][j+2];
          temp4 = A[k][j+3];
          B[j][k] = temp1;
          B[j+1][k] = temp2;
          B[j+2][k] = temp3;
          B[j+3][k] = temp4;
        }
/*
3、61*67

本质也是用分块来优化Cache的读写，不断的尝试分块的大小，进行转置操作。17分块可以小于2000次miss。
*/
for (i = 0; i < N; i += 17)
  for (j = 0; j < M; j += 17)
	for (k = j; k < j + 17 && k < M; ++k)
	  for (m = i; m < i + 17 && m < N; ++m)
	  {
		  temp1 = A[k][m];
		  B[m][k] = temp1;
	  }
          