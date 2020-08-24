/* DS15_01_2014097081_조윤상.c
author : 조윤상
Date : 2018.11.12
Description : Kruskal 알고리즘 -> 가중치가 작은 것 부터 간선을 추가하여 연결시킨다.
              단, Union - Find를 통해 사이클을 이루지 않도록 한다.
*/
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

typedef struct
{
	int v1; //정점 1
	int v2; //정점 2
	int weight; //간선의 가중치
}element;

typedef struct
{
	element heap[BUFFER_SIZE]; //최소히프
	int heap_size;
}HeapType;

void open();
void InsertHeap(HeapType *, element);
void InsertEdge(HeapType *, int, int, int);
element DeleteHeap(HeapType *);
void InitHeap(HeapType *);
int find(int);
void Union(int, int);
int kruskal();

int N;
int *parent;
int *num;
int **matric;

int main()
{
	open();

	parent = (int*)malloc(sizeof(int) * N);
	num = (int*)malloc(sizeof(int) * N);

	kruskal();

	free(matric);
	free(parent);
	free(num);
	return 0;
}

void open()
{
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);

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

void InsertHeap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);
	while (i != 1 && item.weight<h->heap[i / 2].weight) //부모 노드와 비교
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; //최소 히프 생성
}

element DeleteHeap(HeapType *h)
{ 
	int parent = 1, child = 2;

	element data, temp;

	data = h->heap[parent];
	temp = h->heap[(h->heap_size)--]; //삭제에 의한 size 감소

	while (child <= h->heap_size)
	{
		// 자식 노드간 작은 수 비교
		if ((child<h->heap_size) && (h->heap[child].weight)>h->heap[child + 1].weight)
			child++;

		if (temp.weight <= h->heap[child].weight)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2; // 다음 자식 노드와 비교
	}
	h->heap[parent] = temp;
	return data;
}

int find(int v)
{
	int i, p, temp;

	for (i = v; (p = parent[i]) >= 0; i = p); //정점v의 루트를 찾는다.
	temp = i;
	for (i = v; (p = parent[i]) >= 0; i = p)
		parent[i] = temp; // 집합의 모든 원소들의 부모를 s로 설정
	return temp;
}

void Union(int v1, int v2)
{
	if (num[v1] < num[v2]) //자식의 개수로 비교
	{
		parent[v1] = v2; // 부모 변경
		num[v1] += num[v2];
	}
	else
	{
		parent[v2] = v1; // 부모 변경
		num[v2] += num[v1];
	}
}

void InsertEdge(HeapType *h, int i, int j, int weight)
{
	element node;

	node.v1 = i;
	node.v2 = j;
	node.weight = weight;
	InsertHeap(h, node);
}

int kruskal()
{
	element e;
	HeapType h;

	InitHeap(&h);
	for (int i = 0; i<N; i++)
	{
		parent[i] = -1;
		num[i] = 1;
	}
	int Vertex1, Vertex2, edgeCount = 0, sum = 0;

	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (matric[i][j] > 0)
			{
				InsertEdge(&h, i, j, matric[i][j]);
			}
	while (edgeCount<N - 1) // 간선의 개수가 N-1이 될 때 까지
	{
		e = DeleteHeap(&h); //최소 힙
							// 가중치가 가장 낮은 간선을 선택
		Vertex1 = find(e.v1);
		Vertex2 = find(e.v2);
		if (Vertex1 != Vertex2) // 서로의 대표 원소가 같지 않은 경우에만
		{
			printf("(%d, %d) ", e.v1, e.v2, e.weight);
			sum += e.weight;
			edgeCount++; // 간선을 하나 늘린다.	
			Union(Vertex1, Vertex2); 
		}
	}
	printf("\n");
	printf("Cost : %d \n", sum);

	return 0;
}
void InitHeap(HeapType *h) //히프 초기화
{
	h->heap_size = 0;
}
