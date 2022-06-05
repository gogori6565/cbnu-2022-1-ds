#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	printf("[----- [������]  [2021041075] -----]\n");
	
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': //�迭 ����
			initialize(&array);
			break;
		case 'q': case 'Q': //�޸� ���� �� ����
			freeArray(array);
			break;
		case 's': case 'S': //���� ����
			selectionSort(array);
			break;
		case 'i': case 'I': //���� ����
			insertionSort(array);
			break;
		case 'b': case 'B': //���� ����
			bubbleSort(array);
			break;
		case 'l': case 'L': //�� ����
			shellSort(array);
			break;
		case 'k': case 'K': //�� ����
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H': //�ؽ�
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E': //ã�� key���� hash table���� ��ġ
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': //�迭 ���
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL; //�޸� �Ҵ��� ������ ����

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a; //NULL�� �ƴ� ��� �Ҵ�� array�� temp�� ����

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; //0~MAX_ARRAY_SIZE-1 ��ŭ�� ������ ����

	return 0;
}

//�迭 �����Ҵ� ����
int freeArray(int *a)
{
	if(a != NULL) //a�� NULL�� �ƴ϶�� (�޸𸮰� �Ҵ�Ǿ� �ִٸ�)
		free(a);  //a �޸� ����
	return 0;
}

//�迭 ���
void printArray(int *a)
{
	//a�� NULL�̸� �ƹ��͵� ������� ����
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	//NULL�� �ƴϸ� ���
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

//���� ����
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //�ּҰ��� �迭�ε����� ���� i������ �ʱ� ����
		min = a[i];   //�ּҰ��� a�迭�� i��° �ε����� �ʱ� ����
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //i��° �ε������� �����ϵ��� (for���� �ݺ��Ǹ鼭 �̹� ���ĵ� ���� �ε����� �ǵ帮�� �ʵ���)
		{
			if (min > a[j]) //min���� a[j]�� �� ���� ���
			{
				min = a[j]; //a[j]�� �ּҰ����� ����
				minindex = j; //�ּҰ��ε����� j�� ����
			}
		} //�� ������ MAX_ARRAY_SIZE��ŭ ������ ������ min, minindex�� �˻��� �迭�� �ּҰ��� �ּҰ��� �ε����� ����� ����
		a[minindex] = a[i]; //�ּҰ��� ����ִ� ��ġ�� ���� i��° �ε����� �����ϰ�,
		a[i] = min;			//i��° ��ġ�� �ּҰ��� ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

//�������� : ���ĵǾ��ִ� �κ����տ� ���ο� ������ ��ġ�� ã�� ����
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //�ε��� 1���� �迭 �ִ� ������ ���� �ݺ�
	{
		t = a[i]; //i��° �迭���� t�� ����
		j = i;    //i�� j ������ ����
		while (a[j-1] > t && j > 0)  //j�� �պκ� ���Ұ� t������ ũ�� (and) j�� 0���� ũ�ٸ�
		{
			a[j] = a[j-1]; //j��°�� j�� �պκ� ���Ҹ� ����
			j--; //j�� 1���� -> 0�� �Ǹ� while���� ���� (�� ���� �͵� ���� �迭�� �� ����)
		}
		//�迭�� �� �ձ��� �����߰ų�, �պκ��� ���Һ��� ũ��
		a[j] = t; //�ش� t���� j��° �迭�� ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//�������� : ������ �迭�� ��Ҹ� ��-��ȯ�Ͽ� ��ü������ ���� ������ �ϸ鼭 �ִ밪�� �迭�� ���� �ڷ� ������ ���� �ݺ�
//��, �迭�� ���ʺ��� �ִ밪�� ���ʷ� �׿� ���ĵǴ� ���
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = MAX_ARRAY_SIZE-1; i > 0; i--) //���������� �ڿ��� ���� ���ĵǹǷ� ������ �� �޺κ��� ������ �ʵ��� i�� �ڿ��� ���� 1�� ���ߴ� �ڵ�
	{
		for (j = 0; j < i; j++) //�̹� �迭�̵� �޺κ��� ������ �ʵ��� j<i
		{
			if (a[j] > a[j+1]) //j��ġ ���Ұ� �޺κ� ���Ұ����� ũ�ٸ�
			{
				t = a[j];		//t�� j�ε��� ���Ұ� ����
				a[j] = a[j+1]; 	//j�ε����� ���� ��ġ�� �޺κ� ���Ұ� ����
				a[j+1] = t;		//�޺κ� ���� ��ġ�� t�� ����
			} //������ �迭 ��Ҹ� ���� �� ū ���� �� �ڷ� �̴� ��� (�ڿ��� ���� �ִ밪�� �׿� ���ĵǴ� ���)
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//�� ���� : Insertion sort�� �������� ������ ���� ���
//������� h��ŭ ������ ��Ҹ� ���������ϴٰ� ������ ��Ҹ� ���ϴ� ���������� ����ϸ� �ξ� ȿ����!
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	//h=MAX_ARRAY_SIZE/2 : �ִ�迭ũ���� �� ���� ������ h�� 0���� Ŭ ������ �ݺ�(0���� ���ų� ������ ��), h�� (/2) ������ ���̸� �ݺ�
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //j��° �迭 ��Ҹ� v�� ����
				k = j;	  //j�� k�� ����
				while (k > h-1 && a[k-h] > v) //k�� h-1���� ũ�� (and) k-h��°�� �迭��Ұ� v���� ũ�ٸ�
				{
					a[k] = a[k-h]; //k-h��° �迭 ��Ҹ� k��° �迭 ��ҷ� ����
					k -= h;		   //k�� k-h�� ����
				}
				a[k] = v; //k��° �迭��ҿ� v�� ����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//�� ���� : ������ ��ü ���ҿ� ���� ������ �������� �ʰ�, ���� ���� �߽����� ����, ������ �κ��������� �����Ͽ� ����
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) //n�� 1���� ũ�ٸ�
	{
		v = a[n-1]; //v�� n-1��° �迭�� ���� (pivot)
		i = -1;		//i�� -1
		j = n - 1;  //j�� n-1

		while(1)
		{
			while(a[++i] < v); //1 ������ i��° �迭 ���Ұ� v���� �۴ٸ� �ݺ� -> ��, v���� ū �迭������ i��° �ε����� ã�´�
			while(a[--j] > v); //1 ������ j���� �迭 ���Ұ� v���� ũ�ٸ� �ݺ� -> ��, v���� ���� �迭������ j��° �ε����� ã�´�

			if (i >= j) break; //i�� j���� ũ�ų� ���ٸ� �ݺ� ����
			t = a[i];	 //i��° �迭���Ҹ� t�� ����
			a[i] = a[j]; //i��°�� j��° �迭���� ����
			a[j] = t;	 //j��°�� t�� ����
		}
		t = a[i];		//i��° �迭���Ҹ� t�� ����
		a[i] = a[n-1];	//i��°�� pivot �迭���� ����
		a[n-1] = t;		//pivot ��ġ�� t�� ����

		//���ذ��� �߽����� ���� ������ ����
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}

	return 0;
}

//�ؽ��� ��� : �ؽ��Լ� - �����Լ� ���
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //�����Լ�, ��Ŷ �ּ��� ���� : 0~(MAX_HASH_TABLE_SIZE-1)
}


