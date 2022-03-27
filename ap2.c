#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("[----- [이주현] [2021041075] -----]\n");
    
    int list[5];   //배열 list
    int *plist[5]; //5개의 int 포인터 배열 plist

    list[0] = 10;  //배열 list 0번째 요소 = 10
    list[1] = 11;  //배열 list 1번째 요소 = 11
    plist[0] = (int*)malloc(sizeof(int));  //plist 0번째 요소에 동적할당

    printf("list[0] \t= %d\n", list[0]);  //배열 list 0번째 요소의 값 = 10
    printf("address of list \t= %p\n", list);  //배열 list의 배열이름 = 주소
    printf("address of list[0] \t= %p\n", &list[0]); //배열 list 0번째의 주소값 = 배열의 주소
    printf("address of list + 0 \t= %p\n", list+0);  //배열이름 list(주소)에 + 0*sizeof(int) = 배열의 주소
    printf("address of list + 1 \t= %p\n", list+1);  //배열이름 list(주소)에 + 1*sizeof(int) = 배열 list 1번째 요소의 주소
    printf("address of list + 2 \t= %p\n", list+2);  //배열이름 list(주소)에 + 2*sizeof(int) = 배열 list 2번째 요소의 주소
    printf("address of list + 3 \t= %p\n", list+3);  //배열이름 list(주소)에 + 3*sizeof(int) = 배열 list 3번째 요소의 주소
    printf("address of list + 4 \t= %p\n", list+4);  //배열이름 list(주소)에 + 4*sizeof(int) = 배열 list 4번째 요소의 주소
    printf("address of list[4] \t= %p\n", &list[4]); //배열 list 4번째 요소의 주소값 = list+4
    free(plist[0]); //동적할당 해제
}