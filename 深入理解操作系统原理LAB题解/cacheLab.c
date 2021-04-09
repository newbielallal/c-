/*
��������ʵ�顣
��Ϊ�������֣�
1��ģ��cache���еĹ��̣�ͳ��LRU�����£�cache��hit��miss��eviction����ֵ��
2��ʵ�����ֹ�ģ�ľ����ת�ã���Ҫ�����ܵ����cache�������ʣ������ݴ����missֵ��С��֡�
*/

//��һ���ֲ�����Ҫ�޸�csim.c�ļ�����ʼ�ļ����£�
#include "cachelab.h"
int mian()
{
  printSummary(0, 0, 0);
  return 0;
}
/*
���뵽printSummary������������ͳ�Ƶ�miss��hit��eviction��
�������Ϳ�ʼ������Ҫ�õ����ݡ�
һ�����ڱ���cache״̬�Ľṹ�����ڱ���cache����һ�е�״̬�����һ��ʹ��ʱ�䣬��־λ��
*/
typedef struct
{
  int vaild;
  int tag;
  int time;
}LINE;
//�ṹ��洢cache��hit��miss��eviction��
typedef struct
{
  int hitCount;
  int missCount;
  int evictionCount;
}RESULT;

//���建���ʼ������.
LINE **initCache(int s, int E)
{
  int S = 1<<s;/* ����cache��һ���ж����� */
  LINE** cache = NULL;/* ���ڴ洢ÿ���ڴ���ʼ��ַ */
  
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

//������
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
  char operation;         /* ���ͷ�� I L M S */
  unsigned int address;   /* ��ַ���� */
  int size;               /* ��С*/
  LINE line;
  int index;
  int hitFlag;
  int timeStamp = 0;
  int eviFlag = 0;
  
  /* ��ȡcache��ģ */
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
  
  /*��������ָ��Ի���������*/
  /* ָ���ʽΪ��I 0400d7d4,8 */
  /* �ֱ�Ϊ���� ��ַ ���ʵ����ݴ�С */
  /* ���в�����I��ʾ����ָ�L��ʾ�������ݣ�S��ʾ�������ݣ�M��ʾ�������ݺ��ٱ�������*/
  while(fscanf(pFlie, " %c %xu,%d\n", &operation, &address, &size) > 0)
  {
    if('I' == operation)continue;/*������ָ���ȡ*/
    
    /*��ȡ��źͱ�־λ*/
    address = address >> b; /*�����ƿ�ƫ��λ*/
    S = address & ~(~0 << s); /*��ȡ��������λ*/
    tag = address >> s;/*������sλ��������־λ */
    time = INT_MAX;
    hitFlag = 0;
    eviFlag  = 0;
    
    for(index = 0; index < E; ++index)
    {
      line = cache[S][index];
      if(0 == line.vaild)/* ����һ��λ�ô洢��������ʱtime��С��������ȥ��ռ*/
      {
        saveIndex = index;
        time = INT_MIN;
        eviFlag = 0;
        continue;
      }
      if(tag != line.tag)/* δ���У���ô������Ҫ��ռ���ȼ�����ռ����*/
      {
        if(time > line.time)
        {
          time = line.time;
          saveIndex = index;
          eviFlag = 1;
        }
        continue;
      }
      if(tag == line.tag)/* ������ */
      {
        saveIndex = index;
        res.hitCount ++;
        hitFlag = 1;
        break;
      }
    }
    if('M' == operation)/* MΪ��L��S��L��ʱ���Ѿ����ص��ڴ棬����S��ʱ���������*/
    {
      res.hitCount++;
    }
    cache[S][saveIndex].time = timeStamp++;/*�ȸ���ʱ�䣬����continue����*/
    if(hitFlag)/*������*/
    {
      continue;
    }
    res.missCount++;/*δ����*/
    if(eviFlag)/*δ��������������������*/
    {
      res.evictionCount++��
    }
    /* ���������Ϣ */
    cache[S][saveIndex].vaild = 1;
    cache[S][saveIndex].tag = tag;
  }
  /*��ֹ�ڴ�й© */
  fclose(pFlie);
  for(int i = 0; i < S; ++i)
    free(cache[i]);
  free(cache);            // malloc ��Ҫ�ǵ� free ���ҹ��ļ�
  printSummary(res.hitCount, res.missCount, res.evictionCount);
  return 0;
}
/*
���Խ�����£�

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
�˲�����Ҫ�޸�trans.c�ļ��е�transpose_submit������ʹ�þ���ת����ʱ�Ĳ����д���������С��
�ֱ������������д�������Ҳ�ǲ�ͬ�ģ���ͨ�ã����÷ֿ鼼����
*/
/*
32*32
Ҫ�뽵�ͻ��治���д�������ô��Ҫ���Ǿֲ����ˣ������÷ֿ鼼����(cache�Ĺ����s=5��E=1, b=5)
��cache�Ĵ�С��֪�����Դ洢�ڻ����е�һ�����ݿ�Ϊ2����η�����32�ֽڣ�Ҳ����8��int�����ݣ��պ���32�飬�ʷֿ鳤��Ϊ8*8��
���Խ�һ�λ����B����ȫ��ʹ��֮���ٽ��任����������Ϊ����Ҫ����A�����ݣ����Ի��ǻ����A��B����
B�ֽ�A���������������ð˸�������A�����ֵ���������������ϵ�miss����ʹ�����4 * 4 *16=256�Ρ�
���´���Ĳ����д���Ӧ��Ϊ32*8*2+8*4=288��ʵ�ʼ�������287��miss��
��δ����256�����Լ����Ż�������ûʱ��ȥŪ�ˡ�
�������£�
*/
int i, j, k, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
    for (i = 0; i < 32; i += 8)
      for(j = 0; j < 32; j++)
        {
          temp1 = A[j][i]; /*�ȶ�ȡA������*/
          temp2 = A[j][i+1];
          temp3 = A[j][i+2];
          temp4 = A[j][i+3];
          temp5 = A[j][i+4];
          temp6 = A[j][i+5];
          temp7 = A[j][i+6];      
          temp8 = A[j][i+7];
          B[i][j] = temp1; /*�ٴ���B������*/
          B[i+1][j] = temp2;
          B[i+2][j] = temp3;
          B[i+3][j] = temp4;
          B[i+4][j] = temp5;
          B[i+5][j] = temp6;
          B[i+6][j] = temp7;
          B[i+7][j] = temp8;
        }
		/*
2��64*64

�� 64 x 64 �ľ�����˵��ÿ���� 64 �� int���� cache ֻ�ܴ����� 4 ���ˣ���������8��8�Ŀ飬ǰ��4�п��Ի��棬����4�л���Cache�з�����ͻ��
����miss�������ӣ��ĳ�ʹ��4*4�Ŀ顣����������������֣�����ûʱ��ȥ�Ż��ˡ�
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
3��61*67

����Ҳ���÷ֿ����Ż�Cache�Ķ�д�����ϵĳ��Էֿ�Ĵ�С������ת�ò�����17�ֿ����С��2000��miss��
*/
for (i = 0; i < N; i += 17)
  for (j = 0; j < M; j += 17)
	for (k = j; k < j + 17 && k < M; ++k)
	  for (m = i; m < i + 17 && m < N; ++m)
	  {
		  temp1 = A[k][m];
		  B[m][k] = temp1;
	  }
          