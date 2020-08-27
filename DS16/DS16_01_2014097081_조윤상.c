/* 
Description : 최단 경로 중 dijkstra 알고리즘 
*/
#include <stdio.h>
#include <stdlib.h>

#define INF 999999999 //무한대값

void open();
int choose();
void dijkstra(int);

int N, S;
int **matric;
int *distance;
short int *found; //최단 거리 집합

int main()
{
	open();
	distance = (int*)malloc(sizeof(int)*N);
	found = (short int*)malloc(sizeof(short int)*N);
	// 인접행렬에서 대각선을 제외한 값을 무한대로 설정
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (i != j && matric[i][j] == 0)
				matric[i][j] = INF;
			
	dijkstra(S);

	for (int i = 0; i < N; i++)
	{
		printf("%d ", distance[i]);
	}
	printf("\n");

	free(distance);
	free(found);
	free(*matric);
	return 0;
}

void open()
{
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &N, &S);

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

int choose()
{
	int min = INF;
	int index = -1;
	for (int i = 0; i < N; i++)
	{
		if (distance[i] < min && !found[i])
		{
			min = distance[i];
			index = i;
		}
	}
	return index;
}

void dijkstra(int start)
{
	for (int i = 0; i < N; i++) //초기값 설정
	{
		found[i] = false;
		distance[i] = matric[start][i]; //출발 정점을 제외한 모든 정점으로 부터의 거리의 초기값
	}
	found[start] = true; 
	for (int i = 0; i < N - 2; i++)
	{
		int current = choose(); // found 못한 곳에서 가장 작은 값을 가져옴
		found[current] = true;
		for (int j = 0; j < N; j++) //N 까지 가리키는 길을 계산
			if (!found[j])
				if (distance[current] + matric[current][j] < distance[j]) //기존 값과 j를 거쳐서 가는 값을 비교
				{
					distance[j] = distance[current] + matric[current][j];
				}
	}
}