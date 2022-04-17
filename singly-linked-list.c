#include<stdio.h>
#include<stdlib.h> //malloc(), free()

/* 필요한 헤더파일 추가 */

typedef struct Node {  //연결리스트의 Node 구조체
	int key;		   //데이터를 저장할 멤버 key
	struct Node* link; //다음 노드의 주소를 저장할 포인터 link
} listNode; //구조체 변수 listNode

typedef struct Head {
	struct Node* first; //headNode의 Node인 first 노드
}headNode; //headNode로 쓰일 구조체 변수


/* 함수 리스트 */
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

    printf("[----- [이주현]  [2021041075] -----]\n");

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
			headnode = initialize(headnode); //headnode에 대한 메모리 할당
			break;
		case 'p': case 'P':
			printList(headnode); //연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); 		   //key 입력받기
			insertNode(headnode, key); //노드 삽입(입력받은 key보다 큰값이 나오는 노드 바로 앞에)
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);		   //key 입력받기
			deleteNode(headnode, key); //노드 삭제(입력받은 key에 해당하는 노드)
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);		   //key 입력받기
			insertLast(headnode, key); //마지막에 노드 입력
			break;
		case 'e': case 'E':
			deleteLast(headnode);	   //마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);		    //key 입력받기
			insertFirst(headnode, key); //첫번째에 노드 입력
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);		//연결리스트 역순으로 재배치
			break;
		case 'q': case 'Q':
			freeList(headnode); //메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못 입력 받았을 경우
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	//headNode가 NULL이면(OR 메모리를 모두 해제했으면)
	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
		/*연결리스트는 일방향으로 감
		* p를 prev에 넣지 않고 그냥 free 시켜버리면 그 다음 노드들을 해제할 수 없기 때문에
		* 현재 p를 prev에 넣고, p는 다음 link를 가리키는 노드로 이동시킨 후 prev를 해제하면
		* 최종적으로 리스트를 모두 해제시킬 수 있음 p가 NULL일 땐 끝남.
		*/
	}
	free(h); //headNode도 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 동적할당
	node->key = key;   //새로만든 node에 (입력받은)데이터값 입력
	node->link = NULL; //일단 link가 NULL을 가리키도록

	if (h->first == NULL) //공백리스트이면
	{
		h->first = node; //첫 노드가 위에서 새로만든 node로 배정
		return 0;
	}

	//n은 현재노드, trail은 이전노드 역할
	listNode* n = h->first;     //n은 첫노드
	listNode* trail = h->first; //trail(previous)은 첫노드
	//==> 이거 왜해? : 첫노드 부터 검사해줘야 key를 크기 순으로 잘 입력하지

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) { //n이 가진 key가 입력받은 key보다 크거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 첫노드라면
				h->first = node; //첫 노드를 node로 하고
				node->link = n;  //node가 (첫노드였던)n을 가리키도록 함
				//==> 그러면 더 작은 key를 가진 node가 큰값을 가진 n 보다 앞으로 갈 수 있음
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;		//node가 가리키는 link가 n		
				trail->link = node; //trail(이전)이 가리키는 link가 node
			}
			return 0;
		}

		//**trail을 먼저 n으로 삽입해야해. n먼저 하면 현재노드를 trail이랑 같이 가리키고 전 노드를 버리는 셈이니까**
		trail = n;   //trail(이전)은 n
		n = n->link; //n은 다음 노드로 옮겨감
	}

	/* 마지막 노드까지 찾지 못한 경우(자리 찾으면 while안에서 return 0 됨) , 마지막에 삽입 */
	//즉, 마지막 노드까지 입력받은 key가 여기 모든 노드의 키보다 다 커!
	trail->link = node; //trail(이전)노드가 다음노드로 node를 가리킴
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가 (마지막에 추가)
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 node 생성
	node->key = key;   //node->key = 입력받은 key
	node->link = NULL; //node->link = NULL (아직 뭘 가리키고 있지 않아)

	if (h->first == NULL) //공백 리스트 이면
	{
		h->first = node; //첫노드를 node로 설정
		return 0;
	}

	listNode* n = h->first;  //현재노드 n을 첫노드로 설정
	while(n->link != NULL) { //n이 마지막노드가 아니면
		n = n->link; //n을 다음노드로 옮김 (마지막에 추가할거라서 마지막까지 옮기는 거임)
	}
	//n->link == NULL : 현재노드 n이 마지막노드이면
	n->link = node; //마지막노드로 node를 설정
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 node 생성
	node->key = key; //node가 가리키는 key에 입력 key 넣음

	//node가 가리키는 다음 link에 현재 첫노드로 넣고 node를 첫노드로 지정하면 처음에 추가 가능
	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //공백 리스트이면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) { //현재노드 n의 key가 입력key와 같은 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 첫노드인 경우
				h->first = n->link; //n이 가리키는 노드를 첫노드로 설정
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //n노드가 가리키는 노드를 이전노드가 가리키는 곳으로 설정 (n노드가 가리키는 노드를 쏙 빼버림)
			}
			free(n); //n노드 해제
			return 0;
		}

		trail = n;	 //이전노드 n노드로
		n = n->link; //n이 가리키는 노드를 n노드로 설정
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
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
	if(n->link == NULL) { //지금은 while을 돌리지도 않고 첫노드 설정하자마자 검사하니까! first node==last node인 경우 처리
		h->first = NULL; //첫노드 NULL
		free(n); //n노드 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;	 //이전노드를 n노드로 설정
		n = n->link; //n노드는 다음 노드로 옮김 (마지막 노드까지 쭉)
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n); //n노드 해제

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
	listNode* n = h->first; //현재노드 n을 첫노드로 설정

	//n이 가리키는 다음 노드를 첫노드로 설정하고 n노드 해제하면 첫번째 노드만 삭제 가능
	h->first = n->link;
	free(n);

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
		trail = middle; 	  //이전노드 trail = middle
		middle = n;     	  //middle은 현재노드 n
		n = n->link;    	  //n은 다음 노드로 옮겨짐
		middle->link = trail; //(아까 현재노드 n을 받은)middle이 가리키는 다음 노드가 trail (역순으로 가리키는 거임)
		//+) 이게 처음이면 trail에는 NULL이 들어있으니까 첫노드가 NULL을 가리키는 마지막 노드가 될 수 있음
	}

	h->first = middle; //middle(원래 리스트에서 마지막노드)을 첫노드로 설정

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
		p = p->link; 					   //다음 link를 가리키도록 함
		i++;
	}

	printf("  items = %d\n", i); //노드의 개수 출력
}

