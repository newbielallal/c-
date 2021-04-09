/*
内存管理器的相关实验，要求实现一个内存管理器，需要完成mm.c文件中的mm_init()、mm_alloc()、mm_free()、mmrealloc()函数。
使用CSAPP中介绍的几种方式来实现内存管理，采用隐式链表、分离链表，合并方式为立即合并，分配原则为首次匹配。
*/



//书上提供了一系列要使用到的宏，具体如下：
#define WSIZE     4
#define DSIZE     8
/* 默认扩展堆大小 */
#define CHUNKSIZE (1<<12)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

// 取得首部/尾部的值
#define PACK(size, alloc) ((size) | (alloc))

#define GET(p)            (*(unsigned int *)(p))
#define PUT(p, val)       (*(unsigned int *)(p) = (val))

#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(ptr) ((char *)(ptr) - WSIZE)
#define FTRP(ptr) ((char *)(ptr) + GET_SIZE(HDRP(ptr)) - DSIZE)

#define NEXT_BLKP(ptr) ((char *)(ptr) + GET_SIZE((char *)(ptr) - WSIZE))
#define PREV_BLKP(ptr) ((char *)(ptr) - GET_SIZE((char *)(ptr) - DSIZE))
###mm_init()

//初始化内存管理器。

int mm_init(void)
{
  // heap_listp指向内存起始位置
     if ((heap_listp = mem_sbrk(4*WSIZE))==(void *)-1){
        return -1;
    }
    PUT(heap_listp,0);//双字对齐，空一个字。
    PUT(heap_listp+(1*WSIZE),PACK(DSIZE,1));
    PUT(heap_listp+(2*WSIZE),PACK(DSIZE,1));// 起始
    PUT(heap_listp+(3*WSIZE),PACK(0,1)); // 结尾
    heap_listp += (2*WSIZE); // 指向第一个内存块
    if (extend_heap(CHUNKSIZE/WSIZE)==NULL){
        return -1;
    }
    return 0;
}
###mm_alloc()

//从内存管理器中申请size大小的内存。

void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;
    if (size == 0) return NULL;

    if (size <= DSIZE){
        asize = 2*(DSIZE);
    }else{
        asize = DSIZE * ((size + DSIZE + (DSIZE-1))/DSIZE);
    }
    if ((bp = find_fit(asize))!= NULL){
        place(bp,asize);
        return bp;
    }
    extendsize = MAX(asize,CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE))==NULL){
        return NULL;
    }
    place(bp,asize);
    return bp;
}
###mm_free()

//释放掉bp指向的内存块。

void mm_free(void *bp)
{
    if (NULL == bp)
        return;
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}
###mm_realloc()

//将ptr指向的内容放到长度为size的新内存当中去。

void *mm_realloc(void *ptr, size_t size)
{
    void *newptr;

    if (0 == size) {
      mm_free(ptr);
      return NULL;
    }

    if (NULL == ptr) {
      return mm_malloc(size);
    }

   newptr = mm_malloc(size);

    if (!newptr) {
      return NULL;
    }

    memcpy(newptr, ptr, size);
    mm_free(ptr);

    return newptr;
}
//用于寻找第一个能够放下申请内存大小的块，此处不会进行分割。首次适配搜索。
static void *find_fit(size_t size){
    void *bp;
    size_t asize;
    
    bp = heap_listp;
    asize = GET_SIZE(HDRP(bp));
    
    while (asize > 0)
    {
        if (!GET_ALLOC(HDRP(bp)) && (size <= asize)){
            return bp;
        }
         bp = NEXT_BLKP(bp));
         asize = GET_SIZE(HDRP(bp));
    }
    
    return NULL;
}
//当将适配的空闲块减去申请内存后剩余内存大于等于最小块大小时
//才会对空闲块进行分割。
static void place(void *bp,size_t asize){
    size_t csize = GET_SIZE(HDRP(bp));
    
    if ((csize-asize)>=(DSIZE)){
        PUT(HDRP(bp),PACK(asize,1));
        PUT(FTRP(bp),PACK(asize,1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp),PACK(csize-asize,0));
        PUT(FTRP(bp),PACK(csize-asize,0));
    }else{
        PUT(HDRP(bp),PACK(csize,1));
        PUT(FTRP(bp),PACK(csize,1));
    }
}
//当内存不够时，扩展堆的大小。
static void *extend_heap(size_t words)
{
  char *bp;
  int size;
  // 内存对齐
  size = words%2 ? (words+1)*WSIZE :words*WSIZE;
  if (-1 == (bp = mem_sbrk(size)))
  {
    return NULL;
  }
  
  // 将新申请的内存设置为free。
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));
  
  // 合并内存
  return coalesce(bp);
}
//对释放的空闲内存块进行合并。
static void *coalesce(void *bp){
    size_t  prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t  next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t  size = GET_SIZE(HDRP(bp));

//第一种情况，前后都无空闲块
    if (prev_alloc && next_alloc) {
        return bp;
//第二种情况，后面不是空闲块
    }else if (prev_alloc && !next_alloc){
          size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
            PUT(HDRP(bp), PACK(size,0));
            PUT(FTRP(bp), PACK(size,0));
//第三种情况，前面不是空闲块
    }else if (!prev_alloc && next_alloc){
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp),PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)),PACK(size,0));
        bp = PREV_BLKP(bp);
