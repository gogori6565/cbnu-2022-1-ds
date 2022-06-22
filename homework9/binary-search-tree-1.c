#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; //노드의 값
	struct node *left;  //왼쪽 서브트리 (left child)
	struct node *right; //오른쪽 서브트리 (right child)
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
	//head와 ptr 노드 생성 (둘다 NULL로 초기화)
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
    
    printf("[----- [이주현]  [2021041075] -----]\n");

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
			initializeBST(&head); //이진트리 생성
			break;
		case 'q': case 'Q':
			freeBST(head); //이진트리 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //입력받은 key값 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); //입력받은 key값에 해당하는 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); //입력받은 key값의 위치를 노드를 반복적으로 옮겨가며 찾는 작업으로 찾기
			if(ptr != NULL) //ptr이 NULL이 아니라면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 key값의 노드는 ptr의 주소에서 찾았음을 출력
			else //ptr이 NULL이라면
				printf("\n Cannot find the node [%d]\n", key); //찾을 수 없음
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); //입력받은 key값의 위치를 재귀를 사용하여 찾기
			if(ptr != NULL) //ptr이 NULL이 아니라면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 key값의 노드는 ptr의 주소에서 찾았음을 출력
			else //ptr이 NULL이라면
				printf("\n Cannot find the node [%d]\n", key); //찾을 수 없음
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
	if(*h != NULL) //NULL이 아니면,
		freeBST(*h); //해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //h가 가리키는 곳에 메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

/*중위순회(LVR)
* left child -> node -> right child 순으로 순회한다.
*/
void inorderTraversal(Node* ptr)
{
	if(ptr) { //NULL이 아니면 실행 - NULL일때 멈춤
		inorderTraversal(ptr->left);  //재귀호출, ptr의 left child 넘김 (L)
		printf(" [%d] ", ptr->key);   //ptr의 key 출력 (V)
		inorderTraversal(ptr->right); //재귀호출, ptr의 right child 넘김 (R)
	}
}

/*전위순회(VLR)
* node -> left child -> right child 순으로 순회한다.
*/
void preorderTraversal(Node* ptr)
{
	if(ptr) { //NULL이 아니면 실행 - NULL일때 멈춤
		printf(" [%d] ", ptr->key);		//ptr의 key 출력(V)
		preorderTraversal(ptr->left); 	//재귀호출, ptr의 left child 넘김 (L)
		preorderTraversal(ptr->right);	//재귀호출, ptr의 right child 넘김 (R)
	}
}

/*후위순회(LRV)
* left child -> right child -> node 순으로 순회한다.
*/
void postorderTraversal(Node* ptr)
{
	if(ptr) { //NULL이 아니면 실행 - NULL일때 멈춤
		postorderTraversal(ptr->left);	//재귀호출, ptr의 left child 넘김 (L)
		postorderTraversal(ptr->right);	//재귀호출, ptr의 right child 넘김 (R)
		printf(" [%d] ", ptr->key);		//ptr의 key 출력(V)
	}
}

/*key 삽입*/
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 node 생성
	newNode->key = key;  	//node의 key값은 사용자로부터 받은 key
	newNode->left = NULL;	//node의 left child는 NULL
	newNode->right = NULL;	//node의 right child는 NULL

	if (head->left == NULL) { //initializeBST 하고 노드추가가 처음일 때,
		head->left = newNode; //head의 left child에 새로운 node 삽입
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr은 root

	Node* parentNode = NULL; //parentNode=NULL
	while(ptr != NULL) { //ptr이 NULL이 아니면 계속 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr의 key가 입력받은 key와 같다면 그냥 return

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		//ptr을 parentNode에 저장
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr이 가진 key값이 입력받은 key값 보다 작다면
			ptr = ptr->right; //ptr의 right child를 ptr로
		else			   //ptr이 가진 key값이 입력받은 key값 보다 크다면
			ptr = ptr->left;  //ptr의 left child를 ptr로 만듦
	}

	/* linking the new node to the parent */
	// ptr이 NULL이 되어 트리 안에 key와 맞는 노드가 없어서 while을 나온 경우
	if(parentNode->key > key) //parentNode는 ptr이 NULL이 되기 딱 이전 노드, parentNode의 key값이 입력받은 key보다 클 경우
		parentNode->left = newNode; //newNode는 parentNode의 left child
	else 					  //parentNode의 key가 입력받은 key보다 작은 경우
		parentNode->right = newNode; //newNode는 parentNode의 right child
	return 1;
}

