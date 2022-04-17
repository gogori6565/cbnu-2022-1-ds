#include<stdio.h>
#include<stdlib.h> //malloc(), free()

/* �ʿ��� ������� �߰� */

typedef struct Node {  //���Ḯ��Ʈ�� Node ����ü
	int key;		   //�����͸� ������ ��� key
	struct Node* link; //���� ����� �ּҸ� ������ ������ link
} listNode; //����ü ���� listNode

typedef struct Head {
	struct Node* first; //headNode�� Node�� first ���
}headNode; //headNode�� ���� ����ü ����


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

    printf("[----- [������]  [2021041075] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); //headnode�� ���� �޸� �Ҵ�
			break;
		case 'p': case 'P':
			printList(headnode); //���Ḯ��Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); 		   //key �Է¹ޱ�
			insertNode(headnode, key); //��� ����(�Է¹��� key���� ū���� ������ ��� �ٷ� �տ�)
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);		   //key �Է¹ޱ�
			deleteNode(headnode, key); //��� ����(�Է¹��� key�� �ش��ϴ� ���)
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);		   //key �Է¹ޱ�
			insertLast(headnode, key); //�������� ��� �Է�
			break;
		case 'e': case 'E':
			deleteLast(headnode);	   //������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);		    //key �Է¹ޱ�
			insertFirst(headnode, key); //ù��°�� ��� �Է�
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode);		//���Ḯ��Ʈ �������� ���ġ
			break;
		case 'q': case 'Q':
			freeList(headnode); //�޸� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�߸� �Է� �޾��� ���
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	//headNode�� NULL�̸�(OR �޸𸮸� ��� ����������)
	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
		/*���Ḯ��Ʈ�� �Ϲ������� ��
		* p�� prev�� ���� �ʰ� �׳� free ���ѹ����� �� ���� ������ ������ �� ���� ������
		* ���� p�� prev�� �ְ�, p�� ���� link�� ����Ű�� ���� �̵���Ų �� prev�� �����ϸ�
		* ���������� ����Ʈ�� ��� ������ų �� ���� p�� NULL�� �� ����.
		*/
	}
	free(h); //headNode�� ����
	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //��� �����Ҵ�
	node->key = key;   //���θ��� node�� (�Է¹���)�����Ͱ� �Է�
	node->link = NULL; //�ϴ� link�� NULL�� ����Ű����

	if (h->first == NULL) //���鸮��Ʈ�̸�
	{
		h->first = node; //ù ��尡 ������ ���θ��� node�� ����
		return 0;
	}

	//n�� ������, trail�� ������� ����
	listNode* n = h->first;     //n�� ù���
	listNode* trail = h->first; //trail(previous)�� ù���
	//==> �̰� ����? : ù��� ���� �˻������ key�� ũ�� ������ �� �Է�����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) { //n�� ���� key�� �Է¹��� key���� ũ�ų� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { //n�� ù�����
				h->first = node; //ù ��带 node�� �ϰ�
				node->link = n;  //node�� (ù��忴��)n�� ����Ű���� ��
				//==> �׷��� �� ���� key�� ���� node�� ū���� ���� n ���� ������ �� �� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->link = n;		//node�� ����Ű�� link�� n		
				trail->link = node; //trail(����)�� ����Ű�� link�� node
			}
			return 0;
		}

		//**trail�� ���� n���� �����ؾ���. n���� �ϸ� �����带 trail�̶� ���� ����Ű�� �� ��带 ������ ���̴ϱ�**
		trail = n;   //trail(����)�� n
		n = n->link; //n�� ���� ���� �Űܰ�
	}

	/* ������ ������ ã�� ���� ���(�ڸ� ã���� while�ȿ��� return 0 ��) , �������� ���� */
	//��, ������ ������ �Է¹��� key�� ���� ��� ����� Ű���� �� Ŀ!
	trail->link = node; //trail(����)��尡 �������� node�� ����Ŵ
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰� (�������� �߰�)
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� node ����
	node->key = key;   //node->key = �Է¹��� key
	node->link = NULL; //node->link = NULL (���� �� ����Ű�� ���� �ʾ�)

	if (h->first == NULL) //���� ����Ʈ �̸�
	{
		h->first = node; //ù��带 node�� ����
		return 0;
	}

	listNode* n = h->first;  //������ n�� ù���� ����
	while(n->link != NULL) { //n�� ��������尡 �ƴϸ�
		n = n->link; //n�� �������� �ű� (�������� �߰��ҰŶ� ���������� �ű�� ����)
	}
	//n->link == NULL : ������ n�� ����������̸�
	n->link = node; //���������� node�� ����
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� node ����
	node->key = key; //node�� ����Ű�� key�� �Է� key ����

	//node�� ����Ű�� ���� link�� ���� ù���� �ְ� node�� ù���� �����ϸ� ó���� �߰� ����
	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //���� ����Ʈ�̸�
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) { //������ n�� key�� �Է�key�� ���� ���
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { //n�� ù����� ���
				h->first = n->link; //n�� ����Ű�� ��带 ù���� ����
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link; //n��尡 ����Ű�� ��带 ������尡 ����Ű�� ������ ���� (n��尡 ����Ű�� ��带 �� ������)
			}
			free(n); //n��� ����
			return 0;
		}

		trail = n;	 //������� n����
		n = n->link; //n�� ����Ű�� ��带 n���� ����
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //���� ����Ʈ�̸�
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //������ n�� ù���� ����
	listNode* trail = NULL; //������Ʈ trail�� NULL

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) { //������ while�� �������� �ʰ� ù��� �������ڸ��� �˻��ϴϱ�! first node==last node�� ��� ó��
		h->first = NULL; //ù��� NULL
		free(n); //n��� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) {
		trail = n;	 //������带 n���� ����
		n = n->link; //n���� ���� ���� �ű� (������ ������ ��)
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL;
	free(n); //n��� ����

	return 0;
}
/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //���� ����Ʈ�̸�
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //������ n�� ù���� ����

	//n�� ����Ű�� ���� ��带 ù���� �����ϰ� n��� �����ϸ� ù��° ��常 ���� ����
	h->first = n->link;
	free(n);

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //���� ����Ʈ�� ���
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;  //������ n�� ù���� ����
	listNode *trail = NULL;  //������� trail�� NULL
	listNode *middle = NULL; //middle�� NULL

	while(n != NULL){
		trail = middle; 	  //������� trail = middle
		middle = n;     	  //middle�� ������ n
		n = n->link;    	  //n�� ���� ���� �Ű���
		middle->link = trail; //(�Ʊ� ������ n�� ����)middle�� ����Ű�� ���� ��尡 trail (�������� ����Ű�� ����)
		//+) �̰� ó���̸� trail���� NULL�� ��������ϱ� ù��尡 NULL�� ����Ű�� ������ ��尡 �� �� ����
	}

	h->first = middle; //middle(���� ����Ʈ���� ���������)�� ù���� ����

	return 0;
}

//���Ḯ��Ʈ ���
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //���鸮��Ʈ���
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p�� ù��° ���

	while(p != NULL) { //����� ���� ���� ������
		printf("[ [%d]=%d ] ", i, p->key); //������ ���
		p = p->link; 					   //���� link�� ����Ű���� ��
		i++;
	}

	printf("  items = %d\n", i); //����� ���� ���
}

