#include <stdio.h>
int main()
{
    int i, *p; //변수 i, 포인터 변수 p 선언

    i = 10;  //변수 i에 10 저장

    printf("value of i = %d\n", i);     //변수 i의 값 = 10
    printf("address of i = %p\n", &i);  //변수 i의 주소
    printf("value of p = %p\n", p);     //포인터 p에 들어있는 값 (쓰레기값)
    printf("address of p = %p\n", &p);  //포인터 p의 주소

    p = &i;  //포인터 변수 p에 변수 i의 주소값을 저장

    printf("\n\n----- after p = &i ------------\n\n");  //포인터 p에 변수 i의 주소 저장한 후

    printf("value of p = %p\n", p);         //포인터 p에 들어있는 값 = 변수 i의 주소
    printf("address of p = %p\n", &p);      //포인터 p의 주소 (위와 동일)
    printf("dereferencing *p = %d\n", *p);  //포인터 p가 간접참조하는 값 = 변수 i의 값 = 10
    
    return 0;
}

/*
    포인터는 메모리의 '주소'를 가지고 있는 변수이고,
    * 연산자를 통해 포인터가 가리키는 주소에 저장된 내용을 읽는 간접 참조가 가능하다.
    따라서,
    포인터 변수 p에 i의 주소를 저장하기 이전에는 포인터 p에 쓰레기값이 들어있고, 포인터 p 자체도 주소를 가지고 있다.
    p = &i;를 수행한 후에는 포인터 p의 값은 변수 i의 주소이고, &p는 이전과 동일하게 p 자체의 주소이며,
    간접참조연산자 *는 포인터가 가리키는 주소에 저장된 내용을 읽는 것이기 때문에 *p는 변수 i의 값인 10이다.
*/