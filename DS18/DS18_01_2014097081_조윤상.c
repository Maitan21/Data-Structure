/* DS18_01_2014097081_������.c
author : ������
Date : 2018.11.21
Description : AOV �˰���
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
}node;

typedef struct {
	int count;
	nodePointer link;
}hdnodes;

hdnodes *graph;

int N; // ������ ����
int **matric;

void open();
void Add(int, int);
void topSort();
void Init();
int main()
{
	open();
	graph = (hdnodes*)malloc(sizeof(hdnodes)*N); 
	Init(); //�ʱ�ȭ
	for (int i = 0; i<N; i++)
		for (int j = 0; j < N; j++)
		{
			if (matric[i][j] > 0)
				Add(i, j);
		}
	topSort();

	
	return 0;
}

void open()
{
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);

	matric = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++)
		matric[i] = (int*)malloc(sizeof(int) * N);

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

void topSort()
{
	int i, j, k, top;
	nodePointer ptr;
	// �����ڰ� ���� vertices �� ������ �����.
	top = -1;
	for (i = 0; i < N; i++)
		if (!graph[i].count) {
			graph[i].count = top;
			top = i;
		}
	for (i = 0; i < N; i++)
		if (top == -1) { // ��� ������ ������ ���� ->  retrun;
			fprintf(stderr, "\nNetwork has a cycle. Sort terminated.\n");
			exit(EXIT_FAILURE);
		}
		else { //�����ڰ� ���� ���� v�� ����
			j = top;
			top = graph[top].count;
			printf("%d ", j);
			for (ptr = graph[j].link; ptr; ptr = ptr->link) {
				k = ptr->vertex;
				graph[k].count--;
				if (!graph[k].count) {
					graph[k].count = top;
					top = k;
				}
			}
		}
		printf("\n");
}

void Add(int src, int dest)
{
	node* newNode = (node*)malloc(sizeof(node)*N); //node �߰�
	node* temp = graph[src].link;

	newNode->vertex = dest;
	graph[dest].count++;
	newNode->link = NULL; 
	if (temp == NULL) {
		graph[src].link = newNode;
	}
	else {
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = newNode;
	}
}

void Init() 
{
	int i;
	for (i = 0; i < N; i++) {
		graph[i].count = 0;
		graph[i].link = NULL;
	}
}