#include <stdio.h>

struct student1 {  //구조체 student1
    char lastName;
    int studentId;
    char grade;
};
typedef struct {
    char lastName;
    int studentId;
    char grade;
} student2;  //typedef를 사용한 구조 데이터 타입 student2 생성

int main() {

    printf("[----- [이주현] [2021041075] -----]\n");
    
    struct student1 st1 = {'A', 100, 'A'};  //구조체 student1의 변수 st1
    printf("st1.lastName = %c\n", st1.lastName);   //A
    printf("st1.studentId = %d\n", st1.studentId); //100
    printf("st1.grade = %c\n", st1.grade);         //A

    /*
      typedef로 새로운 자료형을 정의했으니 
      student1과 달리 struct 없이 변수 선언 가능
    */
    student2 st2 = {'B', 200, 'B'}; //구조체 student2의 변수 st2
    printf("\nst2.lastName = %c\n", st2.lastName); //B
    printf("st2.studentId = %d\n", st2.studentId); //200
    printf("st2.grade = %c\n", st2.grade);         //B

    student2 st3; //구조체 student2의 변수 st3
    st3 = st2; //구조 치환 (st2와 동일하게 들어감)
    printf("\nst3.lastName = %c\n", st3.lastName); //B
    printf("st3.studentId = %d\n", st3.studentId); //200
    printf("st3.grade = %c\n", st3.grade);         //B

    /* equality test */
    if(st3 == st2) /* not working */ //구조체 변수끼리 비교연산자 == 사용불가. 따로따로 비교해야함
    printf("equal\n"); //비교연산자를 쓰지 않고 하나하나 비교했다면 equal이 나왔을 것
    else
    printf("not equal\n");
    return 0;
}