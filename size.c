#include<stdio.h>
#include<stdlib.h>
void main()
{
    printf("[----- [이주현] [2021041075] -----]\n");

    int **x; //이중포인터 x
    printf("sizeof(x) = %lu\n", sizeof(x)); //포인터 x에는 주소가 저장되어있기 때문에 4bytes
    printf("sizeof(*x) = %lu\n", sizeof(*x)); //싱글포인터 x에는 주소가 저장되어있기 때문에 4bytes
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //더블포인터 x에는 값이 저장되어있는데 int 자료형이기 때문에 4bytes
}