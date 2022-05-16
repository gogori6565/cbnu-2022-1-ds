#include <stdio.h>
void print1 (int *ptr, int rows);

int main()
{
    printf("[----- [이주현] [2021041075] -----]\n");
    
    int one[] = {0, 1, 2, 3, 4};
    printf("one = %p\n", one);          //배열 one의 배열이름 = 주소
    printf("&one = %p\n", &one);        //베열 one의 주소값
    printf("&one[0] = %p\n", &one[0]);  //배열 one의 0번째 요소의 주소값
    /*위 셋다 같은 값*/
    printf("\n");
    print1(&one[0], 5); //print1함수 호출 (배열 one의 주소, 5 넘김)
    return 0;
}

void print1 (int *ptr, int rows)
{/* print out a one-dimensional array using a pointer */
    int i;
    printf ("Address \t Contents\n");
    for (i = 0; i < rows; i++)
    printf("%p \t %5d\n", ptr + i, *(ptr + i)); //ptr이 가지고 있는 값 = one의 주소 -> ptr+i = ptr + (i*sizeof(int)) = 배열 one의 i번째 요소의 주소
                                                //*(ptr+i) = 배열 one의 i번째 요소의 값
    printf("\n");
}