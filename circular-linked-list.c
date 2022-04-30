#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;
//���� ���� ����Ʈ�̱� ������ singly�� doublyó�� Head�� ���� ������ �ʰ�, ����嵵 llink, rllink�� ���� listNode�� ����� ����

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL; //listNode ����ü ������ headnode

	printf("[----- [������]  [2021041075] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode); //���Ḯ��Ʈ ����
			break;
		case 'p': case 'P':
			printList(headnode); //���Ḯ��Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //����� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //�Է¹��� key�� �ش��ϴ� ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //�������� ��� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode); //������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //ù��°�� ��� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); //ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode); //���� ��ġ
			break;
		case 'q': case 'Q':
			freeList(headnode); //���Ḯ��Ʈ ����
			break;
		default: //�߸��� �� �Է½�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

//���������͸� �Ű������� ���� - *h�� headNode�� �ּ�, �� headNode�� �ּҸ� �����ϴ� ������(*h)�� �ּҸ� �ޱ� ���� ���������͸� ��
int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode)); //h�� ����Ű�� ���� �޸� �Ҵ�
	(*h)->rlink = *h;  //h�� ������ ��带 ����Ű�� ��ũ�� �ڽ�����
	(*h)->llink = *h;  //h�� ���� ��带 ����Ű�� ��ũ�� �ڽ����� ���� (���� ���� ����Ʈ�̱� ����)
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	//��尡 �ϳ��� ���
	if(h->rlink == h)
	{
		free(h); //����常 ����
		return 1;
	}

	listNode* p = h->rlink; //��� p�� ù���
	listNode* prev = NULL;

	while(p != NULL && p != h) { //��� p�� NULL�� �ƴϰ�(and) ����嵵 �ƴ� ���
		prev = p;		//prev�� p�ְ�
		p = p->rlink;	//p�� ������ ���� �ű�
		free(prev);		//prev ����
	}
	free(h); //����嵵 ����
	return 0;
}

