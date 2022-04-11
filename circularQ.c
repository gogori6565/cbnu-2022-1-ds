#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //큐의 최대 크기

typedef char element; //큐 원소의 자료형을 char로 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //MAX_QUEUE_SIZE 4를 가지는 일차원 배열 queue
	int front, rear; //새로운 원소가 삽입되는 끝-rear, 원소가 삭제되는 끝-front
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
	QueueType *cQ = createQueue(); //공백 원형 큐 생성
	element data;

	char command; //메뉴 수행할 문자 받는 변수

	printf("[----- [이주현]  [2021041075] -----]\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //메뉴 수행할 command 입력받기

		switch(command) {
		case 'i': case 'I':
			data = getElement(); //사용자로부터 입력받은 값 data에 저장
			enQueue(cQ, data); //사용자로부터 입력받은 값인 data를 cQ 원형 큐에 삽입
			break;
		case 'd': case 'D':
			deQueue(cQ,&data); //삭제 연산
			break;
		case 'p': case 'P':
			printQ(cQ); //배열 출력
			break;
		case 'b': case 'B':
			debugQ(cQ); //현재 배열이 가진 값과 front, rear의 위치를 보여줌
			break;
		case 'q': case 'Q': //반복문 종료
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //옳지 않은 값이 들어왔을 때 경고 메세지
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 들어온 경우 반복문 종료


	return 1;
}

//공백 원형 큐 생성
QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0; //front 초기값 0
	cQ->rear = 0;  //rear 초기값 0
	return cQ;
}

//동적할당 해제 해주기
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; //cQ가 NULL값을 가지고 있다면 함수 종료
    free(cQ); //아니면 free로 동적할당 해제
    return 1;
}

//사용자로부터 원형 큐에 저장할 element 값 입력받기
element getElement()
{
	element item; //char형 item변수 선언
	printf("Input element = ");
	scanf(" %c", &item); //사용자로부터 element 값 입력받기
	return item; //사용자로부터 입력받은 값(item) 반환
}

//원형 큐가 공백 상태인지 검사
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){ //front와 rear가 같으면 공백상태이므로 1 반환
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0; //공백 상태가 아니면 0 반환
	//추후 isEmpty 사용할 때 공백상태를 의미하는 1이면 종료하고 아닌 0이면 수행하도록 할 거임
}

//원형 큐가 포화 상태인지 검사
int isFull(QueueType *cQ)
{
	/*원형 큐는 공백과 포화 상태를 쉽게 구분하기 위해
	front가 있는 자리를 항상 한 칸 비워 두기로 했으므로
	rear보다 한 칸 앞 위치와 front의 위치가 같다면 포화상태로 판단*/
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");
		return 1; //포화상태면 1 반환
	}
	else return 0; //아니면 0 반환
}

//원형 큐 rear에 원소 삽입
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return; //cQ가 포화상태라면 함수 종료
	else { //아니라면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
		/*rear보다 한 칸 앞 위치에 item 값 삽입해주기
		단, 원형 큐이기 때문에 그냥 +1 한 위치가 아니라 (rear+1)%MAX_QUEUE_SIZE로 하여 
		나머지 연산을 수행해 원형으로 시계반대방향으로 돌면서 삽입해주기*/
	}
}

//원형 큐의 front에서 원소를 삭제
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return; //원형 큐 cQ가 공백이면 종료
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //front를 한 칸 앞으로 증가
		*item = cQ->queue[cQ->front]; //front 위치의 값 삭제 연산 수행
		return;
	}
}

//원형 큐의 원소 출력
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //front 위치 first에 저장
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //rear 위치 last에 저장

	printf("Circular Queue : [");

	i = first;
	while(i != last){ //first 위치를 저장한 변수 i가 last(마지막)과 같지 않을 때까지 반복
		printf("%3c", cQ->queue[i]); //queue 배열 원소 출력
		i = (i+1)%MAX_QUEUE_SIZE; //위치 한 칸 씩 앞으로

	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ)
{
	//현재 배열이 가진 값과 front, rear의 위치를 보여줌
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) { //현재 i의 값과 front의 위치가 같다면 위치 값 출력 
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //아니면 i위치의 배열의 값 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear이 위치 값 출력
}


