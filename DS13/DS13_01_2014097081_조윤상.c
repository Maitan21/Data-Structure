/*
Description : Array Representation을 이용하여 Equivalence Class를 구하는 프로그램을 작성
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 24

void open();
int Find(int);
void Union(int, int);
void print(int);

int *parent;
int count[MAX_BUFFER] = { 0 };
int N, a, b;

int main()
{
	int cnt = 0;
	open();

	for (int i = 0; i < N; i++) { // root 인 녀석 카운트
		if (parent[i]<0)
		{
			cnt++;
			count[i]++; //루트 인 각 인자 체크
		}
	}
	printf("%d\n", cnt);
	for (int i = 0; i < N; i++) //체크 된 루트경우만 출력
		if(count[i]>0)
			print(i);
	
	free(parent);
	return 0;
}
void open()
{
	int K;
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &N, &K);
	parent = (int*)malloc(sizeof(int) * N);
	int i = 0, j = 0;
	for (int cnt = 0; cnt < N; cnt++) {
		parent[cnt] = -1;
	}
	
	while (K>0) {
		K--;
		fscanf(fp, "%d %d", &a, &b);
		int x = Find(a);
		int y = Find(b);
			Union(x, y);
	}
	fclose(fp);
}
int Find(int i)
{
	int root, trail, lead;
	for (root = i; parent[root] >= 0; root = parent[root]);
	for (trail = i; trail != root; trail = lead) {
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;
}
void  Union(int i, int j)
{
	int temp = parent[i] + parent[j];

	if (parent[i] > parent[j])
	{
		parent[i] = j;
		parent[j] = temp;
	}
	else
	{
		parent[j] = i;
		parent[i] = temp;
	}
}

void print(int find)
{
	printf("{ ");
	for (int i = 0; i < N; i++) {
		if (Find(find) == Find(i))
			printf("%d ", i);
	}
	printf("}\n");	
}