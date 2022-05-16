#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("[----- [������] [2021041075] -----]\n");

    int list[5];              //�迭 list
    int *plist[5] = {NULL,};  //5���� int ������ �迭 plist

    plist[0] = (int *)malloc(sizeof(int));  //plist 0��° ��ҿ� �����Ҵ�

    list[0] = 1;      //list 0��° ��� = 1
    list[1] = 100;    //list 1��° ��� = 2
    *plist[0] = 200;  //plist 0��°�� ����Ű�� �ִ� ���� ���� 200

    printf("value of list[0] = %d\n", list[0]);       //�迭 list�� 0��° ��ҿ� ����� �� = 1
    printf("address of list[0] = %p\n", &list[0]);    //�迭 list�� 0��°�� �ּҰ� = list�� �ּҰ� 
    printf("value of list = %p\n", list);             //�迭 list�� �迭�̸� = �ּ�
    printf("address of list (&list) = %p\n", &list);  //�迭 list�� �ּҰ� = list = &list
    printf("----------------------------------------\n\n");

    printf("value of list[1] = %d\n", list[1]);        //�迭 list�� 1��° ��ҿ� ����� �� = 100
    printf("address of list[1] = %p\n", &list[1]);     //�迭 list�� 1��°�� �ּҰ� = &list[0]+(1*sizeof(int))
    printf("value of *(list+1) = %d\n", *(list + 1));  //�迭�̸� list(�ּ�)�� + (1*sizeof(int) �� �ּҰ� �����ϴ� ��= list[1] = 100
    printf("address of list+1 = %p\n", list+1);        //�迭�̸� list(�ּ�)�� + (1*sizeof(int) = &list[1]
    printf("----------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]); //������ �迭 plist�� 0��°���� �������ϴ� �� = 200
    printf("&plist[0] = %p\n", &plist[0]);          //������ �迭 plist�� 0��°�� �ּҰ� = plist�� �ּҰ�
    printf("&plist = %p\n", &plist);                //������ �迭 plist�� �ּҰ�
    printf("plist = %p\n", plist);                  //������ �迭 plist�� �迭�̸� = �ּ�
    printf("plist[0] = %p\n", plist[0]);            //������ �迭 plist�� 0��° ��ҿ� ����� �� = �ּ� <- �����Ҵ� ����
    printf("plist[1] = %p\n", plist[1]);            //������ �迭 plist�� 1��° ��ҿ� ����� �� = �ּ� <-Null
    printf("plist[2] = %p\n", plist[2]);            //������ �迭 plist�� 2��° ��ҿ� ����� �� = �ּ� <-Null
    printf("plist[3] = %p\n", plist[3]);            //������ �迭 plist�� 3��° ��ҿ� ����� �� = �ּ� <-Null
    printf("plist[4] = %p\n", plist[4]);            //������ �迭 plist�� 4��° ��ҿ� ����� �� = �ּ� <-Null
    free(plist[0]);                                 //�����Ҵ� ����
}