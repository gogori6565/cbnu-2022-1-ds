#include <stdio.h>
struct student { //구조체 student 선언
char lastName[13]; /* 13 bytes */
int studentId; /* 4 bytes */
short grade; /* 2 bytes */
}; //총 19bytes

int main()
{
    printf("[----- [이주현] [2021041075] -----]\n");

    struct student pst; //구조체 student의 변수 pst 선언
    printf("size of student = %ld\n", sizeof(struct student)); //구조체 student의 크기 = 24bytes
    /*
      총 19bytes인데 왜 24bytes 출력?
      padding(채워넣기)되었음. (padding은 컴파일러마다 다를 수 있음)
      13bytes -> 16bytes (+3bytes)
      4bytes
      2bytes -> 4bytes (+2bytes)
      총 5bytes 채워넣기 돼서 총 19+5 = 24bytes
    */
    printf("size of int = %ld\n", sizeof(int)); //int 자료형의 크기 = 4bytes
    printf("size of short = %ld\n", sizeof(short)); //short 자료형의 크기 = 2bytes
}