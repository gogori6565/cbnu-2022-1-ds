#include <stdio.h>
#define MAX_SIZE 100
float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main(void)
{
    printf("[----- [������] [2021041075] -----]\n");
    
    for(i=0; i < MAX_SIZE; i++)  //MAX_SIZE(100)��ŭ �ݺ�
    input[i] = i; //input �迭�� 0���� 99������ �ε����� 0~99�� �� ���ʷ� ����
    /* for checking call by reference */
    printf("address of input = %p\n", input); //�迭 input�� �迭�̸� = �ּ�
    answer = sum(input, MAX_SIZE); //sum�Լ� ȣ��, return�� answer�� ����
    printf("The sum is: %f\n", answer); //answer = tempsum = 1~99������ ��
}

float sum(float list[], int n) //list -> call by reference, n ->  call by value
{
    printf("value of list = %p\n", list);      //list�� �� = input�� �ּ�
    printf("address of list = %p\n\n", &list); //list�� �ּ�
    /*input�� �ּҸ� list�� �޾Ƽ� list�� ���� input �迭�� ����*/
    int i;
    float tempsum = 0;
    for(i = 0; i < n; i++) //n(100)��ŭ �ݺ�
        tempsum += list[i]; //tempsum�� input[1]~input[99]������ ��Ұ� ���� ���ϱ�
    return tempsum; //tempsum ��ȯ
}