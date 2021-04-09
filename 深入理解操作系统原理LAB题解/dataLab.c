//csapp���׵ĵ�һ��ʵ���⣬linux���������С��޸�bits.c�ļ��еĸ���������ʵ��Ԥ�ڹ��ܼ��ɡ�

//0x0 �����
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}
//~(~x&~y)�ҳ����е�1:1��0:1��1:0�����Ӧλ����Ϊ1��~(x&y)�ҳ����е�0:0��1:0��0:1�������Ӧλ����Ϊ1��Ȼ����������ٽ���&������
//��ֻʣ��1:0��0:1λ�ϵ�1���ڣ�����������

//0x1 ����Сֵ
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x1<<31;
}
//�з���������СֵΪ0x80000000����ôֱ�ӽ�1����31λ����(��Ŀ��˵����32λ��int��)��

//0x2 �ж��Ƿ������ֵ
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return !((x^(~(x+1)))|(!(~x)));
}
//���ֵ�Ķ����Ʊ�ʾΪ��0x7FFF,��x^(~(x+1)Ӧ��Ϊ0�����ǻ���������-1��ҲΪ0������ʹ��!(~x)�ų�-1.

//0x3 �ж����е�����λ�Ƿ�Ϊ1
/* 
 *   allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int temp = 0xAA;
  temp = temp + (temp<<8) + (temp<<16) + (temp<<24);
  return !((temp&x)^temp);
}
//���ȵõ�һ������temp�������е�����λ��Ϊ1����Ϊ0xAAAAAAAA��������x�������������ô�����������
//1��ֻ�����е�����λΪ1����ô�ٺ�temp������򣬷��ؽ������0����ȡ�����ɡ�
//2���������е�����λ��Ϊ1�����߲�ֹ����λΪ1����ô����Ľ����Ȼ��������λ����ĵط���1��������λΪ1��
//��ô�����tempȡ���ͻ�Ϊ1��ȡ����Ϊ0.


//0x4 ȡ�෴��
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
//ȡ����һ���ɣ���Ƶ������ϸ����Ϊ��ȡ����һΪ�෴����

//0x5 �ж��Ƿ�Ϊ���ֵ�ascii��
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int temp1 = ~0x30+1;
  int temp2 = (1<<31) + ~0x3a + 1;
  return (!((x+temp1)>>31)) & (!((x+temp2)>31));
}
//��Ҫ�ж������Ƿ���0x30��0x3a֮�䣬��ô����������temp1��temp2��temp1��-0x30��x����temp�������λӦ��Ϊ0��
//temp2Ϊ���������ֵ����-0x3a��x�����������λӦ��Ϊ0��Ȼ��x�ʹ��ڵ���0x30����С�ڵ���0x3a�ˡ�temp2����ʽ��Ϊ�˱��⸺��ʱ�������

//0x6 x?y:z
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int temp = ~(!!x) + 1;
  return (temp & y) + (~temp & z);
}
//��x��Ϊ�棬��ô����ת��Ϊ0xFFFF������Ϊ�棬����ת����0x0���������y��z������������ɡ�

//0x7 x<=y
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sym = (x>>31) + (y>>31);
  inyt num1 = !((y + (~x) + 1)>>31);
  int symx = x >>31 & 1;
  return (sym & symx) | ((~sym) & num1);
}
//�����жϳ����������ֵķ��ţ����Ƿ���ͬ�ţ�����ţ���ôxΪ��������·���1�����򷵻�0��������ͬ�ţ�y����x���෴����ȡ�����λ��
//�����Ϊ�����򷵻�0��Ϊ������1.

//0x8 �߼���
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return ((x |(~x+1))>>31)+1;
}
//��0��������Լ����෴�����л��������ô����λ�ض�Ϊ1��Ȼ�����ƾ͵õ�0xFFFF�Լ�0x0����һ�󼴿ɵ�0��1.

//0x9 һ�����ò����ʾ������Ҫ��λ��
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int n = 0;
  x ^=(x<<1);
  n += ((!!(x&((~0)<<(n+16))))<<4 );
  n += ((!!(x&((~0)<<(n+8)))) <<3 );
  n += ((!!(x&((~0)<<(n+4)))) <<2 );
  n += ((!!(x&((~0)<<(n+2)))) <<1 );
  n += (!!(x&((~0)<<(n+1))));
  return n + 1;
}
//�����������ҵ����һ��1���ɣ����ڸ������ҵ����һ��0���ɣ�����ٽ���һ��1��0��λ����1(����λ)���ɡ�



//0xa ���������
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exp_mask = 0x7f800000;
   // 1[000 ..00 0]111 ..11
   // 1 is where exp is. to overlay exp
   int anti_exp_mask = 0x807fffff;
   int exp = (uf&exp_mask)>>23;
   int sign = uf&(1<<31);
   if(exp==0) return uf<<1|sign;
   if(exp==255) return uf;
   exp++;
   if(exp==255) return exp_mask|sign;
   return (exp<<23)|(uf&anti_exp_mask);
}
int floatFloat2Int(unsigned uf) {
     int sign = uf>>31;
   int exp = ((uf&0x7f800000)>>23)-127;
   // complements shadowed 1 ahead of number
   int frac = (uf&0x007fffff)|0x00800000;
   // ignore sign and judge 0
   if(!(uf&0x7fffffff)) return 0;
 
   // overflow
   if(exp > 31) return 0x80000000;
   // decimal cast to 0
   if(exp < 0) return 0;
 
   // 23 is the number of frac bits 32 - 9 = 23
   // we need to complement 0
   if(exp > 23) frac <<= (exp - 23);
   else frac >>= (23 - exp);
 
   // check whether overflow
   if(!((frac >> 31) ^ sign)) return frac; // sign is same with before
   // sign is 1 and sign is different from before, overflow
   else if(frac >> 31) return 0x80000000; 
   // sign is different from before and now is positive, get the minus
   else return ~frac + 1;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    if (x >= -149 && x <= -127) {
    // for denormal number
    int i = 149 + x;
    return 1 << i;
  } else {
    // 2.0^x = (1.0 * 2^1)^x = 1.0 * 2^x
    // x cant be bigger than 255
    int exp = x + 127;
    if(exp <= 0) return 0;
    if(exp >= 255) return 0x7f800000; // Positive infinity
    return exp << 23;
  }
}