//最后一种情况，前后都有空闲块.
    }else {
        size +=GET_SIZE(FTRP(NEXT_BLKP(bp)))+ GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(NEXT_BLKP(bp)),PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)),PACK(size,0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}
/*
###测试结果

Results for mm malloc:
trace  valid  util     ops      secs  Kops
 0       yes   99%    5694  0.008726   653
 1       yes   99%    5848  0.007939   737
 2       yes   99%    6648  0.013940   477
 3       yes  100%    5380  0.010529   511
 4       yes   66%   14400  0.000177 81494
 5       yes   92%    4800  0.010952   438
 6       yes   92%    4800  0.010084   476
 7       yes   55%   12000  0.196411    61
 8       yes   51%   24000  0.445172    54
 9       yes   27%   14401  0.215934    67
10       yes   34%   14401  0.003514  4098
Total          74%  112372  0.923379   122

Perf index = 44 (util) + 8 (thru) = 53/100
*/
//为了减少内存碎片，可以采用最佳适配，找到最小的可分配内存块。
static void *find_fit(size_t size){
    void *bp;
    size_t asize;
    void *best = NULL;
    size_t bestSize = INT_MAX;
    
    bp = heap_listp;
    asize = GET_SIZE(HDRP(bp));
    
    while (asize > 0)
    {
        if (!GET_ALLOC(HDRP(bp)) && (size <= asize)){
            if (asize < bestSize)
            {
              best =bp;
              bestSize = asize;
            }
        }
         bp = NEXT_BLKP(bp));
         asize = GET_SIZE(HDRP(bp));
    }
    
    return best;
}
//eeeee,分数也没高多少，还是只有50+。每次分配都要遍历整个链表还是比较慢的，
//试试显式链表，将分配的时间从块总数相关降低到空闲块相关，再加上采用分离链表，
//分离的意思是不同大小的空闲内存块使用不同的空闲链表，这样内存利用率可以接近最佳适配。

