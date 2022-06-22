#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; //����� ��
	struct node *left; //���� ����Ʈ�� (left child)
	struct node *right; //������ ����Ʈ�� (right child)
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE]; //����
int top = -1; //top -1�� �ʱ�ȭ

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE]; //ť
int front = -1; //front -1�� �ʱ�ȭ
int rear = -1; //rear -1�� �ʱ�ȭ

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

void printStack();

int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [������]  [2021041075] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //NULL�� �ƴϸ�,
		freeBST(*h); //����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //h�� ����Ű�� ���� �޸� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

//������ȸ
void recursiveInorder(Node* ptr)
{
	if(ptr) { //ptr�� NULL�� �ƴ϶��
		recursiveInorder(ptr->left); //����Լ�, ptr�� left child �Ѱ���
		printf(" [%d] ", ptr->key); //ptr�� key�� ��� 
		recursiveInorder(ptr->right); //����Լ�, ptr�� right child �Ѱ���
	}
}

/**
 * textbook: p 224
 */
/*�ݺ��� ���� ��ȸ - ������ �ʿ�� �ϴ� ��ȸ
* : ��ȸ ����� ���� ��ȸ�� ����.
*/
void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left) //left child�� �� ��忡 ���޵� ������ ���ÿ� �����Ѵ�
			push(node); //���ÿ� ����
		//�׷��� �� ��忡 �����ϸ� �ٽ� ���ÿ��� �����Ѵ� (���� �ֱٿ� ���� �ͺ���)
		node = pop(); //���ÿ��� ����

		if(!node) break; //���� �����̸� �ݺ� ����
		printf(" [%d] ", node->key); //node�� key�� ���

		node = node->right; //node�� node�� right child�� ����
	}
}

/**
 * textbook: p 225
 */
/*���� ���� Ʈ�� ��ȸ - ť�� �ʿ�� �ϴ� ��ȸ
* : ��Ʈ�� ���� �湮�� ����, ���� �ڽ�, ������ �ڽ��� �湮
* �̷��� ������� �� ������ ��带 ���� ���ʺ��� �����ʱ��� ���ʷ� �湮�Ѵ�
*/
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); //root(ptr)�� ť�� ����

	for(;;)
	{
		ptr = deQueue(); //���� ť���� ��ȯ�� ��� ptr�� ���� (deQueue�� ��ȯ Ÿ���� Node*)
		if(ptr) { //ptr�� NULL�� �ƴ϶��
			printf(" [%d] ", ptr->key); //ptr�� key�� ��� (������ ����� ������ ���)

			if(ptr->left) //ptr�� left child�� NULL�� �ƴ϶��
				enQueue(ptr->left); //ptr�� left child ť�� ����
			if(ptr->right) //ptr�� right child�� NULL�� �ƴ϶��
				enQueue(ptr->right); //ptr�� right child ť�� ����
		}
		else //ptr�� NULL�̸�
			break; //�ݺ� ��!

	}
}

