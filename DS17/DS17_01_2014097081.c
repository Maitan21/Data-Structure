/* 
Description : transitive closure matrix(A+) 와  reflexive transitive closure matrix(A*) 구현
*/
#include <stdio.h>
#include <stdlib.h>

int N;
void open();

int **matric;
int **closure;
int **temp;
void transitive();
void print();

int main(void)
{
	open();

	for (int i = 0; i < N; i++)
		transitive(); //transitive closure

	print(); //출력

	for (int i = 0; i < N; i++)  // 동적할당 해체
	{
		free(temp[i]);
		free(matric[i]);
		free(closure[i]);
	}
	free(temp);
	free(matric);
	free(closure);

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

void transitive()
{
	int i, j, k;

	closure = (int**)malloc(sizeof(int*)*N);        //closure[i][k]
	for (j = 0; j<N; j++)
		closure[j] = (int*)malloc(sizeof(int)*N);      

	temp = (int**)malloc(sizeof(int*)*N);           //교집합을 임시저장
	for (j = 0; j<N; j++)
		temp[j] = (int*)malloc(sizeof(int)*N);        


	for (i = 0; i<N; i++)
		for (j = 0; j<N; j++)
		{
			closure[i][j] = matric[i][j];            //array배열의 요소들을 closure배열에 저장
		}

	for (k = 0; k<N; k++)
		for (i = 0; i<N; i++)
			for (j = 0; j < N; j++)
			{
				//교집합을 먼저 계산해준다.
				if (closure[i][k] == 1 && closure[k][j] == 1) temp[i][j] = 1;   //둘다 1이면 temp도 1
				else temp[i][j] = 0;                              //그 외의 경우는 0

																  //합집합 계산
				if (closure[i][j] == 0 && temp[i][j] == 0)   closure[i][j] = 0;//둘다 0이면 0
				else closure[i][j] = 1;                           //그 외의 경우는 1
			}
}

void print()
{
	printf("A+:\n");   //transitive closure matrix(A+)
	for (int i = 0; i<N; i++)
		for (int j = 0; j<N; j++)
		{
			printf("%d ", closure[i][j]);
			if (j == N - 1) printf("\n");
		}
	printf("\n"); 
	printf("A*:\n"); //reflexive transitive closure matrix(A*)
	for (int i = 0; i<N; i++)
		for (int j = 0; j<N; j++)
		{
			if (i == j && closure[i][j] == 0) closure[i][j] = 1; // 대각선 1로 채우기
			printf("%d ", closure[i][j]);
			if (j == N - 1) printf("\n");
		}
}