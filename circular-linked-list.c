#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;
//원형 연결 리스트이기 때문에 singly와 doubly처럼 Head를 따로 만들지 않고, 헤드노드도 llink, rllink를 갖는 listNode로 사용할 것임

/* 함수 리스트 */
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
	listNode* headnode=NULL; //listNode 구조체 포인터 headnode

	printf("[----- [이주현]  [2021041075] -----]\n");

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
			initialize(&headnode); //연결리스트 생성
			break;
		case 'p': case 'P':
			printList(headnode); //연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //새노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //입력받은 key에 해당하는 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //마지막에 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); //마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //첫번째에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); //첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); //역순 배치
			break;
		case 'q': case 'Q':
			freeList(headnode); //연결리스트 해제
			break;
		default: //잘못된 값 입력시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

//이중포인터를 매개변수로 받음 - *h는 headNode의 주소, 즉 headNode의 주소를 저장하는 포인터(*h)의 주소를 받기 위해 이중포인터를 씀
int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); //h가 가리키는 곳에 메모리 할당
	(*h)->rlink = *h;  //h의 오른쪽 노드를 가리키는 링크를 자신으로
	(*h)->llink = *h;  //h의 왼쪽 노드를 가리키는 링크를 자신으로 설정 (원형 연결 리스트이기 때문)
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	//노드가 하나인 경우
	if(h->rlink == h)
	{
		free(h); //헤드노드만 해제
		return 1;
	}

	listNode* p = h->rlink; //노드 p는 첫노드
	listNode* prev = NULL;

	while(p != NULL && p != h) { //노드 p가 NULL이 아니고(and) 헤드노드도 아닌 경우
		prev = p;		//prev에 p넣고
		p = p->rlink;	//p는 오른쪽 노드로 옮김
		free(prev);		//prev 해제
	}
	free(h); //헤드노드도 해제
	return 0;
}

