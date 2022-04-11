#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //ť�� �ִ� ũ��

typedef char element; //ť ������ �ڷ����� char�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //MAX_QUEUE_SIZE 4�� ������ ������ �迭 queue
	int front, rear; //���ο� ���Ұ� ���ԵǴ� ��-rear, ���Ұ� �����Ǵ� ��-front
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
	QueueType *cQ = createQueue(); //���� ���� ť ����
	element data;

	char command; //�޴� ������ ���� �޴� ����

	printf("[----- [������]  [2021041075] -----]\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //�޴� ������ command �Է¹ޱ�

		switch(command) {
		case 'i': case 'I':
			data = getElement(); //����ڷκ��� �Է¹��� �� data�� ����
			enQueue(cQ, data); //����ڷκ��� �Է¹��� ���� data�� cQ ���� ť�� ����
			break;
		case 'd': case 'D':
			deQueue(cQ,&data); //���� ����
			break;
		case 'p': case 'P':
			printQ(cQ); //�迭 ���
			break;
		case 'b': case 'B':
			debugQ(cQ); //���� �迭�� ���� ���� front, rear�� ��ġ�� ������
			break;
		case 'q': case 'Q': //�ݺ��� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //���� ���� ���� ������ �� ��� �޼���
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� ���� ��� �ݺ��� ����


	return 1;
}

//���� ���� ť ����
QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0; //front �ʱⰪ 0
	cQ->rear = 0;  //rear �ʱⰪ 0
	return cQ;
}

//�����Ҵ� ���� ���ֱ�
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; //cQ�� NULL���� ������ �ִٸ� �Լ� ����
    free(cQ); //�ƴϸ� free�� �����Ҵ� ����
    return 1;
}

//����ڷκ��� ���� ť�� ������ element �� �Է¹ޱ�
element getElement()
{
	element item; //char�� item���� ����
	printf("Input element = ");
	scanf(" %c", &item); //����ڷκ��� element �� �Է¹ޱ�
	return item; //����ڷκ��� �Է¹��� ��(item) ��ȯ
}

//���� ť�� ���� �������� �˻�
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){ //front�� rear�� ������ ��������̹Ƿ� 1 ��ȯ
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0; //���� ���°� �ƴϸ� 0 ��ȯ
	//���� isEmpty ����� �� ������¸� �ǹ��ϴ� 1�̸� �����ϰ� �ƴ� 0�̸� �����ϵ��� �� ����
}

//���� ť�� ��ȭ �������� �˻�
int isFull(QueueType *cQ)
{
	/*���� ť�� ����� ��ȭ ���¸� ���� �����ϱ� ����
	front�� �ִ� �ڸ��� �׻� �� ĭ ��� �α�� �����Ƿ�
	rear���� �� ĭ �� ��ġ�� front�� ��ġ�� ���ٸ� ��ȭ���·� �Ǵ�*/
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");
		return 1; //��ȭ���¸� 1 ��ȯ
	}
	else return 0; //�ƴϸ� 0 ��ȯ
}

//���� ť rear�� ���� ����
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return; //cQ�� ��ȭ���¶�� �Լ� ����
	else { //�ƴ϶��
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
		/*rear���� �� ĭ �� ��ġ�� item �� �������ֱ�
		��, ���� ť�̱� ������ �׳� +1 �� ��ġ�� �ƴ϶� (rear+1)%MAX_QUEUE_SIZE�� �Ͽ� 
		������ ������ ������ �������� �ð�ݴ�������� ���鼭 �������ֱ�*/
	}
}

//���� ť�� front���� ���Ҹ� ����
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return; //���� ť cQ�� �����̸� ����
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //front�� �� ĭ ������ ����
		*item = cQ->queue[cQ->front]; //front ��ġ�� �� ���� ���� ����
		return;
	}
}

//���� ť�� ���� ���
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //front ��ġ first�� ����
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //rear ��ġ last�� ����

	printf("Circular Queue : [");

	i = first;
	while(i != last){ //first ��ġ�� ������ ���� i�� last(������)�� ���� ���� ������ �ݺ�
		printf("%3c", cQ->queue[i]); //queue �迭 ���� ���
		i = (i+1)%MAX_QUEUE_SIZE; //��ġ �� ĭ �� ������

	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ)
{
	//���� �迭�� ���� ���� front, rear�� ��ġ�� ������
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) { //���� i�� ���� front�� ��ġ�� ���ٸ� ��ġ �� ��� 
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //�ƴϸ� i��ġ�� �迭�� �� ���

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front�� rear�� ��ġ �� ���
}


