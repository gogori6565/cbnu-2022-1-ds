#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;            //데이터를 저장할 멤버 key
	struct Node* llink; //왼쪽 노드를 가리킬 링크
	struct Node* rlink; //오른쪽 노드를 가리킬 링크
} listNode;

typedef struct Head {
	struct Node* first; //headNode의 Node인 first 노드
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
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

    printf("[----- [이주현]  [2021041075] -----]\n");

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
			initialize(&headnode); //headnode에 대한 메모리 할당(headnode는 주소 전달), headnode의 주소를 전달하였으므로 반환값x
			break;
		case 'p': case 'P':
			printList(headnode); //연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //Node추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //Node삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //마지막에 노드 추가
			break;
		case 'e': case 'E':
			deleteLast(headnode); //마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //첫번째에 노드 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode); //첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); //노드 역순으로
			break;
		case 'q': case 'Q':
			freeList(headnode); //노드 해제
			break;
		default: //잘못 입력하였을 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

//이중포인터를 매개변수로 받음 - *h는 headNode의 주소, 즉 headNode의 주소를 저장하는 포인터(*h)의 주소를 받기 위해 이중포인터를 씀
int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

    //headNode가 NULL이면(OR 메모리를 모두 해제했으면)
	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //h가 가리키는 곳에 메모리 할당
	(*h)->first = NULL;
	return 1; //headnode의 주소로 받아 넘겨주므로 return 안해줘도 됨
}

//단일포인터를 매개변수로 받음 - 메모리를 해제할 거니까 해제할 메모리에 접근하면됨, 이중포인터로 해도 가능
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {//p가 NULL일 때 끝남
		prev = p;     //prev에 p넣고
		p = p->rlink; //p는 오른쪽 노드로 옮김
		free(prev);   //prev 해제
	}
	free(h); //headNode도 해제
	return 0;
}

//연결리스트 출력
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //공백리스트라면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p는 첫번째 노드

	while(p != NULL) { //노드의 끝에 닿을 때까지
		printf("[ [%d]=%d ] ", i, p->key); //데이터 출력
		p = p->rlink;                      //다음 link를 가리키도록 함
		i++;
	}

	printf("  items = %d\n", i); //노드 개수 출력
}

