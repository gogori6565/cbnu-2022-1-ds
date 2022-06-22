#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; //노드의 값
	struct node *left; //왼쪽 서브트리 (left child)
	struct node *right; //오른쪽 서브트리 (right child)
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE]; //스택
int top = -1; //top -1로 초기화

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE]; //큐
int front = -1; //front -1로 초기화
int rear = -1; //rear -1로 초기화

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

	printf("[----- [이주현]  [2021041075] -----]\n");

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
	if(*h != NULL) //NULL이 아니면,
		freeBST(*h); //해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //h가 가리키는 곳에 메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

//중위순회
void recursiveInorder(Node* ptr)
{
	if(ptr) { //ptr이 NULL이 아니라면
		recursiveInorder(ptr->left); //재귀함수, ptr의 left child 넘겨줌
		printf(" [%d] ", ptr->key); //ptr의 key값 출력 
		recursiveInorder(ptr->right); //재귀함수, ptr의 right child 넘겨줌
	}
}

/**
 * textbook: p 224
 */
/*반복적 중위 순회 - 스택을 필요로 하는 순회
* : 순회 방법은 중위 순회와 같다.
*/
void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left) //left child가 널 노드에 도달될 때까지 스택에 삽입한다
			push(node); //스택에 삽입
		//그러다 널 노드에 도달하면 다시 스택에서 삭제한다 (가장 최근에 쌓인 것부터)
		node = pop(); //스택에서 삭제

		if(!node) break; //공백 스택이면 반복 멈춤
		printf(" [%d] ", node->key); //node의 key값 출력

		node = node->right; //node는 node의 right child로 변경
	}
}

/**
 * textbook: p 225
 */
/*레벨 순서 트리 순회 - 큐를 필요로 하는 순회
* : 루트를 먼저 방문한 다음, 왼쪽 자식, 오른쪽 자식을 방문
* 이러한 방법으로 새 레벨의 노드를 가장 왼쪽부터 오른쪽까지 차례로 방문한다
*/
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); //root(ptr)를 큐에 삽입

	for(;;)
	{
		ptr = deQueue(); //삭제 큐에서 반환한 노드 ptr에 저장 (deQueue의 반환 타입은 Node*)
		if(ptr) { //ptr이 NULL이 아니라면
			printf(" [%d] ", ptr->key); //ptr의 key값 출력 (삭제한 노드의 데이터 출력)

			if(ptr->left) //ptr의 left child가 NULL이 아니라면
				enQueue(ptr->left); //ptr의 left child 큐에 삽입
			if(ptr->right) //ptr의 right child가 NULL이 아니라면
				enQueue(ptr->right); //ptr의 right child 큐에 삽입
		}
		else //ptr이 NULL이면
			break; //반복 끝!

	}
}

