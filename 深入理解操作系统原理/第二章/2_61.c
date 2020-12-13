#include<stdio.h>

void isAllOne(int x)
{
    printf("%s : is %d!\n", __FUNCITON__, !(x ^ ~0));
}
void isAllZero(int x)
{
    printf("%s : is %d!\n", __FUNCITON__, !(x ^ 0));
}
void lowByteIsAllOne(int x)
{
    x = x & 0xff;
    x = x ^ 0xff;
    printf("%s : is %d!\n", __FUNCITON__, !x);
}

int isSmallEndian()
{
    unsigned int a = 1;
    unsigned char* p = &a;

    if(1 == *p)
    {
        printf("%s : the computer is smallEndian\n!", __FUNCTION__);
        return 1;
    }

    printf("%s : the computer is bigEndian\n!", __FUNCTION__);
    return 0;
}
void highByteIsAllZero(int x)
{
    int len = sizeof(int);
    unsigned char *p = x;

    if(1 == isSmallEndian())
    {
        p = p + (len - 1);
    }
    *p = *p & 0xff;
    printf("%s : is %d!\n", __FUNCITON__, !(*p));
}

int main()
{
    int x = ~0;
    printf("x is %x!\n", x);
    isAllOne(x);
    isAllZero(x);
    highByteIsAllZero(x);
    lowByteIsAllOne(x);

    x = 0x0;
    printf("x is %x!\n", x);
    isAllOne(x);
    isAllZero(x);
    highByteIsAllZero(x);
    lowByteIsAllOne(x);

    x= 0xff;
    printf("x is %x!\n", x);
    isAllOne(x);
    isAllZero(x);
    highByteIsAllZero(x);
    lowByteIsAllOne(x);

    x = 0x123456;
    printf("x is %x!\n", x);
    isAllOne(x);
    isAllZero(x);
    highByteIsAllZero(x);
    lowByteIsAllOne(x);

    return 0;
}