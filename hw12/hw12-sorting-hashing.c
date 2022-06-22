#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	printf("[----- [이주현]  [2021041075] -----]\n");
	
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
		case 'z': case 'Z': //배열 생성
			initialize(&array);
			break;
		case 'q': case 'Q': //메모리 해제 및 종료
			freeArray(array);
			break;
		case 's': case 'S': //선택 정렬
			selectionSort(array);
			break;
		case 'i': case 'I': //삽입 정렬
			insertionSort(array);
			break;
		case 'b': case 'B': //버블 정렬
			bubbleSort(array);
			break;
		case 'l': case 'L': //셸 정렬
			shellSort(array);
			break;
		case 'k': case 'K': //퀵 정렬
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H': //해싱
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E': //찾는 key값의 hash table내의 위치
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': //배열 출력
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
	int *temp = NULL; //메모리 할당할 포인터 선언

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; //NULL이 아닌 경우 할당된 array를 temp에 저장

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; //0~MAX_ARRAY_SIZE-1 만큼의 랜덤값 저장

	return 0;
}

//배열 동적할당 해제
int freeArray(int *a)
{
	if(a != NULL) //a가 NULL이 아니라면 (메모리가 할당되어 있다면)
		free(a);  //a 메모리 해제
	return 0;
}

//배열 출력
void printArray(int *a)
{
	//a가 NULL이면 아무것도 출력하지 않음
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	//NULL이 아니면 출력
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

//선택 정렬
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
		minindex = i; //최소값의 배열인덱스를 현재 i값으로 초기 설정
		min = a[i];   //최소값을 a배열의 i번째 인덱스로 초기 설정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //i번째 인덱스부터 정렬하도록 (for문이 반복되면서 이미 정렬된 앞쪽 인덱스를 건드리지 않도록)
		{
			if (min > a[j]) //min보다 a[j]가 더 작을 경우
			{
				min = a[j]; //a[j]를 최소값으로 저장
				minindex = j; //최소값인덱스를 j로 저장
			}
		} //이 과정을 MAX_ARRAY_SIZE만큼 끝까지 돌리면 min, minindex에 검사한 배열의 최소값과 최소값의 인덱스가 저장될 것임
		a[minindex] = a[i]; //최소값이 들어있는 위치에 현재 i번째 인덱스를 저장하고,
		a[i] = min;			//i번째 위치에 최소값을 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

//삽입정렬 : 정렬되어있는 부분집합에 새로운 원소의 위치를 찾아 삽입
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //인덱스 1부터 배열 최대 사이즈 까지 반복
	{
		t = a[i]; //i번째 배열값을 t에 저장
		j = i;    //i를 j 변수에 저장
		while (a[j-1] > t && j > 0)  //j의 앞부분 원소가 t값보다 크고 (and) j가 0보다 크다면
		{
			a[j] = a[j-1]; //j번째에 j의 앞부분 원소를 저장
			j--; //j를 1감소 -> 0이 되면 while문을 멈춤 (더 비교할 것도 없이 배열의 맨 앞임)
		}
		//배열의 맨 앞까지 도달했거나, 앞부분의 원소보다 크면
		a[j] = t; //해당 t값을 j번째 배열에 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//버블정렬 : 인접한 배열의 요소를 비교-교환하여 전체적으로 대충 정렬을 하면서 최대값을 배열의 제일 뒤로 보내는 것을 반복
//즉, 배열의 뒤쪽부터 최대값이 차례로 쌓여 정렬되는 방식
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = MAX_ARRAY_SIZE-1; i > 0; i--) //버블정렬은 뒤에서 부터 정렬되므로 정렬이 된 뒷부분은 비교하지 않도록 i를 뒤에서 부터 1씩 낮추는 코드
	{
		for (j = 0; j < i; j++) //이미 배열이된 뒷부분은 비교하지 않도록 j<i
		{
			if (a[j] > a[j+1]) //j위치 원소가 뒷부분 원소값보다 크다면
			{
				t = a[j];		//t에 j인덱스 원소값 저장
				a[j] = a[j+1]; 	//j인덱스의 원소 위치에 뒷부분 원소값 저장
				a[j+1] = t;		//뒷부분 원소 위치에 t값 저장
			} //인접한 배열 요소를 비교해 더 큰 값을 맨 뒤로 미는 방식 (뒤에서 부터 최대값이 쌓여 정렬되는 방식)
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//셸 정렬 : Insertion sort의 문제점을 보완한 정렬 방법
//어느정도 h만큼 떨어진 요소를 삽입정렬하다가 인접한 요소를 비교하는 삽입정렬을 사용하면 훨씬 효율적!
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	//h=MAX_ARRAY_SIZE/2 : 최대배열크기의 반 에서 시작해 h가 0보다 클 때까지 반복(0보다 같거나 작으면 끝), h를 (/2) 반절씩 줄이며 반복
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //j번째 배열 요소를 v에 저장
				k = j;	  //j를 k에 저장
				while (k > h-1 && a[k-h] > v) //k가 h-1보다 크고 (and) k-h번째의 배열요소가 v보다 크다면
				{
					a[k] = a[k-h]; //k-h번째 배열 요소를 k번째 배열 요소로 저장
					k -= h;		   //k를 k-h로 변경
				}
				a[k] = v; //k번째 배열요소에 v값 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//퀵 정렬 : 정렬할 전체 원소에 대해 정렬을 수행하지 않고, 기준 값을 중심으로 왼쪽, 오른쪽 부분잡합으로 분할하여 정렬
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) //n이 1보다 크다면
	{
		v = a[n-1]; //v는 n-1번째 배열의 원소 (pivot)
		i = -1;		//i는 -1
		j = n - 1;  //j는 n-1

		while(1)
		{
			while(a[++i] < v); //1 증가한 i번째 배열 원소가 v보다 작다면 반복 -> 즉, v보다 큰 배열원소의 i번째 인덱스를 찾는다
			while(a[--j] > v); //1 감소한 j번쨰 배열 원소가 v보다 크다면 반복 -> 즉, v보다 작은 배열원소의 j번째 인덱스를 찾는다

			if (i >= j) break; //i가 j보다 크거나 같다면 반복 멈춤
			t = a[i];	 //i번째 배열원소를 t에 저장
			a[i] = a[j]; //i번째에 j번째 배열원소 저장
			a[j] = t;	 //j번째에 t를 저장
		}
		t = a[i];		//i번째 배열원소를 t에 저장
		a[i] = a[n-1];	//i번째에 pivot 배열원소 저장
		a[n-1] = t;		//pivot 위치에 t를 저장

		//기준값을 중심으로 왼쪽 오른쪽 분할
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}

	return 0;
}

//해쉬값 계산 : 해시함수 - 제산함수 사용
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //제산함수, 버킷 주소의 범위 : 0~(MAX_HASH_TABLE_SIZE-1)
}