/*
首先mm_init()必然是需要修改的，确定一个块最小是多少字节，由于双字对齐，再加上需要头部，尾部，一个pre、一个next，所以最少需要4个字。
也就是16个字节，故空闲块的大小按照如下区域来划分：
16~31 32~63 64~127 128~255 256~511 512~1023 1024~2017 2048~4095 4096~INT_MAC
因为固定大小的空闲块一般不分割的，不合并的，所以如果一个空闲块包含的范围过大，很容易引起很大的内部碎片。
相对于上一个版本的init函数，这个版本需要添加九个节点，用于指向九种空闲链表，所以第一步申请的空间就是9+3为12.
*/
// 新添加的宏
// PRED和NEXT的顺序有点别扭，但是因为root节点只有next，为了方便就写成这样了。
#define PRED(bp) ((char*)(bp) + WSIZE)
#define NEXT(bp) ((char*)bp)
#define PRED_BLKP(bp) (GET(PRED(bp)))
#define NEXTP_BLKP(bp) (GET(NEXT(bp)))
// 存储空闲链表
static char *gfreeList = 0;
int mm_init(void)
{
  // heap_listp指向的是起始位置
     if ((heap_listp = mem_sbrk(12*WSIZE))==(void *)-1){
        return -1;
    }
    PUT(heap_listp,0，NULL);//未分配内存，所以先指向null
    PUT(heap_listp+(1*WSIZE),NULL);
    PUT(heap_listp+(2*WSIZE),NULL);
    PUT(heap_listp+(3*WSIZE),NULL);
    PUT(heap_listp+(4*WSIZE),NULL);
    PUT(heap_listp+(5*WSIZE),NULL);
    PUT(heap_listp+(6*WSIZE),NULL);
    PUT(heap_listp+(7*WSIZE),NULL);
    PUT(heap_listp+(8*WSIZE),NULL);
    PUT(heap_listp+(9*WSIZE),PACK(DSIZE,1));
    PUT(heap_listp+(10*WSIZE),PACK(DSIZE,1));
    PUT(heap_listp+(11*WSIZE),PACK(0,1));
    
    gfreeList = heap_list;
    heap_listp += (10*WSIZE);
    if(extend_heap(CHUNKSIZE/WSIZE)==NULL){
        return -1;
    }
    return 0;
}
//然后是修改extend_heap函数，因为申请的必定是一个空闲块，所以要将其插入合适的空闲链表当中。
//开始本来是想设计成固定大小空闲块，不分割，不合并的，但是这样有个测试用例有严重的外部碎片，所以修改成了要合并要分割的版本。

static void *extend_heap(size_t words)
{
  char *bp;
  size_t size;
  size = words%2 ? (words+1)*WSIZE : words*WSIZE;  //对大小双字对对齐

  if ((void*)-1 == (bp = mem_sbrk(size)))
  {
    return NULL;
  }

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

  //前面处理都一样，然后将这个空闲块的前继和后继置空
  PUT(PRED(bp), NULL);
  PUT(NEXT(bp), NULL);

  //合并后插入现有的free内存块当中。
  bp = coalesce(bp);
  bp = insertFreeList(bp);

  return bp;
}
//然后是合并函数coalesce，用于将释放的内存块合并，和上一种方法差不多，不同的是添加了空闲链表的管理。

static void *coalesce(void *bp){
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));
  
  if (prev_alloc && next_alloc){
    return bp;
  }else if (prev_alloc && !next_alloc){
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    deleteListNode(NEXT_BLKP(bp));// 两个空闲块合并，那么必然要删除一个空闲块
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }else if (!prev_alloc && next_alloc){
    size += GET_SIZE(FTRP(PREV_BLKP(bp)));
    deleteListNode(PREV_BLKP(bp));// 同理
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }else{
    size += GET_SIZE(HDRP(NEXT_BLKP(bp))) + GET_SIZE(FTRP(PREV_BLKP(bp)));
    deleteListNode(NEXT_BLKP(bp));// 同理
    deleteListNode(PREV_BLKP(bp));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }
  return bp;
}
//然后就是insertFreeList函数，将空闲块插入到合适的链表中去，采用头插法，将释放的块直接放入空闲链表的首部。

static void * insertFreeList(void * ptr)
{
  size_t size = GET_SIZE(HDRP(ptr));
  int turn = findTurn(size);// 该存储在第几个链表下
  void *root = gfreeList+turn*WSIZE;

  // 若此链表下没有节点，直接插入即可，若有则要修改链接顺序。
  if (NULL != NEXTP_BLKP(root))
  {
    PUT(PRED(NEXTP_BLKP(root)), ptr);
    PUT(NEXT(ptr), NEXTP_BLKP(root));
  }
  else
  {
    PUT(NEXT(ptr), NULL);
  }

  PUT(NEXT(root), ptr);  
  PUT(PRED(ptr), root); 
  
  return ptr;
}
//然后是findTurn函数，用于确定size大小的内存块应该放在哪个内存链表下。