//리스트 출력
void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //headNode가 NULL이면 (리스트 생성이 안된 경우))
		printf("Nothing to print....\n"); //출력할 거 없음
		return;
	}

	p = h->rlink; //노드 p를 첫노드로 설정

	while(p != NULL && p != h) { //노드 p가 NULL이 아니고(and) 헤드노드도 아닌 경우
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //노드 p 마지막까지 옮겨주며 출력
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//headnode의 llink, headnode 자신, rlink의 값 출력 (주소 출력됨)

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
	//각 출력값을 보면 연결리스트가 왼쪽링크, 오른쪽 링크로 왼쪽노드, 오른쪽 노드와 잘 연결돼있음을 볼 수 있음

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; //빈 리스트이면 종료
	
	//새노드 생성
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;	//새노드가 갖는 key값은 입력받은 key값
	node->rlink = NULL; //오른쪽 링크 : NULL
	node->llink = NULL; //왼쪽 링크 : NULL

	//노드가 헤드노드 하나이면
	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; //헤드노드가 가리키는 오른쪽 노드를 node
		h->llink = node; //헤드노드가 가리키는 왼쪽 노드를 node로
		node->rlink = h; //node가 가리키는 오른쪽 노드를 헤드노드로
		node->llink = h; //node가 가리키는 왼쪽 노드를 h로 설정
		//즉, 헤드노드와 node가 쌍으로 서로를 가리키며 원형 연결을 가능케함
	} 
	else //노드가 여러 개이면 
	{
		h->llink->rlink = node; //헤드노드가 가리키는 왼쪽노드(리스트의 마지막 노드)가 가리키는 오른쪽 노드를 node로
		node->llink = h->llink; //node가 가리키는 왼쪽노드를 헤드노드가 가리키는 왼쪽노드(리스트의 마지막 노드)로
		h->llink = node;		//헤드노드가 가리키는 왼쪽노드(리스트의 마지막 노드)를 node로 (이제 node가 마지막이니까)
		node->rlink = h;		//노드가 가리키는 오른쪽 노드를 헤드노드로 설정
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	//리스트에 노드가 헤드노드 하나뿐이거나(OR) 헤드노드가 NULL인 경우
	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n"); //삭제할 게 없다
		return 1;
	}

	listNode* nodetoremove = h->llink; //nodetoremove를 첫노드로 설정

	/* link 정리 */
	nodetoremove->llink->rlink = h; //nodetoremove의 왼쪽 노드가 가리키는 오른쪽 노드를 첫노드로
	h->llink = nodetoremove->llink; //h가 가리키는 왼쪽노드(마지막노드)를 nodetoremove가 가리키던 왼쪽 노드로 설정

	free(nodetoremove); //nodetoremove 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	//새노드 생성
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink; //새노드가 가리키는 오른쪽 노드를 헤드노드가 가리키는 오른쪽 노드로 설정
	h->rlink->llink = node; //헤드노드가 가리키는 오른쪽 노드가 가리키는 왼쪽 노드를 node로
	node->llink = h;		//새노드가 가리킬 왼쪽 노드를 헤드노드로
	h->rlink = node;		//헤드노드가 가리키는 오른쪽 노드를 새노드로 설정
	/*1)노드가 헤드노드 하나일때는 h와 node가 서로를 가리켜 원형 연결하도록 할 수 있고
	* 2)노드가 여러개 일 경우는 node를 처음에 추가하지만 헤드노드와 맨 끝 노드가 서로를 연결하고 있어 원형 연결이 가능해진다.
	*/

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	//리스트에 노드가 헤드노드 하나뿐이거나(OR) 헤드노드가 NULL인 경우
	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n"); //삭제할 게 없다
		return 0;
	}

	listNode* nodetoremove = h->rlink; //nodetoremove를 첫노드로 설정

	/* link 정리 */
	nodetoremove->rlink->llink = h; //nodetoremove(첫노드)가 가리키는 오른쪽노드가 가리키는 왼쪽노드를 헤드노드로
	h->rlink = nodetoremove->rlink;	//첫노드를 nodetoremove(첫노드)가 가리키는 오른쪽 노드로 설정

	free(nodetoremove); //nodetoremove 삭제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	//리스트에 노드가 헤드노드 하나뿐이거나(OR) 헤드노드가 NULL인 경우
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n"); //역순할 게 없음
		return 0;
	}
	listNode *n = h->rlink; //노드 n은 첫노드
	listNode *trail = h;	//노드 trail은 헤드노드
	listNode *middle = h; 	//노드 middle은 헤드노드

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;
	//역순 배치하면 h->rlink(첫노드)가 마지막노드가 되니까 마지막노드를 h->llink가 가리키는 거지

	while(n != NULL && n != h){ //노드 n이 NULL이 아니고(and) 헤드노드도 아닌 경우
		trail = middle;			//trail이 middle로
		middle = n;				//middle이 n으로
		n = n->rlink;			//n이 다음노드로
		middle->rlink = trail;	//middle이 가리키는 오른쪽 노드를 trail(이전)으로
		middle->llink = n;		//middle이 가리키는 왼쪽 노드를 n(다음노드)로 설정
	}

	h->rlink = middle; //마지막 노드일 middle을 첫노드로 설정

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //빈 리스트이면 종료

	//새노드 생성
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //새노드가 갖는 key값은 입력받은 key값
	node->llink = node->rlink = NULL; //오른쪽, 왼쪽노드 가리키는 링크 : NULL 

	//노드가 하나일 경우
	if (h->rlink == h)
	{
		insertFirst(h, key); //노드 처음에 추가
		return 1;
	}

	listNode* n = h->rlink; //n을 첫노드로 설정

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { //n이 NULL이 아니고(and) 헤드노드도 아닌 경우
		if(n->key >= key) { //n이 가리키는 key가 입력 key보다 큰 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //n이 첫노드면
				insertFirst(h, key); //첫노드에 n추가
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;		//새노드가 가리키는 오른쪽 노드를 n
				node->llink = n->llink; //새노드가 가리키는 왼쪽 노드를 n이 가리키던 왼쪽노드로 설정
				n->llink->rlink = node; //n이 가리키는 왼쪽 노드가 가리키는 오른쪽 노드를 node로 
				n->llink = node;		//n이 가리키는 왼쪽 노드를 node로 설정
			}
			return 0;
		}

		n = n->rlink; //n을 다음노드로 옮김
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	//리스트에 노드가 헤드노드 하나뿐이거나(OR) 헤드노드가 NULL인 경우
	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n"); //삭제할 게 없다
		return 0;
	}

	listNode* n = h->rlink; //노드 n은 첫노드

	while(n != NULL && n != h) { //노드 n이 NULL이 아니고(and) 헤드노드도 아닌 경우
		if(n->key == key) { //n이 가리키는 key값이 입력받은 key값과 같은 경우
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //첫노드 삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 왼쪽 노드가 가리키는 오른쪽 노드를 n의 오른쪽 노드로
				n->rlink->llink = n->llink; //n의 오른쪽 노드가 가리키는 왼쪽 노드를 n의 왼쪽 노드로 설정
				free(n); //n 해제
			}
			return 0;
		}

		n = n->rlink; //n을 다음노드로 옮김
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}