/**
 * list에 key에 대한 노드하나를 추가 (마지막에 추가)
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 node 생성
	node->key = key;    //node->key = 입력받은 key
	node->rlink = NULL; //오른쪽 노드를 가리키는 링크 = NULL
	node->llink = NULL; //왼쪽 노드를 가리키는 링크 = NULL

	if (h->first == NULL) //공백 리스트 이면
	{
		h->first = node; //새로만든 node를 첫노드로 설정
		return 0;
	}

	listNode* n = h->first;   //현재노드 n을 첫노드로 설정
	while(n->rlink != NULL) { //n이 마지막노드가 아니면
		n = n->rlink; //n을 다음노드로 옮김 (마지막에 추가할거라서 n을 마지막까지 옮김)
	}
    //n이 마지막 노드라면
	n->rlink = node; //n의 오른쪽 노드로 node를 가리킴
	node->llink = n; //node의 왼쪽 노드로 n을 가리킴
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //공백 리스트이면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //현재노드 n을 첫노드로 설정
	listNode* trail = NULL; //이전노트 trail은 NULL

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { //현재노드 n(첫노드)이 가리키는 오른쪽 노드가 NULL일 경우 (first node == last node)
		h->first = NULL; //첫노드 NULL
		free(n); //n노드 해제
		return 0;
	}
	
	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n; //이전노드를 n노드로 설정
		n = n->rlink; //n노드는 다음 노드로 옮김 (마지막 노드까지 이동)
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //이전노드가 가리키는 오른쪽 노드(n)을 NULL로
	free(n); //그리고 n노드 해제

	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 node 생성
	node->key = key; //node가 가리키는 key에 입력 key 넣음
	node->rlink = node->llink = NULL; //node의 오른쪽, 왼쪽 노드 NULL

	if(h->first == NULL) //첫노드가 NULL인 경우
	{
		h->first = node; //node를 첫노드로 설정
		return 1;
	}

	node->rlink = h->first; //node가 가리키는 오른쪽 노드 => 원래 첫노드
	node->llink = NULL;     //node가 가리키는 왼쪽 노드는 NULL (node를 처음에 추가할 거니까!)

	listNode *p = h->first; //첫노드롤 노드 p에 넣고
	p->llink = node; //p의 왼쪽 노드를 node로 설정하고
	h->first = node; //node를 첫노드로 설정

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //공백 리스트이면
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //현재노드 n에 첫노드 넣기
	h->first = n->rlink; //n이 가리키는 오른쪽 노드를 첫노드로 설정

	free(n); //현재노드 n(삭제하려했던 첫노드)를 해제 

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //공백 리스트인 경우
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;  //현재노드 n을 첫노드로 설정
	listNode *trail = NULL;  //이전노드 trail은 NULL
	listNode *middle = NULL; //middle은 NULL

	while(n != NULL){
		trail = middle; //이전노드 trail = middle
		middle = n;     //middle은 현재노드 n
		n = n->rlink;   //n은 n이 가리키는 오른쪽 노드로 옮겨짐
		middle->rlink = trail; //(아까의 현재노드 n인)middle이 가리키는 오른쪽 노드가 이전 노드(역순 배치)
		middle->llink = n;     //middle이 가리키는 왼쪽 노드가 n
	}

	h->first = middle; //middle(원래 리스트에서 마지막노드)을 첫노드로 설정

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 node 생성
	node->key = key; //새로만든 node에 (입력받은)데이터값 입력
	node->llink = node->rlink = NULL; //node가 가리키는 왼쪽, 오른쪽 노드 NULL

	if (h->first == NULL) //공백리스트이면
	{
		h->first = node; //첫 노드를 위에서 새로만든 node로 배정
		return 0;
	}

	listNode* n = h->first; //현재노드 n은 첫노드로 설정

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) { //n이 가진 key가 입력받은 key보다 크거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {  //n이 첫노드라면
				insertFirst(h, key); //insertFirst 함수 호출하여 첫노드에 해당 key값 가진 노드 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //node가 가리키는 오른쪽 노드를 n으로 설정
				node->llink = n->llink; //node가 가리키는 왼쪽 노드를 n이 가리키는 왼쪽노드로 설정
				n->llink->rlink = node; //n이 가리키는 왼쪽노드(현재 node가 가리키는 왼쪽노드)의 오른쪽 노드를 가리키는 링크가 node를 가리킴
				//(즉, 원래 n이 가리키던 왼쪽 노드와 현재 n사이에 node가 낄 수 있음)
			}
			return 0;
		}

		n = n->rlink; //n이 가진 key가 입력받은 key보다 작다면 계속 오른쪽 노드로 옮기면서 아닌 경우 찾기
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //insertLast 함수 호출해 마지막에 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //공백 리스트이면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; //현재노드 n을 첫노드로 설정

	while(n != NULL) {
		if(n->key == key) { //현재노드 n의 key가 입력key와 같은 경우
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //deleteFirst 함수 호출해서 첫번째 노드 삭제
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); //deleteLast 함수 호출해서 마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //원래 자신(n)을 가리키던 왼쪽 노드의 오른쪽링크를 자신(n)이 가리키는 오른쪽 노드를 가리키도록 함
				n->rlink->llink = n->llink; //원래 자신(n)을 가리키던 오른쪽 노드의 왼쪽링크를 자신(n)이 가리키는 왼쪽 노드를 가리키도록 함
				free(n); //그리고 n노드 해제
			}
			return 1;
		}

		n = n->rlink; //n을 다음노드로 옮김
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}