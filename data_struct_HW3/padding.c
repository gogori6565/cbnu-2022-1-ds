#include <stdio.h>
struct student { //����ü student ����
char lastName[13]; /* 13 bytes */
int studentId; /* 4 bytes */
short grade; /* 2 bytes */
}; //�� 19bytes

int main()
{
    printf("[----- [������] [2021041075] -----]\n");

    struct student pst; //����ü student�� ���� pst ����
    printf("size of student = %ld\n", sizeof(struct student)); //����ü student�� ũ�� = 24bytes
    /*
      �� 19bytes�ε� �� 24bytes ���?
      padding(ä���ֱ�)�Ǿ���. (padding�� �����Ϸ����� �ٸ� �� ����)
      13bytes -> 16bytes (+3bytes)
      4bytes
      2bytes -> 4bytes (+2bytes)
      �� 5bytes ä���ֱ� �ż� �� 19+5 = 24bytes
    */
    printf("size of int = %ld\n", sizeof(int)); //int �ڷ����� ũ�� = 4bytes
    printf("size of short = %ld\n", sizeof(short)); //short �ڷ����� ũ�� = 2bytes
}