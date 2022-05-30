#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 10 //최대 Vertex의 수
#define MAX_QUEUE_SIZE 50 //최대 큐사이즈

typedef struct Node{
	int vertex; //정점의 데이터
	struct Node* link; //다음 인접 정점 연결 링크
}listnode;

typedef struct Head{
	int Vnum; //정점의 개수
	listnode* list[MAX_VERTEX]; //정점에 대한 헤드를 저장할 배열
}Graph;

typedef struct queue{
	int queue[MAX_QUEUE_SIZE]; //큐배열
	int first,last; //큐의 삭제끝, 삽입끝
}Q; //너비우선탐색에 쓰일 큐 구조체

short int visited[MAX_VERTEX]; //탐색에 쓰일 방문여부배열

void initialize(Graph **h);
int insert_vertex(Graph* h);
int insert_edge(Graph* h,int u, int v);
int print(Graph* h);
void freeGraph(Graph* h);
void dfs(Graph*h,int v);
void bfs(Graph* h,int v);
void init(Q *q);
int is_empty(Q *q);
int is_full(Q *q);
void enqueue(Q *q, int item);
int dequeue(Q *q);

int main(void)
{
	Graph* h=NULL;

    char command;
	int u,v;

    printf("[----- [이주현]  [2021041075] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph    = z                                    \n");
		printf(" Insert Vertex       = v           Insert Edge           = e\n");
		printf(" Depth First Search  = d           Breath First Search   = b\n");
		printf(" Print Graph         = p           Quit                  = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&h); //그래프 생성 및 초기화
			break;
		case 'v': case 'V':
			printf("삽입할 정점의 개수 = ");
			scanf("%d", &v); 		   //삽입할 정점의 개수 입력받기
			for(int i=0;i<v;i++)
				insert_vertex(h);	//입력받은 개수만큼 0~v(입력받은 개수-1)(최대 9)까지 정점이 생성됨
			break;
		case 'e': case 'E':
			printf("u = ");
			scanf("%d", &u); //꼬리가 될 vertex
			printf("v = ");
			scanf("%d", &v); //머리가 될 vertex
			//무방향그래프로 만들어 줄 것임
			insert_edge(h,u,v);  //간선 삽입
			insert_edge(h,v,u);  //무방향그래프면 반대도 삽입, 방향그래프면 (u,v)만 수행
			break;
		case 'd': case 'D':
			printf("깊이우선탐색 시작할 정점 v = ");
			scanf("%d", &v);
			dfs(h,v); //깊이우선탐색
			printf("\n");
			//깊이우선탐색 후 visitied 배열 초기화 - 안하면 계속 탐색 불가
			for(int i=0;i<MAX_VERTEX;i++)
				visited[i]=0;
			break;
		case 'b': case 'B':
			printf("너비우선탐색 시작할 정점 v = ");
			scanf("%d", &v);
			bfs(h,v); //너비우선탐색
			printf("\n");
			//너비우선탐색 후 visitied 배열 초기화 - 안하면 계속 탐색 불가
			for(int i=0;i<MAX_VERTEX;i++)
				visited[i]=0;
			break;
		case 'p': case 'P':
			print(h);
			break;
		case 'q': case 'Q':
			freeGraph(h); //메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못 입력 받았을 경우
			break;
		}

	}while(command != 'q' && command != 'Q');
}

void initialize(Graph **h)
{
	//h가 NULL이 아니면 freeGraph를 호출해 먼저 메모리 해제
	if(*h!=NULL)
	{
		freeGraph(*h);
	}

	*h=(Graph*)malloc(sizeof(Graph)); //h가 가리키는 곳에 메모리 할당
	(*h)->Vnum=0; //정점의 개수 0으로 초기화
	
	for(int i=0;i<MAX_VERTEX;i++)
	{
		(*h)->list[i]=NULL; //정점에 대한 헤드노드 배열 NULL로 초기화
	}
}

//그래프에 정점(vertex)삽입
int insert_vertex(Graph* h)
{
	//현재 최대정점 개수까지 도달한 경우 정잠을 더 삽입하지 못하도록 막음
	if(((h->Vnum)+1)>MAX_VERTEX)
	{
		printf("최대 vertex의 개수를 초과했습니다.\n");
		return 0;	
	}
	//최대 개수를 안넘는다면 정점 개수 하나 더 증가시킴
	h->Vnum++;
}

