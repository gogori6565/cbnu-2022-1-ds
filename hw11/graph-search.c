#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 10 //�ִ� Vertex�� ��
#define MAX_QUEUE_SIZE 50 //�ִ� ť������

typedef struct Node{
	int vertex; //������ ������
	struct Node* link; //���� ���� ���� ���� ��ũ
}listnode;

typedef struct Head{
	int Vnum; //������ ����
	listnode* list[MAX_VERTEX]; //������ ���� ��带 ������ �迭
}Graph;

typedef struct queue{
	int queue[MAX_QUEUE_SIZE]; //ť�迭
	int first,last; //ť�� ������, ���Գ�
}Q; //�ʺ�켱Ž���� ���� ť ����ü

short int visited[MAX_VERTEX]; //Ž���� ���� �湮���ι迭

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

    printf("[----- [������]  [2021041075] -----]\n");

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
			initialize(&h); //�׷��� ���� �� �ʱ�ȭ
			break;
		case 'v': case 'V':
			printf("������ ������ ���� = ");
			scanf("%d", &v); 		   //������ ������ ���� �Է¹ޱ�
			for(int i=0;i<v;i++)
				insert_vertex(h);	//�Է¹��� ������ŭ 0~v(�Է¹��� ����-1)(�ִ� 9)���� ������ ������
			break;
		case 'e': case 'E':
			printf("u = ");
			scanf("%d", &u); //������ �� vertex
			printf("v = ");
			scanf("%d", &v); //�Ӹ��� �� vertex
			//������׷����� ����� �� ����
			insert_edge(h,u,v);  //���� ����
			insert_edge(h,v,u);  //������׷����� �ݴ뵵 ����, ����׷����� (u,v)�� ����
			break;
		case 'd': case 'D':
			printf("���̿켱Ž�� ������ ���� v = ");
			scanf("%d", &v);
			dfs(h,v); //���̿켱Ž��
			printf("\n");
			//���̿켱Ž�� �� visitied �迭 �ʱ�ȭ - ���ϸ� ��� Ž�� �Ұ�
			for(int i=0;i<MAX_VERTEX;i++)
				visited[i]=0;
			break;
		case 'b': case 'B':
			printf("�ʺ�켱Ž�� ������ ���� v = ");
			scanf("%d", &v);
			bfs(h,v); //�ʺ�켱Ž��
			printf("\n");
			//�ʺ�켱Ž�� �� visitied �迭 �ʱ�ȭ - ���ϸ� ��� Ž�� �Ұ�
			for(int i=0;i<MAX_VERTEX;i++)
				visited[i]=0;
			break;
		case 'p': case 'P':
			print(h);
			break;
		case 'q': case 'Q':
			freeGraph(h); //�޸� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�߸� �Է� �޾��� ���
			break;
		}

	}while(command != 'q' && command != 'Q');
}

void initialize(Graph **h)
{
	//h�� NULL�� �ƴϸ� freeGraph�� ȣ���� ���� �޸� ����
	if(*h!=NULL)
	{
		freeGraph(*h);
	}

	*h=(Graph*)malloc(sizeof(Graph)); //h�� ����Ű�� ���� �޸� �Ҵ�
	(*h)->Vnum=0; //������ ���� 0���� �ʱ�ȭ
	
	for(int i=0;i<MAX_VERTEX;i++)
	{
		(*h)->list[i]=NULL; //������ ���� ����� �迭 NULL�� �ʱ�ȭ
	}
}

//�׷����� ����(vertex)����
int insert_vertex(Graph* h)
{
	//���� �ִ����� �������� ������ ��� ������ �� �������� ���ϵ��� ����
	if(((h->Vnum)+1)>MAX_VERTEX)
	{
		printf("�ִ� vertex�� ������ �ʰ��߽��ϴ�.\n");
		return 0;	
	}
	//�ִ� ������ �ȳѴ´ٸ� ���� ���� �ϳ� �� ������Ŵ
	h->Vnum++;
}

