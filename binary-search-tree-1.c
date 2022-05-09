#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; //����� ��
	struct node *left;  //���� ����Ʈ�� (left child)
	struct node *right; //������ ����Ʈ�� (right child)
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	//head�� ptr ��� ���� (�Ѵ� NULL�� �ʱ�ȭ)
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
    
    printf("[----- [������]  [2021041075] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); //����Ʈ�� ����
			break;
		case 'q': case 'Q':
			freeBST(head); //����Ʈ�� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //�Է¹��� key�� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); //�Է¹��� key���� �ش��ϴ� ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); //�Է¹��� key���� ��ġ�� ��带 �ݺ������� �Űܰ��� ã�� �۾����� ã��
			if(ptr != NULL) //ptr�� NULL�� �ƴ϶��
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� key���� ���� ptr�� �ּҿ��� ã������ ���
			else //ptr�� NULL�̶��
				printf("\n Cannot find the node [%d]\n", key); //ã�� �� ����
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); //�Է¹��� key���� ��ġ�� ��͸� ����Ͽ� ã��
			if(ptr != NULL) //ptr�� NULL�� �ƴ϶��
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� key���� ���� ptr�� �ּҿ��� ã������ ���
			else //ptr�� NULL�̶��
				printf("\n Cannot find the node [%d]\n", key); //ã�� �� ����
			break;
		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}

/*������ȸ(LVR)
* left child -> node -> right child ������ ��ȸ�Ѵ�.
*/
void inorderTraversal(Node* ptr)
{
	if(ptr) { //NULL�� �ƴϸ� ���� - NULL�϶� ����
		inorderTraversal(ptr->left);  //���ȣ��, ptr�� left child �ѱ� (L)
		printf(" [%d] ", ptr->key);   //ptr�� key ��� (V)
		inorderTraversal(ptr->right); //���ȣ��, ptr�� right child �ѱ� (R)
	}
}

/*������ȸ(VLR)
* node -> left child -> right child ������ ��ȸ�Ѵ�.
*/
void preorderTraversal(Node* ptr)
{
	if(ptr) { //NULL�� �ƴϸ� ���� - NULL�϶� ����
		printf(" [%d] ", ptr->key);		//ptr�� key ���(V)
		preorderTraversal(ptr->left); 	//���ȣ��, ptr�� left child �ѱ� (L)
		preorderTraversal(ptr->right);	//���ȣ��, ptr�� right child �ѱ� (R)
	}
}

/*������ȸ(LRV)
* left child -> right child -> node ������ ��ȸ�Ѵ�.
*/
void postorderTraversal(Node* ptr)
{
	if(ptr) { //NULL�� �ƴϸ� ���� - NULL�϶� ����
		postorderTraversal(ptr->left);	//���ȣ��, ptr�� left child �ѱ� (L)
		postorderTraversal(ptr->right);	//���ȣ��, ptr�� right child �ѱ� (R)
		printf(" [%d] ", ptr->key);		//ptr�� key ���(V)
	}
}

/*key ����*/
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //���ο� node ����
	newNode->key = key;  	//node�� key���� ����ڷκ��� ���� key
	newNode->left = NULL;	//node�� left child�� NULL
	newNode->right = NULL;	//node�� right child�� NULL

	if (head->left == NULL) { //initializeBST �ϰ� ����߰��� ó���� ��,
		head->left = newNode; //head�� left child�� ���ο� node ����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr�� root

	Node* parentNode = NULL; //parentNode=NULL
	while(ptr != NULL) { //ptr�� NULL�� �ƴϸ� ��� �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr�� key�� �Է¹��� key�� ���ٸ� �׳� return

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		//ptr�� parentNode�� ����
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr�� ���� key���� �Է¹��� key�� ���� �۴ٸ�
			ptr = ptr->right; //ptr�� right child�� ptr��
		else			   //ptr�� ���� key���� �Է¹��� key�� ���� ũ�ٸ�
			ptr = ptr->left;  //ptr�� left child�� ptr�� ����
	}

	/* linking the new node to the parent */
	// ptr�� NULL�� �Ǿ� Ʈ�� �ȿ� key�� �´� ��尡 ��� while�� ���� ���
	if(parentNode->key > key) //parentNode�� ptr�� NULL�� �Ǳ� �� ���� ���, parentNode�� key���� �Է¹��� key���� Ŭ ���
		parentNode->left = newNode; //newNode�� parentNode�� left child
	else 					  //parentNode�� key�� �Է¹��� key���� ���� ���
		parentNode->right = newNode; //newNode�� parentNode�� right child
	return 1;
}