/*삽입*/
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드
	newNode->key = key; //새로운 노드의 key는 입력받은 key
	newNode->left = NULL; //새로운 노드의 left child는 NULL
	newNode->right = NULL; //새로운 노드의 right child는 NULL

	if (head->left == NULL) { //initializeBST 하고 노드추가가 처음일 때,
		head->left = newNode; //head의 left child에 새로운 node 삽입
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr은 root

	Node* parentNode = NULL; //parentNode = NULL
	while(ptr != NULL) { //ptr이 NULL이 아니면 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr의 key가 입력받은 key와 같다면

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr을 parentNode에 저장

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr이 가진 key값이 입력받은 key값 보다 작다면
			ptr = ptr->right; //ptr의 right child를 ptr로
		else //ptr이 가진 key값이 입력받은 key값 보다 크다면
			ptr = ptr->left; //ptr의 left child를 ptr로 만듦
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //현재 parentNode는 ptr이 NULL이 되기 딱 이전 노드, parentNode의 key값이 입력받은 key보다 클 경우
		parentNode->left = newNode; //newNode는 parentNode의 left child
	else //parentNode의 key값이 입력받은 key보다 작을 경우
		parentNode->right = newNode;  //newNode는 parentNode의 right child
	return 1;
}

/*삭제*/
int deleteNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //root가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //head의 left child는 root


	Node* parent = NULL; //parent = NULL
	Node* ptr = root; //ptr은 root

	/*ptr이 NULL이 아니고 ptr의 key값이 입력받은 key값과 다르다면 반복
	* 즉, ptr이 NULL이 되거나, ptr의 key값이 입력받은 key값과 같게 된다면 반복 종료
	*/
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) { //ptr의 key값이 입력받은 key값고 다르다면

			parent = ptr;	/* save the parent */
			//parent는 ptr

			if(ptr->key > key) //ptr의 key값이 입력받은 key값보다 크다면
				ptr = ptr->left; //ptr은 ptr의 left child
			else //ptr의 key값이 입력받은 key값보다 작다면
				ptr = ptr->right; //ptr은 ptr의 right child
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //ptr이 NULL이라면
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node : 삭제될 노드가 leaf node일 경우
	 */
	if(ptr->left == NULL && ptr->right == NULL) //ptr의 left와 right child가 NULL이라면
	{
		//parent가 NULL이 아닐 때 
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) //parent의 left child가 ptr이면
				parent->left = NULL; //parent의 left child를 NULL로
			else //parent의 right child가 ptr이면
				parent->right = NULL; //parent의 right child를 NULL로
		} else { //parent가 NULL이면 (ptr이 root인데 입력받은 key값과 동일해서 오는 경우)
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; //root를 NULL(삭제)

		}

		free(ptr); //ptr 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child : 삭제될 노드가 가진 자식노드가 한 개인 경우
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //ptr의 left child 나 right child 둘 중 하나라도 NULL이면 (둘 다 NULL이면 위에서 걸려)
	{
		Node* child; //child라는 node 생성
		if (ptr->left != NULL) //ptr의 left chlid가 그 한 개의 자식노드라면 
			child = ptr->left; //child는 ptr의 left child
		else //ptr의 right child가 그 한 개의 자식노드라면
			child = ptr->right; //chlid는 ptr의 right child

		if(parent != NULL) //parent가 NULL이 아니면
		{
			if(parent->left == ptr) //parent의 left child가 ptr이라면
				parent->left = child; //parent의 left child는 child이다
			else //parent의 left child가 ptr이 아니라면
				parent->right = child; //parent right child는 child이다
		} else { // parent가 NULL이라면
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //child는 root (root인 ptr을 없애고 child가 root가 되는 것임)
		}

		free(ptr); //ptr 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children : ptr노드가 자식 둘 다 가지고 있을 경우
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //candidate이라는 노드 생성
	parent = ptr; //parent = ptr


	candidate = ptr->right; //candidate은 ptr의 right child

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) //candidate의 left child가 존재한다면
	{
		parent = candidate; //parent를 candidate로
		candidate = candidate->left; //candidate의 left child를 candidate으로 변경
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //parent의 right child가 candidate과 같다면
		parent->right = candidate->right; //parent의 right child를 candidate의 right child로 변경
	else //아니라면
		parent->left = candidate->right; //parent의 left child를 candidate의 right child로 변경

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //candidate의 key값을 ptr의 key값으로 넣음

	free(candidate); //candidate 해제
	return 1;
}

//노드 해제
void freeNode(Node* ptr)
{
	if(ptr) { //ptr이 NULL이 아니라면 실행
		freeNode(ptr->left); //재귀함수, ptr의 left child 해제
		freeNode(ptr->right); //재귀함수, ptr의 right child 해제
		free(ptr); //ptr 해제
	}
}

//이진트리 해제
int freeBST(Node* head)
{

	if(head->left == head) //head의 left child가 head와 같다면
	{
		free(head); //head 해제
		return 1;
	}

	Node* p = head->left; //p는 root

	freeNode(p); //p노드 해제

	free(head); //head 해제
	return 1;
}

Node* pop()
{
	if (top < 0) return NULL; //top이 0보다 작으면 (-1이면) 반환
	return stack[top--]; //현재 top 상태의 stack을 반환한 뒤에 top 1 감소시키기
}

void push(Node* aNode)
{
	stack[++top] = aNode; //top을 1 증가시킨 후 aNode를 stack에 삽입
}

//Stack 출력
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) //i가 top보다 작거나 같으면 반복
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

Node* deQueue()
{
	if (front == rear) { //front와 rear가 같다면 공백
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //공백이 아니라면, front를 한 칸 앞으로 보내고
	return queue[front]; //현재 front인 큐에 있는 값을 반환

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear를 한 칸 앞으로 보내고
	if (front == rear) { //front와 rear가 같다면 가득참
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //가득차지 않았다면 현재 rear의 큐에 aNode 삽입
}
