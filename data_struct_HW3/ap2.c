#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("[----- [������] [2021041075] -----]\n");
    
    int list[5];   //�迭 list
    int *plist[5]; //5���� int ������ �迭 plist

    list[0] = 10;  //�迭 list 0��° ��� = 10
    list[1] = 11;  //�迭 list 1��° ��� = 11
    plist[0] = (int*)malloc(sizeof(int));  //plist 0��° ��ҿ� �����Ҵ�

    printf("list[0] \t= %d\n", list[0]);  //�迭 list 0��° ����� �� = 10
    printf("address of list \t= %p\n", list);  //�迭 list�� �迭�̸� = �ּ�
    printf("address of list[0] \t= %p\n", &list[0]); //�迭 list 0��°�� �ּҰ� = �迭�� �ּ�
    printf("address of list + 0 \t= %p\n", list+0);  //�迭�̸� list(�ּ�)�� + 0*sizeof(int) = �迭�� �ּ�
    printf("address of list + 1 \t= %p\n", list+1);  //�迭�̸� list(�ּ�)�� + 1*sizeof(int) = �迭 list 1��° ����� �ּ�
    printf("address of list + 2 \t= %p\n", list+2);  //�迭�̸� list(�ּ�)�� + 2*sizeof(int) = �迭 list 2��° ����� �ּ�
    printf("address of list + 3 \t= %p\n", list+3);  //�迭�̸� list(�ּ�)�� + 3*sizeof(int) = �迭 list 3��° ����� �ּ�
    printf("address of list + 4 \t= %p\n", list+4);  //�迭�̸� list(�ּ�)�� + 4*sizeof(int) = �迭 list 4��° ����� �ּ�
    printf("address of list[4] \t= %p\n", &list[4]); //�迭 list 4��° ����� �ּҰ� = list+4
    free(plist[0]); //�����Ҵ� ����
}