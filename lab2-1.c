#include <stdio.h>

int main()
{
    printf("[----- [이주현] [2021041075] -----]\n");

    char charType;
    int integerType;
    float floatType;
    double doubleType;

    printf("Size of char: %ld byte\n",sizeof(charType));        //변수 charType의 자료형 char의 크기 = 1byte
    printf("Size of int: %ld bytes\n",sizeof(integerType));     //변수 integerType의 자료형 int의 크기 = 4bytes
    printf("Size of float: %ld bytes\n",sizeof(floatType));     //변수 floatType의 자료형 float의 크기 = 4bytes
    printf("Size of double: %ld bytes\n",sizeof(doubleType));   //변수 doubleType의 자료형 double의 크기 = 8bytes

    printf("-----------------------------------------\n");

    printf("Size of char: %ld byte\n",sizeof(char));        //자료형 char의 크기 = 1byte
    printf("Size of int: %ld bytes\n",sizeof(int));         //자료형 int의 크기 = 4bytes
    printf("Size of float: %ld bytes\n",sizeof(float));     //자료형 float의 크기 = 4bytes
    printf("Size of double: %ld bytes\n",sizeof(double));   //자료형 double의 크기 = 8bytes

    printf("-----------------------------------------\n");

    /* 포인터 변수는 메모리 위치를 가리키기 위한 주소를 저장하기 때문에
       sizeof했을 때, 메모리 주소를 담을 수 있는 크기가 반환된다.
       따라서 32bit 컴파일러에서는 4bytes, 64bit 컴파일러에서는 8bytes를 반환한다.
    */
    printf("Size of char*: %ld byte\n",sizeof(char*));
    printf("Size of int*: %ld bytes\n",sizeof(int*));
    printf("Size of float*: %ld bytes\n",sizeof(float*));
    printf("Size of double*: %ld bytes\n",sizeof(double*));
    
    return 0;
}