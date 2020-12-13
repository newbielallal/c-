#include<stdio.h>

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
void replaceByte(unsigned int *x, int i, unsigned char b)
{
    int index = 0;
    unsigned char *p = x;

    if(0 == isSmallEndian())
    {
        i = sizeof(int) - (i + 1);
    }

    for(index = 0; index <=i; ++p, ++index)
    {
        if(index == i)
        {
            *p = b;
            break;
        }
    }
}

int main()
{
    unsigned int x = 0x12345678;
    int i = 0;
    unsigned char b = 0xef;

    printf("x is %x!\n", x);
    replaceByte(&x, i, b);
    printf("x is %x!\n", x);

    return 0;
}