/*
�ڴ�����������ʵ�飬Ҫ��ʵ��һ���ڴ����������Ҫ���mm.c�ļ��е�mm_init()��mm_alloc()��mm_free()��mmrealloc()������
ʹ��CSAPP�н��ܵļ��ַ�ʽ��ʵ���ڴ����������ʽ�������������ϲ���ʽΪ�����ϲ�������ԭ��Ϊ�״�ƥ�䡣
*/



//�����ṩ��һϵ��Ҫʹ�õ��ĺ꣬�������£�
#define WSIZE     4
#define DSIZE     8
/* Ĭ����չ�Ѵ�С */
#define CHUNKSIZE (1<<12)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

// ȡ���ײ�/β����ֵ
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

//��ʼ���ڴ��������

int mm_init(void)
{
  // heap_listpָ���ڴ���ʼλ��
     if ((heap_listp = mem_sbrk(4*WSIZE))==(void *)-1){
        return -1;
    }
    PUT(heap_listp,0);//˫�ֶ��룬��һ���֡�
    PUT(heap_listp+(1*WSIZE),PACK(DSIZE,1));
    PUT(heap_listp+(2*WSIZE),PACK(DSIZE,1));// ��ʼ
    PUT(heap_listp+(3*WSIZE),PACK(0,1)); // ��β
    heap_listp += (2*WSIZE); // ָ���һ���ڴ��
    if (extend_heap(CHUNKSIZE/WSIZE)==NULL){
        return -1;
    }
    return 0;
}
###mm_alloc()

//���ڴ������������size��С���ڴ档

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

//�ͷŵ�bpָ����ڴ�顣

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

//��ptrָ������ݷŵ�����Ϊsize�����ڴ浱��ȥ��

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
//����Ѱ�ҵ�һ���ܹ����������ڴ��С�Ŀ飬�˴�������зָ�״�����������
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
//��������Ŀ��п��ȥ�����ڴ��ʣ���ڴ���ڵ�����С���Сʱ
//�Ż�Կ��п���зָ
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
//���ڴ治��ʱ����չ�ѵĴ�С��
static void *extend_heap(size_t words)
{
  char *bp;
  int size;
  // �ڴ����
  size = words%2 ? (words+1)*WSIZE :words*WSIZE;
  if (-1 == (bp = mem_sbrk(size)))
  {
    return NULL;
  }
  
  // ����������ڴ�����Ϊfree��
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));
  
  // �ϲ��ڴ�
  return coalesce(bp);
}
//���ͷŵĿ����ڴ����кϲ���
static void *coalesce(void *bp){
    size_t  prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t  next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t  size = GET_SIZE(HDRP(bp));

//��һ�������ǰ���޿��п�
    if (prev_alloc && next_alloc) {
        return bp;
//�ڶ�����������治�ǿ��п�
    }else if (prev_alloc && !next_alloc){
          size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
            PUT(HDRP(bp), PACK(size,0));
            PUT(FTRP(bp), PACK(size,0));
//�����������ǰ�治�ǿ��п�
    }else if (!prev_alloc && next_alloc){
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp),PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)),PACK(size,0));
        bp = PREV_BLKP(bp);
//���һ�������ǰ���п��п�.
    }else {
        size +=GET_SIZE(FTRP(NEXT_BLKP(bp)))+ GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(NEXT_BLKP(bp)),PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)),PACK(size,0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}
