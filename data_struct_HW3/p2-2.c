#include <stdio.h>
void print1 (int *ptr, int rows);

int main()
{
    printf("[----- [������] [2021041075] -----]\n");
    
    int one[] = {0, 1, 2, 3, 4};
    printf("one = %p\n", one);          //�迭 one�� �迭�̸� = �ּ�
    printf("&one = %p\n", &one);        //���� one�� �ּҰ�
    printf("&one[0] = %p\n", &one[0]);  //�迭 one�� 0��° ����� �ּҰ�
    /*�� �´� ���� ��*/
    printf("\n");
    print1(&one[0], 5); //print1�Լ� ȣ�� (�迭 one�� �ּ�, 5 �ѱ�)
    return 0;
}

void print1 (int *ptr, int rows)
{/* print out a one-dimensional array using a pointer */
    int i;
    printf ("Address \t Contents\n");
    for (i = 0; i < rows; i++)
    printf("%p \t %5d\n", ptr + i, *(ptr + i)); //ptr�� ������ �ִ� �� = one�� �ּ� -> ptr+i = ptr + (i*sizeof(int)) = �迭 one�� i��° ����� �ּ�
                                                //*(ptr+i) = �迭 one�� i��° ����� ��
    printf("\n");
}