/*삭제*/
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL이라면
		printf("\n Nothing to delete!!\n"); //아무것도 출력할 게 없다고 출력
		return -1;
	}

	if (head->left == NULL) { //root가 NULL이라면
		printf("\n Nothing to delete!!\n"); //아무것도 출력할 게 없다고 출력
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr은 root


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //parentNode를  head로 지정

	while(ptr != NULL) { //ptr이 NULL이 아닐 때까지 반복

		if(ptr->key == key) { //ptr의 key값이 입력받은 key와 같다면
			if(ptr->left == NULL && ptr->right == NULL) { //ptr의 left child와 right child가 둘다 NULL이라면

				/* root node case */
				if(parentNode == head) //parentNode가 head라면 (현재 root인 ptr이 가진 key가 입력받은 key와 같다면)
					head->left = NULL; //root는 NULL (delete 수행)

				/* left node case or right case*/
				if(parentNode->left == ptr) //parentNode의 left child가 ptr과 같다면
					parentNode->left = NULL; //parentNode의 left child(즉, ptr)를 NULL로(delete 수행)
				else //parentNode의 left child가 ptr과 다르다면
					parentNode->right = NULL; //parentNode의 right child(즉, ptr)를 NULL로(delete 수행)

				free(ptr); //ptr 해제
			}
			else { //ptr의 left child와 right child가 둘 중 하나라도 NULL이 아니라면 (노드를 가지고 있다면)
				printf("the node [%d] is not a leaf \n", ptr->key); //해당 노드는 leaf노드가 아님
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //parentNode를 ptr로 만듦

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key값이 key보다 작다면
			ptr = ptr->right; //ptr은 ptr의 right child로 변경
		else			   //ptr의 key값이 key보다 크다면
			ptr = ptr->left; //ptr은 ptr의 left child로 변경


	}

	printf("Cannot find the node for key [%d]\n ", key); //ptr이 NULL이 되어 while문을 빠져나온 경우 ("key값을 갖는 node를 찾을 수 없음")

	return 1;
}

//입력받은 key값의 위치를 재귀를 사용하는 방법으로 찾기
Node* searchRecursive(Node* ptr, int key) //매개변수(root, key)받음
{
	if(ptr == NULL) //ptr(root)이 NULL이라면
		return NULL; //NULL 반환

	if(ptr->key < key) //ptr의 key값이 입력받은 key값보다 작다면
		ptr = searchRecursive(ptr->right, key); //재귀함수, ptr의 right child 넘김
	else if(ptr->key > key) //ptr의 key값이 입력받은 key값보다 크다면
		ptr = searchRecursive(ptr->left, key); //재귀함수, ptr의 left child 넘김

	/* if ptr->key == key */
	return ptr; //ptr의 key값이 입력받은 key값과 동일하다면 현재 ptr 반환

}

//입력받은 key값의 위치를 노드를 반복적으로 옮겨가며 찾는 작업으로 찾기
Node* searchIterative(Node* head, int key) //매개변수(head, key)받음
{
	/* root node */
	Node* ptr = head->left; //ptr은 root

	while(ptr != NULL) //ptr이 NULL이 아닐 때까지 반복
	{
		if(ptr->key == key) //ptr의 key값이 입력받은 key값과 같다면
			return ptr; //ptr을 return 

		if(ptr->key < key) ptr = ptr->right; //ptr의 key값이 입력받은 key값보다 작다면, ptr을 right child로 만듦
		else //ptr의 key값이 입력받은 key값보다 크다면
			ptr = ptr->left; //ptr을 left child로 만듦
	}

	return NULL; //못찾았다면 NULL 반환
}

//트리 아래부터 차례로 전부 해제시키기
void freeNode(Node* ptr)
{
	if(ptr) { //ptr이 NULL이 아니라면
		freeNode(ptr->left);  //재귀함수, ptr의 left child를 넘김
		freeNode(ptr->right); //재귀함수, ptr의 right child를 넘김
		free(ptr);			  //ptr 해제
	}
}

int freeBST(Node* head)
{
	if(head->left == head) //root가 head와 같다면
	{
		free(head); //head 해제
		return 1;
	}

	Node* p = head->left; //노드 p는 root

	freeNode(p); //노드 p 해제(freeNode 함수 호출해서)

	free(head); //head도 해제
	return 1;
}