int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	//hash table -1�� �ʱ�ȭ
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; //�迭 a�� i��° �ε����� ���� key�� ����
		hashcode = hashCode(key); //�ؽð�
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //��Ŷ�� �󽽷��̶��
		{
			hashtable[hashcode] = key; //�ش� hashcode�� ��Ŷ�� key ����
		} else 	{ //��Ŷ�� �󽽷��� �ƴ϶�� (�浹�߻�)

			index = hashcode; //hashcode�� index ������ ����

			while(hashtable[index] != -1) //�󽽷� ��Ŷ�� ���� ������ �ݺ�
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //�ε����� 1�� �÷��� key�� ���� �� ���� ��Ŷ�� ã��
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //ã�� �󽽷� ��Ŷ�� key����
		}
	}

	return 0;
}

//����ڰ� ã�� key���� hash table�� ��� index�� ��ġ���ִ��� search
int search(int *ht, int key)
{
	int index = hashCode(key); //index ������ ����ڷκ��� �Է¹��� key�� hashcode ����

	if(ht[index] == key) //hashtable���� �ش� index ��ġ�� ���� key�� ���ٸ�
		return index; //index ��ȯ

	while(ht[++index] != key) //index�� �� ĭ�� �÷����鼭 key���� ��� ��Ŷ�� ����ִ� �� Ž�� (ã���� �ݺ� ����)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; //ã�� ��ġ�� index ��ȯ
}