//그래프에 간선(u,v)삽입
int insert_edge(Graph* h,int u, int v)
{		
	if(u==v)
	{
		printf("self loop 불가\n");
		return 0;
	}
	//간선을 이을 수 없는 경우라면 종료 (u이나 v의 번호가 현재 정점의 개수보다 크거나 같다면)
	if((u>=h->Vnum)||(v>=h->Vnum)) //같으면 왜 안돼? : 배열이잖아 인덱스-1 만큼만 쓰니까
	{
		printf("정점 번호가 틀렸습니다.\n");
		return 0;
	}

	/*
	* 탐색할 때, 여러 간선 중에 번호가 작은 정점부터 탐색하기 위해서는
	* 인접리스트를 만드는 노드를 오름차순으로 넣어줘야한다
	*/
	listnode* u_node=(listnode*)malloc(sizeof(listnode));
	u_node=h->list[u]; //list[u]에 접근이 처음이면 NULL값
	listnode* u_node_trail=(listnode*)malloc(sizeof(listnode));
	u_node_trail=h->list[u]; //u_node를 가리키는 이전 노드
	listnode* v_node=(listnode*)malloc(sizeof(listnode)); //새노드 생성
	v_node->vertex=v; //새 노드가 가진 정점의 값을 v로 설정
	
	//오름차순으로 인접리스트 만들기 위해 수행
	while(1)
	{
		//h->list[u] 정점에 접근이 처음인 경우
		if(h->list[u]==NULL)
		{
			//맨 처음에(배열에)v_node를 추가 (u_node는 h->list[u])
			v_node->link=h->list[u];
			h->list[u]=v_node;
			return 0;
		}
		//v_node의 정점이 u_node의 정점보다 작은 경우 인접리스트에 삽입
		else if(v_node->vertex<u_node->vertex)
		{
			//숫자가 맨 처음(배열)에 들어가야하는 경우 (제일 작은 숫자인 경우)
			if(u_node==h->list[u])
			{
				v_node->link=h->list[u];
				h->list[u]=v_node;
			}
			//중간인 경우
			else
			{
				v_node->link=u_node;
				u_node_trail->link=v_node;
			}
			return 0;
		}
		//이미 존재하는 간선이라면
		else if(v_node->vertex==u_node->vertex)
		{
			printf("이미 존재하는 간선입니다.\n");
			return 0;
		}
		u_node_trail=u_node;
		u_node=u_node->link;
		
		/*
		* 여기서 마지막 노드를 검사하는 이유
		* 1) while(u_node!=NULL)을 할 수 없다 : 애초에 초기화한 h->list[u]가 첫 접근일 경우 NULL이어서 시작도 못하고 끝나버린다
		* 2) 중간부분에서 못하는 이유는 u_node가 NULL인데 ->vertex가 있을 수 없으니 더 작은지 확인하는 게 무의미하다
		*/
		if(u_node==NULL) //마지막 노드까지 왔다면
		{
			v_node->link=u_node;
			u_node_trail->link=v_node;
			return 0;
		}
	}
}

//그래프 인접리스트 출력
int print(Graph* h)
{
	for(int i=0;i<h->Vnum;i++)
	{
		listnode* n=h->list[i];
		printf("정점 %d의 인접 리스트 : ",i);
		while(n!=NULL)
		{
			printf("[%d] ",n->vertex);
			n=n->link;
		}
		printf("\n");
	}
}

//그래프 동적할당 해제
void freeGraph(Graph* h)
{
	for(int i=0;i<h->Vnum;i++)
	{
		listnode* n=h->list[i];
		listnode* prev=NULL;

		while(n!=NULL)
		{
			prev=n;
			n=n->link;
			free(prev);
		}
		free(n);
	}
}

//정점 v에서 시작하는 깊이우선탐색
void dfs(Graph*h,int v)
{
	listnode* w;
	visited[v]=1; //정점 v를 방문하면 1을 넣어 '방문했음'을 표시
	printf("%5d",v); //방문한 정점 순서대로 출력되도록 함
	for(w=h->list[v];w;w=w->link)
	{
		/*하나의 정점을 꺼내 정점의 인접리스트를 계속 처리하되,
		* 이미 방문한 정점(visited[v]값이 1)은 무시하고 방문하지 않은 정점(visited[v]값이 0)을 방문할 것임*/
		if(!visited[w->vertex])
			dfs(h,w->vertex);
	}
}

//정점 v에서 시작하는 너비 우선 탐색
void bfs(Graph* h,int v)
{
	listnode *w;
	Q q;
	init(&q);    		 //큐 초기화 
	visited[v] = 1;      //정점 v를 방문하면 1을 넣어 '방문했음'을 표시
	printf("%5d", v);    //방문한 정점 순서대로 출력되도록 함
	enqueue(&q, v);		 //시작정점을 큐에 저장 

	while (!is_empty(&q)) {
		v = dequeue(&q);		// 큐에 저장된 정점 선택 
		for(w=h->list[v];w;w=w->link)
		{
			if (!visited[w->vertex]) 
			{ 
				visited[w->vertex] = 1;   //방문 표시
				printf("%5d", w->vertex);
				enqueue(&q, w->vertex);	  //정점을 큐에 삽입
			}
		}
	}
}

// 초기화 함수
void init(Q *q)
{
	q->first = q->last = 0;
}

// 공백 상태 검출 함수
int is_empty(Q *q)
{
	if(q->first == q->last) return 1;
	else return 0;
}

// 포화 상태 검출 함수
int is_full(Q *q)
{
	if((q->last + 1) % MAX_QUEUE_SIZE == q->first) return 1;
	else return 0;
}

// 삽입 함수
void enqueue(Q *q, int item)
{
	if (is_full(q))
		printf("큐가 포화상태입니다\n");
	q->last = (q->last + 1) % MAX_QUEUE_SIZE; //삽입 끝 한 칸 앞으로 가서 삽입
	q->queue[q->last] = item;
}

// 삭제 함수
int dequeue(Q *q)
{
	if (is_empty(q))
		printf("큐가 공백상태입니다\n");
	q->first = (q->first + 1) % MAX_QUEUE_SIZE; //한 칸 앞으로 가서 해당 내용 삭제
	return q->queue[q->first];
}