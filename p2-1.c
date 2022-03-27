#include <stdio.h>
#define MAX_SIZE 100
float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main(void)
{
    printf("[----- [이주현] [2021041075] -----]\n");
    
    for(i=0; i < MAX_SIZE; i++)  //MAX_SIZE(100)만큼 반복
    input[i] = i; //input 배열에 0부터 99까지의 인덱스에 0~99의 값 차례로 대입
    /* for checking call by reference */
    printf("address of input = %p\n", input); //배열 input의 배열이름 = 주소
    answer = sum(input, MAX_SIZE); //sum함수 호출, return값 answer에 저장
    printf("The sum is: %f\n", answer); //answer = tempsum = 1~99까지의 합
}

float sum(float list[], int n) //list -> call by reference, n ->  call by value
{
    printf("value of list = %p\n", list);      //list의 값 = input의 주소
    printf("address of list = %p\n\n", &list); //list의 주소
    /*input의 주소를 list가 받아서 list를 통해 input 배열에 접근*/
    int i;
    float tempsum = 0;
    for(i = 0; i < n; i++) //n(100)만큼 반복
        tempsum += list[i]; //tempsum에 input[1]~input[99]까지의 요소값 누적 합하기
    return tempsum; //tempsum 반환
}