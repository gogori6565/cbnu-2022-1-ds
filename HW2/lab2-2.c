#include <stdio.h>

int main()
{
    printf("[----- [이주현] [2021041075] -----]\n");

    int i;
    int *ptr;
    int **dptr;

    i = 1234;

    printf("[checking values before ptr = &i] \n");
    printf("value of i == %d\n", i);        //변수 i의 값 = 1234
    printf("address of i == %p\n", &i);     //변수 i의 주소
    printf("value of ptr == %p\n", ptr);    //포인터 변수 ptr의 값 = 쓰레기값
    printf("address of ptr == %p\n", &ptr); //포인터 변수 ptr의 주소

    ptr = &i; //포인터 변수 ptr에 변수 i의 주소 넣기

    printf("\n[checking values after ptr = &i] \n");
    printf("value of i == %d\n", i);        //변수 i의 값 = 1234
    printf("address of i == %p\n", &i);     //변수 i의 주소
    printf("value of ptr == %p\n", ptr);    //포인터 변수 ptr의 값 = 변수 i의 주소
    printf("address of ptr == %p\n", &ptr); //포인터 변수 ptr의 주소
    printf("value of *ptr == %d\n", *ptr);  //포인터 변수 ptr이 역참조하는 값 = 1234

    dptr = &ptr; //이중포인터 변수 dptr에 포인터 변수 ptr의 주소 넣기

    printf("\n[checking values after dptr = &ptr] \n");
    printf("value of i == %d\n", i);            //변수 i의 값 = 1234
    printf("address of i == %p\n", &i);         //변수 i의 주소
    printf("value of ptr == %p\n", ptr);        //포인터 변수 ptr의 값 = 변수 i의 주소
    printf("address of ptr == %p\n", &ptr);     //포인터 변수 ptr의 주소
    printf("value of *ptr == %d\n", *ptr);      //포인터 변수 ptr이 역참조하는 값 = 1234
    printf("value of dptr == %p\n", dptr);      //이중 포인터 변수 dptr의 값 = 포인터 변수 ptr의 주소
    printf("address of dptr == %p\n", &dptr);    //이중 포인터 변수 dptr의 주소
    printf("value of *dptr == %p\n", *dptr);    //이중 포인터 변수 dptr이 한 번 역참조하는 값 = 포인터 변수 ptr의 값 = 변수 i의 주소
    printf("value of **dptr == %d\n", **dptr);  //이중 포인터 변수 dptr이 두 번 역참조하는 값 = 포인터 변수 ptr이 역참조하는 값 = 변수 i의 값 = 1234

    *ptr = 7777; //포인터 변수 ptr이 역참조하는 값에 7777 대입 = 변수 i에 7777 대입

    printf("\n[after *ptr = 7777] \n");
    printf("value of i == %d\n", i);            //변수 i의 값 = 7777
    printf("value of *ptr == %d\n", *ptr);      //포인터 변수 ptr이 역참조하는 값 = 7777
    printf("value of **dptr == %d\n", **dptr);  //이중포인터 변수 dptr이 두 번 역참조하는 값 = 7777

    **dptr = 8888; //이중포인터 변수 dptr이 두 번 역참조하는 값에 8888 대입 = 변수 i에 8888 대입

    printf("\n[after **dptr = 8888] \n");
    printf("value of i == %d\n", i);            //변수 i의 값 = 8888
    printf("value of *ptr == %d\n", *ptr);      //포인터 변수 ptr이 역참조하는 값 = 8888
    printf("value of **dptr == %d\n", **dptr);  //이중 포인터 변수 dptr이 두 번 역참조하는 값 = 8888

    return 0;
}
