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
    printf("[----- [������]  [2021041075] -----]\n");

    int row, col;
    srand(time(NULL)); //������ �ߺ��� ���� ����

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); //��, �� �� �Է¹ޱ�
    /*��� a, b, a_t(a�� ��ġ���) ����*/
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //a, b ����� NULL�� ������ �� �˻�

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
        scanf(" %c", &command); //�޴� ���� ���ĺ� �ޱ�

        switch(command) {
        case 'z': case 'Z': //��� 0~19 ������ ���� ����
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': //��� ���
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //a, b����� ���� ����
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //a, b����� ���� ����
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': //��ġ��� matrix_t ���ϱ�
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //�Լ� �������� col�� ��ġ��� t�� row��, row�� col�� ����� ���� (�ڼ��� �� �Ʒ� ����)
            print_matrix(matrix_a_t, col, row); //��ġ��� ���
            break;
        case 'm': case 'M': //a, t����� ���� ����
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': //�����Ҵ��� �����ϴ� ���ÿ� do while���� ������
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: //���������� command ���� �ԷµǾ��� ��� ���
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); //q�� Q�� ������ do while���� ����

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    //��ó�� �˻�
	if (row <= 0 || col <= 0) { //�� �Ǵ� ���� 0�̰ų� 0���� ������ �˻�
		printf("Check the size of row and col!\n");
		return NULL;
	}

    int **x, i;
    x=(int**)malloc(sizeof(int*)*row); //�ּҸ� �����ϴ� �����Ҵ�
    // MALLOC(x,row*sizeof(*x));

    for(i=0;i<row;i++)
    {
        x[i]=(int*)malloc(sizeof(int)*col);  //���� �����ϴ� �����Ҵ�
        // MALLOC(x[i],col*sizeof(**x));
    }

    //��ó�� �˻�
	if (x == NULL) { //����� NULL ���� �������� �˻�
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

    return x; //matrix_(?)�� �����ؾ� �ϹǷ� ��� x�� ��ȯ������ ����
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    //��ó�� �˻�
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%3d ",matrix[i][j]); //��� ���
        }
        printf("\n"); //row(��) �ϳ� ��� �� ����
    }
    printf("\n");

    //��ó�� �˻�
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return;
	}
    return ;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    //��ó�� �˻�
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i;
    for(i=0;i<row;i++)
    {
        free(matrix[i]); //���ΰ��� ����
    }
    free(matrix); //���ΰ��� ����
    // ���� ������ �Ҵ�� �ݴ�� ���� ������ ���� ������ ����, ���� ������ �ش��ϴ� �޸� ����

    return 1;
    //�����Ҵ��� �����ϴ� �Լ��̹Ƿ� ��ó�� �˻�� ���� �ʴ´�.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //Initialize Matrix
{
    //��ó�� �˻�
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            matrix[i][j]=rand()%20; //0~19������ ������ ��Ŀ� ����
        }
    }

    //��ó�� �˻�
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** add_matrix=create_matrix(row,col); //��� a,b�� ���� ���� �������� add_matrix�� �����Ѵ�.

    //��ó�� �˻�
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            add_matrix[i][j]=matrix_a[i][j]+matrix_b[i][j]; //�迭���� ���Ѵ�
        }
    }

    //��ó�� �˻� - ��� _a,_b,add_ �� ����� NULL���� ������ �� �˻�
	if (matrix_a == NULL || matrix_b == NULL || add_matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    print_matrix(add_matrix,row,col); //add_matrix ��� ���
    free_matrix(add_matrix,row,col); //add_matrix ��� �����Ҵ� ����
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int ** sub_matrix=create_matrix(row,col); //��� a,b�� �� ���� ������ sub_matrix ����

    //��ó�� �˻�
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            sub_matrix[i][j]=matrix_a[i][j]-matrix_b[i][j]; //�迭���� ����.
        }
    }

    //��ó�� �˻� - ��� _a,_b,sub_ �� ����� NULL���� ������ �� �˻�
	if (matrix_a == NULL || matrix_b == NULL || sub_matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(sub_matrix,row,col); //sub_matrix ��� ���
    free_matrix(sub_matrix,row,col); //sub_matrix ��� �����Ҵ� ����
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{ //�Ű����� row�� col��, col�� row�� ����. ��ġ����̹Ƿ� ��� ���� �ٲ����
    //��ó�� �˻�
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
            /* �Ű������� row�� col��, col�� row�� �־����Ƿ� 
            matrix_t�� [i][j]�״�� ������ matrix�� [j][i] �ݴ�� ����־�
            t����� �࿡ a���(matrix)�� �� ���� ����*/
        }
    }

    //��ó�� �˻� - ��İ� ����� ��ġ����� NULL ���� ������ �� �˻�
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int **matrix_at=create_matrix(row,col); //��� a*t�� ������ ��� ����

    //��ó�� �˻�
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int i,j,k; //i�� _a�� ��, j�� _t�� ���� ���
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            int temp=0;
            for(k=0;k<col;k++)
            {
                temp+=matrix_a[i][k]*matrix_t[k][j];
                /*����� ���� : a����� ù��° ���, t����� ù��° ���� �� �ڸ��� �°� ���ϰ� �װ͵��� ����,
                �׸��� ���Ӱ� ������ matrix_at�� [i][j]�ڸ��� �� ���� ����,
                a����� ù �� ����, t��Ŀ� ���� ������ŭ ���� �Űܰ��� ���ϰ� ������ �����ϰ�,
                �׷��� ��� ���� ������ ��� ���� ������ �Űܰ��� �����Ѵ�.*/
            }
            matrix_at[i][j]=temp; //_at��Ŀ� ������ ���� �� �� ����
        }
    }

    //��ó�� �˻� - _t�� _at����� NULL���� ������ �� �˻�
    if (matrix_t == NULL || matrix_at ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    print_matrix(matrix_at,row,col); //matrix_at ��� ���
    free_matrix(matrix_at,row,col); //matrix_at ��� �����Ҵ� ����
    return 1;
}