/*����*/
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //���ο� ���
	newNode->key = key; //���ο� ����� key�� �Է¹��� key
	newNode->left = NULL; //���ο� ����� left child�� NULL
	newNode->right = NULL; //���ο� ����� right child�� NULL

	if (head->left == NULL) { //initializeBST �ϰ� ����߰��� ó���� ��,
		head->left = newNode; //head�� left child�� ���ο� node ����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr�� root

	Node* parentNode = NULL; //parentNode = NULL
	while(ptr != NULL) { //ptr�� NULL�� �ƴϸ� �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr�� key�� �Է¹��� key�� ���ٸ�

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr�� parentNode�� ����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr�� ���� key���� �Է¹��� key�� ���� �۴ٸ�
			ptr = ptr->right; //ptr�� right child�� ptr��
		else //ptr�� ���� key���� �Է¹��� key�� ���� ũ�ٸ�
			ptr = ptr->left; //ptr�� left child�� ptr�� ����
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //���� parentNode�� ptr�� NULL�� �Ǳ� �� ���� ���, parentNode�� key���� �Է¹��� key���� Ŭ ���
		parentNode->left = newNode; //newNode�� parentNode�� left child
	else //parentNode�� key���� �Է¹��� key���� ���� ���
		parentNode->right = newNode;  //newNode�� parentNode�� right child
	return 1;
}

/*����*/
int deleteNode(Node* head, int key)
{
	if (head == NULL) { //head�� NULL�̶��
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //root�� NULL�̶��
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //head�� left child�� root


	Node* parent = NULL; //parent = NULL
	Node* ptr = root; //ptr�� root

	/*ptr�� NULL�� �ƴϰ� ptr�� key���� �Է¹��� key���� �ٸ��ٸ� �ݺ�
	* ��, ptr�� NULL�� �ǰų�, ptr�� key���� �Է¹��� key���� ���� �ȴٸ� �ݺ� ����
	*/
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) { //ptr�� key���� �Է¹��� key���� �ٸ��ٸ�

			parent = ptr;	/* save the parent */
			//parent�� ptr

			if(ptr->key > key) //ptr�� key���� �Է¹��� key������ ũ�ٸ�
				ptr = ptr->left; //ptr�� ptr�� left child
			else //ptr�� key���� �Է¹��� key������ �۴ٸ�
				ptr = ptr->right; //ptr�� ptr�� right child
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //ptr�� NULL�̶��
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node : ������ ��尡 leaf node�� ���
	 */
	if(ptr->left == NULL && ptr->right == NULL) //ptr�� left�� right child�� NULL�̶��
	{
		//parent�� NULL�� �ƴ� �� 
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) //parent�� left child�� ptr�̸�
				parent->left = NULL; //parent�� left child�� NULL��
			else //parent�� right child�� ptr�̸�
				parent->right = NULL; //parent�� right child�� NULL��
		} else { //parent�� NULL�̸� (ptr�� root�ε� �Է¹��� key���� �����ؼ� ���� ���)
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; //root�� NULL(����)

		}

		free(ptr); //ptr ����
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child : ������ ��尡 ���� �ڽĳ�尡 �� ���� ���
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //ptr�� left child �� right child �� �� �ϳ��� NULL�̸� (�� �� NULL�̸� ������ �ɷ�)
	{
		Node* child; //child��� node ����
		if (ptr->left != NULL) //ptr�� left chlid�� �� �� ���� �ڽĳ���� 
			child = ptr->left; //child�� ptr�� left child
		else //ptr�� right child�� �� �� ���� �ڽĳ����
			child = ptr->right; //chlid�� ptr�� right child

		if(parent != NULL) //parent�� NULL�� �ƴϸ�
		{
			if(parent->left == ptr) //parent�� left child�� ptr�̶��
				parent->left = child; //parent�� left child�� child�̴�
			else //parent�� left child�� ptr�� �ƴ϶��
				parent->right = child; //parent right child�� child�̴�
		} else { // parent�� NULL�̶��
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //child�� root (root�� ptr�� ���ְ� child�� root�� �Ǵ� ����)
		}

		free(ptr); //ptr ����
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children : ptr��尡 �ڽ� �� �� ������ ���� ���
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //candidate�̶�� ��� ����
	parent = ptr; //parent = ptr


	candidate = ptr->right; //candidate�� ptr�� right child

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) //candidate�� left child�� �����Ѵٸ�
	{
		parent = candidate; //parent�� candidate��
		candidate = candidate->left; //candidate�� left child�� candidate���� ����
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //parent�� right child�� candidate�� ���ٸ�
		parent->right = candidate->right; //parent�� right child�� candidate�� right child�� ����
	else //�ƴ϶��
		parent->left = candidate->right; //parent�� left child�� candidate�� right child�� ����

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //candidate�� key���� ptr�� key������ ����

	free(candidate); //candidate ����
	return 1;
}

//��� ����
void freeNode(Node* ptr)
{
	if(ptr) { //ptr�� NULL�� �ƴ϶�� ����
		freeNode(ptr->left); //����Լ�, ptr�� left child ����
		freeNode(ptr->right); //����Լ�, ptr�� right child ����
		free(ptr); //ptr ����
	}
}

//����Ʈ�� ����
int freeBST(Node* head)
{

	if(head->left == head) //head�� left child�� head�� ���ٸ�
	{
		free(head); //head ����
		return 1;
	}

	Node* p = head->left; //p�� root

	freeNode(p); //p��� ����

	free(head); //head ����
	return 1;
}

Node* pop()
{
	if (top < 0) return NULL; //top�� 0���� ������ (-1�̸�) ��ȯ
	return stack[top--]; //���� top ������ stack�� ��ȯ�� �ڿ� top 1 ���ҽ�Ű��
}

void push(Node* aNode)
{
	stack[++top] = aNode; //top�� 1 ������Ų �� aNode�� stack�� ����
}

//Stack ���
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) //i�� top���� �۰ų� ������ �ݺ�
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

Node* deQueue()
{
	if (front == rear) { //front�� rear�� ���ٸ� ����
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //������ �ƴ϶��, front�� �� ĭ ������ ������
	return queue[front]; //���� front�� ť�� �ִ� ���� ��ȯ

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear�� �� ĭ ������ ������
	if (front == rear) { //front�� rear�� ���ٸ� ������
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //�������� �ʾҴٸ� ���� rear�� ť�� aNode ����
}
