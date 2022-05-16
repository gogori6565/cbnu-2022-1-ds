#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{
    char command;
    printf("[----- [이주현]  [2021041075] -----]\n");

    int row, col;
    srand(time(NULL)); //난수의 중복을 막기 위해

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); //행, 열 값 입력받기
    /*행렬 a, b, a_t(a의 전치행렬) 생성*/
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //a, b 행렬이 NULL을 가지는 지 검사

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //메뉴 수행 알파벳 받기

        switch(command) {
        case 'z': case 'Z': //행렬 0~19 사이의 난수 생성
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': //행렬 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //a, b행렬의 덧셈 연산
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //a, b행렬의 빼기 연산
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': //전치행렬 matrix_t 구하기
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //함수 내에서는 col을 전치행렬 t의 row로, row를 col로 사용할 것임 (자세한 건 아래 설명)
            print_matrix(matrix_a_t, col, row); //전치행렬 출력
            break;
        case 'm': case 'M': //a, t행렬의 곱셈 연산
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': //동적할당을 해제하는 동시에 do while문도 종료함
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: //비정상적인 command 값이 입력되었을 경우 출력
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); //q나 Q가 들어오면 do while문을 종료

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    //전처리 검사
	if (row <= 0 || col <= 0) { //행 또는 열이 0이거나 0보다 작은지 검사
		printf("Check the size of row and col!\n");
		return NULL;
	}

    int **x, i;
    x=(int**)malloc(sizeof(int*)*row); //주소를 저장하는 동적할당
    // MALLOC(x,row*sizeof(*x));

    for(i=0;i<row;i++)
    {
        x[i]=(int*)malloc(sizeof(int)*col);  //값을 저장하는 동적할당
        // MALLOC(x[i],col*sizeof(**x));
    }

    //후처리 검사
	if (x == NULL) { //행렬이 NULL 값을 가지는지 검사
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

    return x; //matrix_(?)에 저장해야 하므로 행렬 x를 반환값으로 전달
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    //전처리 검사
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%3d ",matrix[i][j]); //행렬 출력
        }
        printf("\n"); //row(행) 하나 출력 후 개행
    }
    printf("\n");

    //후처리 검사
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return;
	}
    return ;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    //전처리 검사
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i;
    for(i=0;i<row;i++)
    {
        free(matrix[i]); //가로공간 해제
    }
    free(matrix); //세로공간 해제
    // 해제 순서는 할당과 반대로 가로 공간을 먼저 해제한 다음, 세로 공간에 해당하는 메모리 해제

    return 1;
    //동적할당을 해제하는 함수이므로 후처리 검사는 하지 않는다.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //Initialize Matrix
{
    //전처리 검사
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            matrix[i][j]=rand()%20; //0~19사이의 난수를 행렬에 저장
        }
    }

    //후처리 검사
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** add_matrix=create_matrix(row,col); //행렬 a,b를 더한 값을 저장해줄 add_matrix를 생성한다.

    //전처리 검사
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            add_matrix[i][j]=matrix_a[i][j]+matrix_b[i][j]; //배열끼리 더한다
        }
    }

    //후처리 검사 - 행렬 _a,_b,add_ 세 행렬이 NULL값을 가지는 지 검사
	if (matrix_a == NULL || matrix_b == NULL || add_matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    print_matrix(add_matrix,row,col); //add_matrix 행렬 출력
    free_matrix(add_matrix,row,col); //add_matrix 행렬 동적할당 해제
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int ** sub_matrix=create_matrix(row,col); //행렬 a,b를 뺀 값을 저장할 sub_matrix 생성

    //전처리 검사
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            sub_matrix[i][j]=matrix_a[i][j]-matrix_b[i][j]; //배열끼리 뺀다.
        }
    }

    //후처리 검사 - 행렬 _a,_b,sub_ 세 행렬이 NULL값을 가지는 지 검사
	if (matrix_a == NULL || matrix_b == NULL || sub_matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(sub_matrix,row,col); //sub_matrix 행렬 출력
    free_matrix(sub_matrix,row,col); //sub_matrix 행렬 동적할당 해제
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{ //매개변수 row에 col을, col에 row를 넣음. 전치행렬이므로 행과 열을 바꿔야함
    //전처리 검사
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            matrix_t[i][j]=matrix[j][i]; 
            /* 매개변수에 row에 col을, col에 row를 넣었으므로 
            matrix_t는 [i][j]그대로 가지만 matrix는 [j][i] 반대로 담아주어
            t행렬의 행에 a행렬(matrix)의 열 값을 담음*/
        }
    }

    //후처리 검사 - 행렬과 행렬의 전치행렬이 NULL 값을 가지는 지 검사
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int **matrix_at=create_matrix(row,col); //행렬 a*t를 저장할 행렬 생성

    //전처리 검사
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j,k; //i는 _a의 행, j는 _t의 행을 담당
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            int temp=0;
            for(k=0;k<col;k++)
            {
                temp+=matrix_a[i][k]*matrix_t[k][j];
                /*행렬의 곱셈 : a행렬의 첫번째 행과, t행렬의 첫번째 열을 각 자리에 맞게 곱하고 그것들을 더함,
                그리고 새롭게 생성한 matrix_at의 [i][j]자리에 그 값을 저장,
                a행렬의 첫 행 고정, t행렬에 열의 개수만큼 열을 옮겨가며 곱하고 저장을 수행하고,
                그렇게 행과 열의 곱셈을 행과 열을 적절히 옮겨가며 수행한다.*/
            }
            matrix_at[i][j]=temp; //_at행렬에 곱셈을 더한 총 값 저장
        }
    }

    //후처리 검사 - _t와 _at행렬이 NULL값을 가지는 지 검사
    if (matrix_t == NULL || matrix_at ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    print_matrix(matrix_at,row,col); //matrix_at 행렬 출력
    free_matrix(matrix_at,row,col); //matrix_at 행렬 동적할당 해제
    return 1;
}
