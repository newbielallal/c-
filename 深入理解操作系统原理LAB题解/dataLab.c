//csapp配套的第一个实验题，linux环境下运行。修改bits.c文件中的各个函数，实现预期功能即可。

//0x0 求异或
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
//~(~x&~y)找出所有的1:1、0:1、1:0将其对应位设置为1，~(x&y)找出所有的0:0、1:0、0:1，将其对应位设置为1。然后两个结果再进行&操作，
//就只剩下1:0、0:1位上的1还在，即可完成异或。

//0x1 求最小值
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x1<<31;
}
//有符号数的最小值为0x80000000，那么直接将1左移31位即可(题目已说明是32位的int型)。

//0x2 判断是否是最大值
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
//最大值的二进制表示为：0x7FFF,那x^(~(x+1)应该为0，但是还有特殊项-1，也为0，所以使用!(~x)排除-1.

//0x3 判断所有的奇数位是否为1
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
//首先得到一个数字temp，其所有的奇数位都为1，即为0xAAAAAAAA，将其与x进行与操作，那么分两种情况：
//1、只有所有的奇数位为1，那么再和temp进行异或，返回结果就是0，再取反即可。
//2、不是所有的奇数位都为1，或者不止奇数位为1，那么相与的结果必然会在奇数位以外的地方有1或者奇数位为1，
//那么最后与temp取异或就会为1，取反则为0.


//0x4 取相反数
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
//取反加一即可，视频中有详细分析为何取反加一为相反数。

//0x5 判断是否为数字的ascii码
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
//需要判断数字是否在0x30到0x3a之间，那么构造两个数temp1、temp2，temp1是-0x30，x加上temp后其符号位应该为0。
//temp2为负数的最大值加上-0x3a，x加上它后符号位应该为0，然后x就大于等于0x30而且小于等于0x3a了。temp2的形式是为了避免负数时计算错误。

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
//即x若为真，那么将其转换为0xFFFF，若不为真，则将其转换成0x0，最后再与y和z进行与操作即可。

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
//首先判断出这两个数字的符号，看是否是同号，若异号，那么x为负的情况下返回1，否则返回0。若两者同号，y加上x的相反数，取其符号位，
//若结果为负数则返回0，为正返回1.

//0x8 逻辑！
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
//除0外的数与自己的相反数进行或操作，那么符号位必定为1，然后左移就得到0xFFFF以及0x0，加一后即可得0和1.

//0x9 一个数用补码表示最少需要几位？
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
//对于正数，找到其第一个1即可，对于负数，找到其第一个0即可，最后再将第一个1或0的位数加1(符号位)即可。



//0xa 浮点数相关
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