static int findTurn(size_t size){
  int index = 0;
  if (size >= 4096)
    return 8;
  
  size = size>>5;
  while (size){
    size = size>>1;
    index++;
  }
  return index;
}
//然后是mm_malloc函数，和上一种没有区别。

void *mm_malloc(size_t size){
    size_t asize;
    size_t extendsize;
    char *bp;
    if (size ==0) return NULL;
    int turn;

    asize = size<=DSIZE ? 2*DSIZE : DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
  
    // 放入指定大小的块中。
    turn = findTurn(asize);
    if ((bp = find_fit(turn, asize))!= NULL){
        place(bp,asize);
        return bp;
    }
    extendsize = MAX(asize,CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE))==NULL){
        return NULL;
    }
    place(bp,asize);
    return bp;
}
//然后是mm_free，注意释放后的内存块要插入相应的空闲链表上。

void mm_free(void *ptr){
    if (ptr == 0)
        return;
    size_t size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    ptr = coalesce(ptr);
    insertFreeList(ptr);
}
//然后是find_fit，寻找合适的内存块分配。

void *find_fit(int turn, size_t asize){
    void *res = NULL;
    // 如果当前链表中的空闲块不够，可以借用更大的空闲链表中的块
    while (turn <=8)
    {
        res = gfreeList+turn*WSIZE;
        while ((res = NEXTP_BLKP(res)) != NULL)
        { // 第8块是4096~无穷，所以空间可能不够
          if (GET_SIZE(HDRP(res)) >= asize)
            {
              return res;   
            }
        }
        turn++;
     }
    return NULL;
}
//place函数用于处理分配内存后的内存块分块和空闲链表删除节点。deleteListNode函数用于从空闲链表中删除节点。

static void place(void *bp,size_t asize){
  size_t csize;
  csize = GET_SIZE(HDRP(bp)) - asize;
  // 将bp分配出来，那么要删除空闲链表中相应的节点
  deleteListNode(bp);
  if(csize >= DSIZE*2){  //需要分割
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(csize, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(csize, 0));
    // 将剩下的部分插入回链表中
    insertFreeList(NEXT_BLKP(bp));
  }else{
    PUT(HDRP(bp), PACK(GET_SIZE(HDRP(bp)), 1));
    PUT(FTRP(bp), PACK(GET_SIZE(HDRP(bp)), 1));
  }
}

void deleteListNode(void *bp)
{
// 分是否是链表的最后一个节点来分别删除节点。
  PUT(NEXT(PRED_BLKP(bp)), NEXTP_BLKP(bp));
  if(NEXTP_BLKP(bp)!=NULL)
    PUT(PRED(NEXTP_BLKP(bp)), PRED_BLKP(bp));
}
//mm_realloc和前一种方法没区别。

void *mm_realloc(void *ptr, size_t size)
{
    size_t oldsize;
    void *newptr;

    if(size == 0) {
        mm_free(ptr);
        return NULL;
    }

    if(ptr == NULL) {
        return mm_malloc(size);
    }

    newptr = mm_malloc(size);
    if(!newptr) {
         return NULL;
    }

    memcpy(newptr, ptr, size);
    mm_free(ptr);
    return newptr;
}
/*
测试结果如下：

Results for mm malloc:
trace  valid  util     ops      secs  Kops
 0       yes   98%    5694  0.000177 32224
 1       yes   94%    5848  0.000252 23170
 2       yes   98%    6648  0.000228 29171
 3       yes   99%    5380  0.000174 30884
 4       yes   66%   14400  0.000230 62636
 5       yes   89%    4800  0.000313 15326
 6       yes   85%    4800  0.000346 13861
 7       yes   55%   12000  0.000278 43088
 8       yes   51%   24000  0.001006 23866
 9       yes   30%   14401  0.216739    66
10       yes   45%   14401  0.003779  3811
Total          74%  112372  0.223523   503

Perf index = 44 (util) + 34 (thru) = 78/100
还是增加了20多分，接下来可以通过以下几个方面改进：

从首次适配改为最佳适配

空闲链表的插入从首插法改为按照地址大小插入

从立即合并修改为延时合并。
*/