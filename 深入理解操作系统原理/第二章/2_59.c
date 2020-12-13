#include<stdio.h>

int main()
{
    int x = 0x12345678;
    int y = 0x87654321;

    printf("x is %x!\n", x);
    printf("y is %x!\n", y);
    printf("answer is %x!\n", (x & 0xff) | (y & (~0 ^ 0xff)));

    return 0;

}