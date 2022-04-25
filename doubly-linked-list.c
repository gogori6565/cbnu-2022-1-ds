#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */

typedef struct Node {
	int key;            //�����͸� ������ ��� key
	struct Node* llink; //���� ��带 ����ų ��ũ
	struct Node* rlink; //������ ��带 ����ų ��ũ
} listNode;

typedef struct Head {
	struct Node* first; //headNode�� Node�� first ���
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
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
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode); //headnode�� ���� �޸� �Ҵ�(headnode�� �ּ� ����), headnode�� �ּҸ� �����Ͽ����Ƿ� ��ȯ��x
			break;
		case 'p': case 'P':
			printList(headnode); //���Ḯ��Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //Node�߰�
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //Node����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //�������� ��� �߰�
			break;
		case 'e': case 'E':
			deleteLast(headnode); //������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //ù��°�� ��� �߰�
			break;
		case 't': case 'T':
			deleteFirst(headnode); //ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode); //��� ��������
			break;
		case 'q': case 'Q':
			freeList(headnode); //��� ����
			break;
		default: //�߸� �Է��Ͽ��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

//���������͸� �Ű������� ���� - *h�� headNode�� �ּ�, �� headNode�� �ּҸ� �����ϴ� ������(*h)�� �ּҸ� �ޱ� ���� ���������͸� ��
int initialize(headNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

    //headNode�� NULL�̸�(OR �޸𸮸� ��� ����������)
	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode)); //h�� ����Ű�� ���� �޸� �Ҵ�
	(*h)->first = NULL;
	return 1; //headnode�� �ּҷ� �޾� �Ѱ��ֹǷ� return �����൵ ��
}

//���������͸� �Ű������� ���� - �޸𸮸� ������ �Ŵϱ� ������ �޸𸮿� �����ϸ��, ���������ͷ� �ص� ����
int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {//p�� NULL�� �� ����
		prev = p;     //prev�� p�ְ�
		p = p->rlink; //p�� ������ ���� �ű�
		free(prev);   //prev ����
	}
	free(h); //headNode�� ����
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
		p = p->rlink;                      //���� link�� ����Ű���� ��
		i++;
	}

	printf("  items = %d\n", i); //��� ���� ���
}

/**
 * list�� key�� ���� ����ϳ��� �߰� (�������� �߰�)
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� node ����
	node->key = key;    //node->key = �Է¹��� key
	node->rlink = NULL; //������ ��带 ����Ű�� ��ũ = NULL
	node->llink = NULL; //���� ��带 ����Ű�� ��ũ = NULL

	if (h->first == NULL) //���� ����Ʈ �̸�
	{
		h->first = node; //���θ��� node�� ù���� ����
		return 0;
	}

	listNode* n = h->first;   //������ n�� ù���� ����
	while(n->rlink != NULL) { //n�� ��������尡 �ƴϸ�
		n = n->rlink; //n�� �������� �ű� (�������� �߰��ҰŶ� n�� ���������� �ű�)
	}
    //n�� ������ �����
	n->rlink = node; //n�� ������ ���� node�� ����Ŵ
	node->llink = n; //node�� ���� ���� n�� ����Ŵ
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
	if(n->rlink == NULL) { //������ n(ù���)�� ����Ű�� ������ ��尡 NULL�� ��� (first node == last node)
		h->first = NULL; //ù��� NULL
		free(n); //n��� ����
		return 0;
	}
	
	/* ������ ������ �̵� */
	while(n->rlink != NULL) {
		trail = n; //������带 n���� ����
		n = n->rlink; //n���� ���� ���� �ű� (������ ������ �̵�)
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL; //������尡 ����Ű�� ������ ���(n)�� NULL��
	free(n); //�׸��� n��� ����

	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� node ����
	node->key = key; //node�� ����Ű�� key�� �Է� key ����
	node->rlink = node->llink = NULL; //node�� ������, ���� ��� NULL

	if(h->first == NULL) //ù��尡 NULL�� ���
	{
		h->first = node; //node�� ù���� ����
		return 1;
	}

	node->rlink = h->first; //node�� ����Ű�� ������ ��� => ���� ù���
	node->llink = NULL;     //node�� ����Ű�� ���� ���� NULL (node�� ó���� �߰��� �Ŵϱ�!)

	listNode *p = h->first; //ù���� ��� p�� �ְ�
	p->llink = node; //p�� ���� ��带 node�� �����ϰ�
	h->first = node; //node�� ù���� ����

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
	listNode* n = h->first; //������ n�� ù��� �ֱ�
	h->first = n->rlink; //n�� ����Ű�� ������ ��带 ù���� ����

	free(n); //������ n(�����Ϸ��ߴ� ù���)�� ���� 

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
		trail = middle; //������� trail = middle
		middle = n;     //middle�� ������ n
		n = n->rlink;   //n�� n�� ����Ű�� ������ ���� �Ű���
		middle->rlink = trail; //(�Ʊ��� ������ n��)middle�� ����Ű�� ������ ��尡 ���� ���(���� ��ġ)
		middle->llink = n;     //middle�� ����Ű�� ���� ��尡 n
	}

	h->first = middle; //middle(���� ����Ʈ���� ���������)�� ù���� ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� node ����
	node->key = key; //���θ��� node�� (�Է¹���)�����Ͱ� �Է�
	node->llink = node->rlink = NULL; //node�� ����Ű�� ����, ������ ��� NULL

	if (h->first == NULL) //���鸮��Ʈ�̸�
	{
		h->first = node; //ù ��带 ������ ���θ��� node�� ����
		return 0;
	}

	listNode* n = h->first; //������ n�� ù���� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) { //n�� ���� key�� �Է¹��� key���� ũ�ų� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {  //n�� ù�����
				insertFirst(h, key); //insertFirst �Լ� ȣ���Ͽ� ù��忡 �ش� key�� ���� ��� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; //node�� ����Ű�� ������ ��带 n���� ����
				node->llink = n->llink; //node�� ����Ű�� ���� ��带 n�� ����Ű�� ���ʳ��� ����
				n->llink->rlink = node; //n�� ����Ű�� ���ʳ��(���� node�� ����Ű�� ���ʳ��)�� ������ ��带 ����Ű�� ��ũ�� node�� ����Ŵ
				//(��, ���� n�� ����Ű�� ���� ���� ���� n���̿� node�� �� �� ����)
			}
			return 0;
		}

		n = n->rlink; //n�� ���� key�� �Է¹��� key���� �۴ٸ� ��� ������ ���� �ű�鼭 �ƴ� ��� ã��
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key); //insertLast �Լ� ȣ���� �������� ����
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //���� ����Ʈ�̸�
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; //������ n�� ù���� ����

	while(n != NULL) {
		if(n->key == key) { //������ n�� key�� �Է�key�� ���� ���
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); //deleteFirst �Լ� ȣ���ؼ� ù��° ��� ����
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h); //deleteLast �Լ� ȣ���ؼ� ������ ��� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; //���� �ڽ�(n)�� ����Ű�� ���� ����� �����ʸ�ũ�� �ڽ�(n)�� ����Ű�� ������ ��带 ����Ű���� ��
				n->rlink->llink = n->llink; //���� �ڽ�(n)�� ����Ű�� ������ ����� ���ʸ�ũ�� �ڽ�(n)�� ����Ű�� ���� ��带 ����Ű���� ��
				free(n); //�׸��� n��� ����
			}
			return 1;
		}

		n = n->rlink; //n�� �������� �ű�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}