/*����*/
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { //head�� NULL�̶��
		printf("\n Nothing to delete!!\n"); //�ƹ��͵� ����� �� ���ٰ� ���
		return -1;
	}

	if (head->left == NULL) { //root�� NULL�̶��
		printf("\n Nothing to delete!!\n"); //�ƹ��͵� ����� �� ���ٰ� ���
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr�� root


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //parentNode��  head�� ����

	while(ptr != NULL) { //ptr�� NULL�� �ƴ� ������ �ݺ�

		if(ptr->key == key) { //ptr�� key���� �Է¹��� key�� ���ٸ�
			if(ptr->left == NULL && ptr->right == NULL) { //ptr�� left child�� right child�� �Ѵ� NULL�̶��

				/* root node case */
				if(parentNode == head) //parentNode�� head��� (���� root�� ptr�� ���� key�� �Է¹��� key�� ���ٸ�)
					head->left = NULL; //root�� NULL (delete ����)

				/* left node case or right case*/
				if(parentNode->left == ptr) //parentNode�� left child�� ptr�� ���ٸ�
					parentNode->left = NULL; //parentNode�� left child(��, ptr)�� NULL��(delete ����)
				else //parentNode�� left child�� ptr�� �ٸ��ٸ�
					parentNode->right = NULL; //parentNode�� right child(��, ptr)�� NULL��(delete ����)

				free(ptr); //ptr ����
			}
			else { //ptr�� left child�� right child�� �� �� �ϳ��� NULL�� �ƴ϶�� (��带 ������ �ִٸ�)
				printf("the node [%d] is not a leaf \n", ptr->key); //�ش� ���� leaf��尡 �ƴ�
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //parentNode�� ptr�� ����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr�� key���� key���� �۴ٸ�
			ptr = ptr->right; //ptr�� ptr�� right child�� ����
		else			   //ptr�� key���� key���� ũ�ٸ�
			ptr = ptr->left; //ptr�� ptr�� left child�� ����


	}

	printf("Cannot find the node for key [%d]\n ", key); //ptr�� NULL�� �Ǿ� while���� �������� ��� ("key���� ���� node�� ã�� �� ����")

	return 1;
}

//�Է¹��� key���� ��ġ�� ��͸� ����ϴ� ������� ã��
Node* searchRecursive(Node* ptr, int key) //�Ű�����(root, key)����
{
	if(ptr == NULL) //ptr(root)�� NULL�̶��
		return NULL; //NULL ��ȯ

	if(ptr->key < key) //ptr�� key���� �Է¹��� key������ �۴ٸ�
		ptr = searchRecursive(ptr->right, key); //����Լ�, ptr�� right child �ѱ�
	else if(ptr->key > key) //ptr�� key���� �Է¹��� key������ ũ�ٸ�
		ptr = searchRecursive(ptr->left, key); //����Լ�, ptr�� left child �ѱ�

	/* if ptr->key == key */
	return ptr; //ptr�� key���� �Է¹��� key���� �����ϴٸ� ���� ptr ��ȯ

}

//�Է¹��� key���� ��ġ�� ��带 �ݺ������� �Űܰ��� ã�� �۾����� ã��
Node* searchIterative(Node* head, int key) //�Ű�����(head, key)����
{
	/* root node */
	Node* ptr = head->left; //ptr�� root

	while(ptr != NULL) //ptr�� NULL�� �ƴ� ������ �ݺ�
	{
		if(ptr->key == key) //ptr�� key���� �Է¹��� key���� ���ٸ�
			return ptr; //ptr�� return 

		if(ptr->key < key) ptr = ptr->right; //ptr�� key���� �Է¹��� key������ �۴ٸ�, ptr�� right child�� ����
		else //ptr�� key���� �Է¹��� key������ ũ�ٸ�
			ptr = ptr->left; //ptr�� left child�� ����
	}

	return NULL; //��ã�Ҵٸ� NULL ��ȯ
}

//Ʈ�� �Ʒ����� ���ʷ� ���� ������Ű��
void freeNode(Node* ptr)
{
	if(ptr) { //ptr�� NULL�� �ƴ϶��
		freeNode(ptr->left);  //����Լ�, ptr�� left child�� �ѱ�
		freeNode(ptr->right); //����Լ�, ptr�� right child�� �ѱ�
		free(ptr);			  //ptr ����
	}
}

int freeBST(Node* head)
{
	if(head->left == head) //root�� head�� ���ٸ�
	{
		free(head); //head ����
		return 1;
	}

	Node* p = head->left; //��� p�� root

	freeNode(p); //��� p ����(freeNode �Լ� ȣ���ؼ�)

	free(head); //head�� ����
	return 1;
}