int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	//hash table -1로 초기화
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
		key = a[i]; //배열 a의 i번째 인덱스의 값을 key로 저장
		hashcode = hashCode(key); //해시값
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //버킷이 빈슬롯이라면
		{
			hashtable[hashcode] = key; //해당 hashcode의 버킷에 key 저장
		} else 	{ //버킷이 빈슬롯이 아니라면 (충돌발생)

			index = hashcode; //hashcode를 index 변수에 저장

			while(hashtable[index] != -1) //빈슬롯 버킷이 나올 때까지 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //인덱스를 1씩 늘려서 key를 넣을 빈 슬롯 버킷을 찾음
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //찾은 빈슬롯 버킷에 key저장
		}
	}

	return 0;
}

//사용자가 찾는 key값이 hash table의 어느 index에 위치해있는지 search
int search(int *ht, int key)
{
	int index = hashCode(key); //index 변수에 사용자로부터 입력받은 key의 hashcode 저장

	if(ht[index] == key) //hashtable에서 해당 index 위치의 값이 key와 같다면
		return index; //index 반환

	while(ht[++index] != key) //index를 한 칸씩 늘려가면서 key값이 어느 버킷에 들어있는 지 탐색 (찾으면 반복 멈춤)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; //찾은 위치의 index 반환
}



