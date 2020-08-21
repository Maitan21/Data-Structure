/* 
Description : BFS, DFS의 이해
*/
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0;
#define TRUE 1;
#define BUFFER_SIZE 100

int N;

typedef struct graphNode
{ // 그래프에 대한 인접 리스트의 노드 구조 정의
	int vertex;
	struct graphNode* link;
}graphNode;

graphNode **adjList;

int *queue;
int rear = -1, front = -1;
int visited[BUFFER_SIZE];
void open();

void insertEdge(int u, int v);
void print_adjList();

void dfs(int);

void addq(int *rear, int vertex);
int deleteq(int *front);
void bfs(int);


int **matric;


int main()
{

	open();
	adjList = (graphNode**)malloc(sizeof(graphNode)*N);
	queue = (int*)malloc(sizeof(int)*N);

	for (int i = 0; i<N; i++)
	{
		visited[i] = FALSE;
		adjList[i] = NULL;
	}

	for (int i = N - 1; i >= 0; i--)
		for (int j = N - 1; j >= 0; j--)
			if (matric[i][j] > 0)
				insertEdge(i, j);

	print_adjList();
	printf("BFS : ");
	bfs(0);
	printf("\n");

	for (int i = 0; i < N; i++)
		visited[i] = FALSE; //visited 초기화

	printf("DFS : ");
	dfs(0);
	printf("\n");

	return 0;
}

void open()
{
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);
	//RUN 2차원 배열 
	matric = (int**)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++)
		matric[i] = (int*)malloc(sizeof(int*) * N);

	int i = 0, j = 0;
	int item;

	while (fscanf(fp, "%d", &item) != EOF)
	{
		matric[i][j] = item;
		j++;
		if (j == N)
		{
			i++;
			j = 0;
		}
	}
	fclose(fp);
}

void insertEdge(int u, int v)
{ //엣지 추가
	graphNode* node;
	node = (graphNode *)malloc(sizeof(graphNode));
	node->vertex = u;
	node->link = adjList[v];
	adjList[v] = node;
}

void print_adjList()
{ //인접리스트 출력
	int i;
	graphNode* p;
	for (i = 0; i<N; i++)
	{
		printf("Vertex %d : ", i);
		p = adjList[i];
		while (p)
		{
			printf("%d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

void dfs(int v)
{
	graphNode * w;
	visited[v] = TRUE;
	printf("%d ", v);
	for (w = adjList[v]; w; w = w->link)
		if (!visited[w->vertex])
			dfs(w->vertex);
}
void bfs(int v)
{
	graphNode *w;
	int front, rear;
	front = rear = -1;
	printf("%d ", v);
	visited[v] = TRUE;
	addq(&rear, v);
	while (front != rear)
	{
		v = deleteq(&front);

		for (w = adjList[v]; w; w = w->link)
		{
			if (!visited[w->vertex])
			{
				printf("%d ", w->vertex);
				addq(&rear, w->vertex);
				visited[w->vertex] = TRUE;
			}
		}
	}
}

void addq(int *rear, int vertex) //큐 
{
	*rear = (*rear) % N;
	queue[++(*rear)] = vertex;
}
int deleteq(int *front)
{
	return queue[++(*front) % N];
}