//�׷����� ����(u,v)����
int insert_edge(Graph* h,int u, int v)
{		
	if(u==v)
	{
		printf("self loop �Ұ�\n");
		return 0;
	}
	//������ ���� �� ���� ����� ���� (u�̳� v�� ��ȣ�� ���� ������ �������� ũ�ų� ���ٸ�)
	if((u>=h->Vnum)||(v>=h->Vnum)) //������ �� �ȵ�? : �迭���ݾ� �ε���-1 ��ŭ�� ���ϱ�
	{
		printf("���� ��ȣ�� Ʋ�Ƚ��ϴ�.\n");
		return 0;
	}

	/*
	* Ž���� ��, ���� ���� �߿� ��ȣ�� ���� �������� Ž���ϱ� ���ؼ���
	* ��������Ʈ�� ����� ��带 ������������ �־�����Ѵ�
	*/
	listnode* u_node=(listnode*)malloc(sizeof(listnode));
	u_node=h->list[u]; //list[u]�� ������ ó���̸� NULL��
	listnode* u_node_trail=(listnode*)malloc(sizeof(listnode));
	u_node_trail=h->list[u]; //u_node�� ����Ű�� ���� ���
	listnode* v_node=(listnode*)malloc(sizeof(listnode)); //����� ����
	v_node->vertex=v; //�� ��尡 ���� ������ ���� v�� ����
	
	//������������ ��������Ʈ ����� ���� ����
	while(1)
	{
		//h->list[u] ������ ������ ó���� ���
		if(h->list[u]==NULL)
		{
			//�� ó����(�迭��)v_node�� �߰� (u_node�� h->list[u])
			v_node->link=h->list[u];
			h->list[u]=v_node;
			return 0;
		}
		//v_node�� ������ u_node�� �������� ���� ��� ��������Ʈ�� ����
		else if(v_node->vertex<u_node->vertex)
		{
			//���ڰ� �� ó��(�迭)�� �����ϴ� ��� (���� ���� ������ ���)
			if(u_node==h->list[u])
			{
				v_node->link=h->list[u];
				h->list[u]=v_node;
			}
			//�߰��� ���
			else
			{
				v_node->link=u_node;
				u_node_trail->link=v_node;
			}
			return 0;
		}
		//�̹� �����ϴ� �����̶��
		else if(v_node->vertex==u_node->vertex)
		{
			printf("�̹� �����ϴ� �����Դϴ�.\n");
			return 0;
		}
		u_node_trail=u_node;
		u_node=u_node->link;
		
		/*
		* ���⼭ ������ ��带 �˻��ϴ� ����
		* 1) while(u_node!=NULL)�� �� �� ���� : ���ʿ� �ʱ�ȭ�� h->list[u]�� ù ������ ��� NULL�̾ ���۵� ���ϰ� ����������
		* 2) �߰��κп��� ���ϴ� ������ u_node�� NULL�ε� ->vertex�� ���� �� ������ �� ������ Ȯ���ϴ� �� ���ǹ��ϴ�
		*/
		if(u_node==NULL) //������ ������ �Դٸ�
		{
			v_node->link=u_node;
			u_node_trail->link=v_node;
			return 0;
		}
	}
}

//�׷��� ��������Ʈ ���
int print(Graph* h)
{
	for(int i=0;i<h->Vnum;i++)
	{
		listnode* n=h->list[i];
		printf("���� %d�� ���� ����Ʈ : ",i);
		while(n!=NULL)
		{
			printf("[%d] ",n->vertex);
			n=n->link;
		}
		printf("\n");
	}
}

//�׷��� �����Ҵ� ����
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

//���� v���� �����ϴ� ���̿켱Ž��
void dfs(Graph*h,int v)
{
	listnode* w;
	visited[v]=1; //���� v�� �湮�ϸ� 1�� �־� '�湮����'�� ǥ��
	printf("%5d",v); //�湮�� ���� ������� ��µǵ��� ��
	for(w=h->list[v];w;w=w->link)
	{
		/*�ϳ��� ������ ���� ������ ��������Ʈ�� ��� ó���ϵ�,
		* �̹� �湮�� ����(visited[v]���� 1)�� �����ϰ� �湮���� ���� ����(visited[v]���� 0)�� �湮�� ����*/
		if(!visited[w->vertex])
			dfs(h,w->vertex);
	}
}

//���� v���� �����ϴ� �ʺ� �켱 Ž��
void bfs(Graph* h,int v)
{
	listnode *w;
	Q q;
	init(&q);    		 //ť �ʱ�ȭ 
	visited[v] = 1;      //���� v�� �湮�ϸ� 1�� �־� '�湮����'�� ǥ��
	printf("%5d", v);    //�湮�� ���� ������� ��µǵ��� ��
	enqueue(&q, v);		 //���������� ť�� ���� 

	while (!is_empty(&q)) {
		v = dequeue(&q);		// ť�� ����� ���� ���� 
		for(w=h->list[v];w;w=w->link)
		{
			if (!visited[w->vertex]) 
			{ 
				visited[w->vertex] = 1;   //�湮 ǥ��
				printf("%5d", w->vertex);
				enqueue(&q, w->vertex);	  //������ ť�� ����
			}
		}
	}
}

// �ʱ�ȭ �Լ�
void init(Q *q)
{
	q->first = q->last = 0;
}

// ���� ���� ���� �Լ�
int is_empty(Q *q)
{
	if(q->first == q->last) return 1;
	else return 0;
}

// ��ȭ ���� ���� �Լ�
int is_full(Q *q)
{
	if((q->last + 1) % MAX_QUEUE_SIZE == q->first) return 1;
	else return 0;
}

// ���� �Լ�
void enqueue(Q *q, int item)
{
	if (is_full(q))
		printf("ť�� ��ȭ�����Դϴ�\n");
	q->last = (q->last + 1) % MAX_QUEUE_SIZE; //���� �� �� ĭ ������ ���� ����
	q->queue[q->last] = item;
}

// ���� �Լ�
int dequeue(Q *q)
{
	if (is_empty(q))
		printf("ť�� ��������Դϴ�\n");
	q->first = (q->first + 1) % MAX_QUEUE_SIZE; //�� ĭ ������ ���� �ش� ���� ����
	return q->queue[q->first];
}