#include<stdio.h>
#include<stdlib.h>
void main()
{
    printf("[----- [������] [2021041075] -----]\n");

    int **x; //���������� x
    printf("sizeof(x) = %lu\n", sizeof(x)); //������ x���� �ּҰ� ����Ǿ��ֱ� ������ 4bytes
    printf("sizeof(*x) = %lu\n", sizeof(*x)); //�̱������� x���� �ּҰ� ����Ǿ��ֱ� ������ 4bytes
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //���������� x���� ���� ����Ǿ��ִµ� int �ڷ����̱� ������ 4bytes
}