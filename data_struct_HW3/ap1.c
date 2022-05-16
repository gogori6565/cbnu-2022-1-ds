#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("[----- [이주현] [2021041075] -----]\n");

    int list[5];              //배열 list
    int *plist[5] = {NULL,};  //5개의 int 포인터 배열 plist

    plist[0] = (int *)malloc(sizeof(int));  //plist 0번째 요소에 동적할당

    list[0] = 1;      //list 0번째 요소 = 1
    list[1] = 100;    //list 1번째 요소 = 2
    *plist[0] = 200;  //plist 0번째가 가리키고 있는 곳의 값이 200

    printf("value of list[0] = %d\n", list[0]);       //배열 list의 0번째 요소에 저장된 값 = 1
    printf("address of list[0] = %p\n", &list[0]);    //배열 list의 0번째의 주소값 = list의 주소값 
    printf("value of list = %p\n", list);             //배열 list의 배열이름 = 주소
    printf("address of list (&list) = %p\n", &list);  //배열 list의 주소값 = list = &list
    printf("----------------------------------------\n\n");

    printf("value of list[1] = %d\n", list[1]);        //배열 list의 1번째 요소에 저장된 값 = 100
    printf("address of list[1] = %p\n", &list[1]);     //배열 list의 1번째의 주소값 = &list[0]+(1*sizeof(int))
    printf("value of *(list+1) = %d\n", *(list + 1));  //배열이름 list(주소)에 + (1*sizeof(int) 한 주소가 참조하는 값= list[1] = 100
    printf("address of list+1 = %p\n", list+1);        //배열이름 list(주소)에 + (1*sizeof(int) = &list[1]
    printf("----------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]); //포인터 배열 plist의 0번째에서 역참조하는 값 = 200
    printf("&plist[0] = %p\n", &plist[0]);          //포인터 배열 plist의 0번째의 주소값 = plist의 주소값
    printf("&plist = %p\n", &plist);                //포인터 배열 plist의 주소값
    printf("plist = %p\n", plist);                  //포인터 배열 plist의 배열이름 = 주소
    printf("plist[0] = %p\n", plist[0]);            //포인터 배열 plist의 0번째 요소에 저장된 값 = 주소 <- 동적할당 받음
    printf("plist[1] = %p\n", plist[1]);            //포인터 배열 plist의 1번째 요소에 저장된 값 = 주소 <-Null
    printf("plist[2] = %p\n", plist[2]);            //포인터 배열 plist의 2번째 요소에 저장된 값 = 주소 <-Null
    printf("plist[3] = %p\n", plist[3]);            //포인터 배열 plist의 3번째 요소에 저장된 값 = 주소 <-Null
    printf("plist[4] = %p\n", plist[4]);            //포인터 배열 plist의 4번째 요소에 저장된 값 = 주소 <-Null
    free(plist[0]);                                 //동적할당 해제
}