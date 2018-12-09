#include <stdio.h>

int foo(int a)
{
    int tmp = a * 2;
    return tmp + 69; 
}

int main(int argc, char** argv)
{
    if (argc == 0)
    {
        printf("argc is 0\n");
    } else {
        printf("argc is not 0\n");
    }

    int a = 55;
    int b = a + foo(a);
    int c = foo(c);
    return 0;
}