/*
###���Խ��

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
//Ϊ�˼����ڴ���Ƭ�����Բ���������䣬�ҵ���С�Ŀɷ����ڴ�顣
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
//eeeee,����Ҳû�߶��٣�����ֻ��50+��ÿ�η��䶼Ҫ�������������ǱȽ����ģ�
//������ʽ�����������ʱ��ӿ�������ؽ��͵����п���أ��ټ��ϲ��÷�������
//�������˼�ǲ�ͬ��С�Ŀ����ڴ��ʹ�ò�ͬ�Ŀ������������ڴ������ʿ��Խӽ�������䡣

/*
����mm_init()��Ȼ����Ҫ�޸ĵģ�ȷ��һ������С�Ƕ����ֽڣ�����˫�ֶ��룬�ټ�����Ҫͷ����β����һ��pre��һ��next������������Ҫ4���֡�
Ҳ����16���ֽڣ��ʿ��п�Ĵ�С�����������������֣�
16~31 32~63 64~127 128~255 256~511 512~1023 1024~2017 2048~4095 4096~INT_MAC
��Ϊ�̶���С�Ŀ��п�һ�㲻�ָ�ģ����ϲ��ģ��������һ�����п�����ķ�Χ���󣬺���������ܴ���ڲ���Ƭ��
�������һ���汾��init����������汾��Ҫ��ӾŸ��ڵ㣬����ָ����ֿ����������Ե�һ������Ŀռ����9+3Ϊ12.
*/
// ����ӵĺ�
// PRED��NEXT��˳���е��Ť��������Ϊroot�ڵ�ֻ��next��Ϊ�˷����д�������ˡ�
#define PRED(bp) ((char*)(bp) + WSIZE)
#define NEXT(bp) ((char*)bp)
#define PRED_BLKP(bp) (GET(PRED(bp)))
#define NEXTP_BLKP(bp) (GET(NEXT(bp)))
// �洢��������
static char *gfreeList = 0;
int mm_init(void)
{
  // heap_listpָ�������ʼλ��
     if ((heap_listp = mem_sbrk(12*WSIZE))==(void *)-1){
        return -1;
    }
    PUT(heap_listp,0��NULL);//δ�����ڴ棬������ָ��null
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
//Ȼ�����޸�extend_heap��������Ϊ����ıض���һ�����п飬����Ҫ���������ʵĿ��������С�
//��ʼ����������Ƴɹ̶���С���п飬���ָ���ϲ��ģ����������и��������������ص��ⲿ��Ƭ�������޸ĳ���Ҫ�ϲ�Ҫ�ָ�İ汾��

static void *extend_heap(size_t words)
{
  char *bp;
  size_t size;
  size = words%2 ? (words+1)*WSIZE : words*WSIZE;  //�Դ�С˫�ֶԶ���

  if ((void*)-1 == (bp = mem_sbrk(size)))
  {
    return NULL;
  }

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

  //ǰ�洦��һ����Ȼ��������п��ǰ�̺ͺ���ÿ�
  PUT(PRED(bp), NULL);
  PUT(NEXT(bp), NULL);

  //�ϲ���������е�free�ڴ�鵱�С�
  bp = coalesce(bp);
  bp = insertFreeList(bp);

  return bp;
}
//Ȼ���Ǻϲ�����coalesce�����ڽ��ͷŵ��ڴ��ϲ�������һ�ַ�����࣬��ͬ��������˿�������Ĺ���

static void *coalesce(void *bp){
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));
  
  if (prev_alloc && next_alloc){
    return bp;
  }else if (prev_alloc && !next_alloc){
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    deleteListNode(NEXT_BLKP(bp));// �������п�ϲ�����ô��ȻҪɾ��һ�����п�
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }else if (!prev_alloc && next_alloc){
    size += GET_SIZE(FTRP(PREV_BLKP(bp)));
    deleteListNode(PREV_BLKP(bp));// ͬ��
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }else{
    size += GET_SIZE(HDRP(NEXT_BLKP(bp))) + GET_SIZE(FTRP(PREV_BLKP(bp)));
    deleteListNode(NEXT_BLKP(bp));// ͬ��
    deleteListNode(PREV_BLKP(bp));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }
  return bp;
}
//Ȼ�����insertFreeList�����������п���뵽���ʵ�������ȥ������ͷ�巨�����ͷŵĿ�ֱ�ӷ������������ײ���

static void * insertFreeList(void * ptr)
{
  size_t size = GET_SIZE(HDRP(ptr));
  int turn = findTurn(size);// �ô洢�ڵڼ���������
  void *root = gfreeList+turn*WSIZE;

  // ����������û�нڵ㣬ֱ�Ӳ��뼴�ɣ�������Ҫ�޸�����˳��
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
//Ȼ����findTurn����������ȷ��size��С���ڴ��Ӧ�÷����ĸ��ڴ������¡�

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
//Ȼ����mm_malloc����������һ��û������

void *mm_malloc(size_t size){
    size_t asize;
    size_t extendsize;
    char *bp;
    if (size ==0) return NULL;
    int turn;

    asize = size<=DSIZE ? 2*DSIZE : DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
  
    // ����ָ����С�Ŀ��С�
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
//Ȼ����mm_free��ע���ͷź���ڴ��Ҫ������Ӧ�Ŀ��������ϡ�

void mm_free(void *ptr){
    if (ptr == 0)
        return;
    size_t size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    ptr = coalesce(ptr);
    insertFreeList(ptr);
}
//Ȼ����find_fit��Ѱ�Һ��ʵ��ڴ����䡣

void *find_fit(int turn, size_t asize){
    void *res = NULL;
    // �����ǰ�����еĿ��п鲻�������Խ��ø���Ŀ��������еĿ�
    while (turn <=8)
    {
        res = gfreeList+turn*WSIZE;
        while ((res = NEXTP_BLKP(res)) != NULL)
        { // ��8����4096~������Կռ���ܲ���
          if (GET_SIZE(HDRP(res)) >= asize)
            {
              return res;   
            }
        }
        turn++;
     }
    return NULL;
}
//place�������ڴ�������ڴ����ڴ��ֿ�Ϳ�������ɾ���ڵ㡣deleteListNode�������ڴӿ���������ɾ���ڵ㡣

static void place(void *bp,size_t asize){
  size_t csize;
  csize = GET_SIZE(HDRP(bp)) - asize;
  // ��bp�����������ôҪɾ��������������Ӧ�Ľڵ�
  deleteListNode(bp);
  if(csize >= DSIZE*2){  //��Ҫ�ָ�
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(csize, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(csize, 0));
    // ��ʣ�µĲ��ֲ����������
    insertFreeList(NEXT_BLKP(bp));
  }else{
    PUT(HDRP(bp), PACK(GET_SIZE(HDRP(bp)), 1));
    PUT(FTRP(bp), PACK(GET_SIZE(HDRP(bp)), 1));
  }
}

void deleteListNode(void *bp)
{
// ���Ƿ�����������һ���ڵ����ֱ�ɾ���ڵ㡣
  PUT(NEXT(PRED_BLKP(bp)), NEXTP_BLKP(bp));
  if(NEXTP_BLKP(bp)!=NULL)
    PUT(PRED(NEXTP_BLKP(bp)), PRED_BLKP(bp));
}
//mm_realloc��ǰһ�ַ���û����

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
���Խ�����£�

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
����������20��֣�����������ͨ�����¼�������Ľ���

���״������Ϊ�������

��������Ĳ�����ײ巨��Ϊ���յ�ַ��С����

�������ϲ��޸�Ϊ��ʱ�ϲ���
*/