//����Ʈ ���
void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //headNode�� NULL�̸� (����Ʈ ������ �ȵ� ���))
		printf("Nothing to print....\n"); //����� �� ����
		return;
	}

	p = h->rlink; //��� p�� ù���� ����

	while(p != NULL && p != h) { //��� p�� NULL�� �ƴϰ�(and) ����嵵 �ƴ� ���
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //��� p ���������� �Ű��ָ� ���
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//headnode�� llink, headnode �ڽ�, rlink�� �� ��� (�ּ� ��µ�)

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
	//�� ��°��� ���� ���Ḯ��Ʈ�� ���ʸ�ũ, ������ ��ũ�� ���ʳ��, ������ ���� �� ����������� �� �� ����

}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; //�� ����Ʈ�̸� ����
	
	//����� ����
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;	//����尡 ���� key���� �Է¹��� key��
	node->rlink = NULL; //������ ��ũ : NULL
	node->llink = NULL; //���� ��ũ : NULL

	//��尡 ����� �ϳ��̸�
	if (h->rlink == h) /* ù ���� ���� */
	{
		h->rlink = node; //����尡 ����Ű�� ������ ��带 node
		h->llink = node; //����尡 ����Ű�� ���� ��带 node��
		node->rlink = h; //node�� ����Ű�� ������ ��带 ������
		node->llink = h; //node�� ����Ű�� ���� ��带 h�� ����
		//��, ������ node�� ������ ���θ� ����Ű�� ���� ������ ��������
	} 
	else //��尡 ���� ���̸� 
	{
		h->llink->rlink = node; //����尡 ����Ű�� ���ʳ��(����Ʈ�� ������ ���)�� ����Ű�� ������ ��带 node��
		node->llink = h->llink; //node�� ����Ű�� ���ʳ�带 ����尡 ����Ű�� ���ʳ��(����Ʈ�� ������ ���)��
		h->llink = node;		//����尡 ����Ű�� ���ʳ��(����Ʈ�� ������ ���)�� node�� (���� node�� �������̴ϱ�)
		node->rlink = h;		//��尡 ����Ű�� ������ ��带 ������ ����
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	//����Ʈ�� ��尡 ����� �ϳ����̰ų�(OR) ����尡 NULL�� ���
	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n"); //������ �� ����
		return 1;
	}

	listNode* nodetoremove = h->llink; //nodetoremove�� ù���� ����

	/* link ���� */
	nodetoremove->llink->rlink = h; //nodetoremove�� ���� ��尡 ����Ű�� ������ ��带 ù����
	h->llink = nodetoremove->llink; //h�� ����Ű�� ���ʳ��(���������)�� nodetoremove�� ����Ű�� ���� ���� ����

	free(nodetoremove); //nodetoremove ����

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	//����� ����
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink; //����尡 ����Ű�� ������ ��带 ����尡 ����Ű�� ������ ���� ����
	h->rlink->llink = node; //����尡 ����Ű�� ������ ��尡 ����Ű�� ���� ��带 node��
	node->llink = h;		//����尡 ����ų ���� ��带 ������
	h->rlink = node;		//����尡 ����Ű�� ������ ��带 ������ ����
	/*1)��尡 ����� �ϳ��϶��� h�� node�� ���θ� ������ ���� �����ϵ��� �� �� �ְ�
	* 2)��尡 ������ �� ���� node�� ó���� �߰������� ������ �� �� ��尡 ���θ� �����ϰ� �־� ���� ������ ����������.
	*/

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	//����Ʈ�� ��尡 ����� �ϳ����̰ų�(OR) ����尡 NULL�� ���
	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n"); //������ �� ����
		return 0;
	}

	listNode* nodetoremove = h->rlink; //nodetoremove�� ù���� ����

	/* link ���� */
	nodetoremove->rlink->llink = h; //nodetoremove(ù���)�� ����Ű�� �����ʳ�尡 ����Ű�� ���ʳ�带 ������
	h->rlink = nodetoremove->rlink;	//ù��带 nodetoremove(ù���)�� ����Ű�� ������ ���� ����

	free(nodetoremove); //nodetoremove ����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

	//����Ʈ�� ��尡 ����� �ϳ����̰ų�(OR) ����尡 NULL�� ���
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n"); //������ �� ����
		return 0;
	}
	listNode *n = h->rlink; //��� n�� ù���
	listNode *trail = h;	//��� trail�� �����
	listNode *middle = h; 	//��� middle�� �����

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink;
	//���� ��ġ�ϸ� h->rlink(ù���)�� ��������尡 �Ǵϱ� ��������带 h->llink�� ����Ű�� ����

	while(n != NULL && n != h){ //��� n�� NULL�� �ƴϰ�(and) ����嵵 �ƴ� ���
		trail = middle;			//trail�� middle��
		middle = n;				//middle�� n����
		n = n->rlink;			//n�� ��������
		middle->rlink = trail;	//middle�� ����Ű�� ������ ��带 trail(����)����
		middle->llink = n;		//middle�� ����Ű�� ���� ��带 n(�������)�� ����
	}

	h->rlink = middle; //������ ����� middle�� ù���� ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //�� ����Ʈ�̸� ����

	//����� ����
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //����尡 ���� key���� �Է¹��� key��
	node->llink = node->rlink = NULL; //������, ���ʳ�� ����Ű�� ��ũ : NULL 

	//��尡 �ϳ��� ���
	if (h->rlink == h)
	{
		insertFirst(h, key); //��� ó���� �߰�
		return 1;
	}

	listNode* n = h->rlink; //n�� ù���� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) { //n�� NULL�� �ƴϰ�(and) ����嵵 �ƴ� ���
		if(n->key >= key) { //n�� ����Ű�� key�� �Է� key���� ū ���
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) { //n�� ù����
				insertFirst(h, key); //ù��忡 n�߰�
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;		//����尡 ����Ű�� ������ ��带 n
				node->llink = n->llink; //����尡 ����Ű�� ���� ��带 n�� ����Ű�� ���ʳ��� ����
				n->llink->rlink = node; //n�� ����Ű�� ���� ��尡 ����Ű�� ������ ��带 node�� 
				n->llink = node;		//n�� ����Ű�� ���� ��带 node�� ����
			}
			return 0;
		}

		n = n->rlink; //n�� �������� �ű�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	//����Ʈ�� ��尡 ����� �ϳ����̰ų�(OR) ����尡 NULL�� ���
	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n"); //������ �� ����
		return 0;
	}

	listNode* n = h->rlink; //��� n�� ù���

	while(n != NULL && n != h) { //��� n�� NULL�� �ƴϰ�(and) ����嵵 �ƴ� ���
		if(n->key == key) { //n�� ����Ű�� key���� �Է¹��� key���� ���� ���
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); //ù��� ����
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h); //������ ��� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; //n�� ���� ��尡 ����Ű�� ������ ��带 n�� ������ ����
				n->rlink->llink = n->llink; //n�� ������ ��尡 ����Ű�� ���� ��带 n�� ���� ���� ����
				free(n); //n ����
			}
			return 0;
		}

		n = n->rlink; //n�� �������� �ű�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}
