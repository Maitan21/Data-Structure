/*
Description : 선택 트리의 Winner tree를 구현하기. 그리고 빠진 자리에 Restructuring 하여 다시 Winner Tree 수행
*/
#include <stdio.h>
#include <stdlib.h>


#define MAX_BUFFER 8
int TEMP[MAX_BUFFER][MAX_BUFFER];
int stack[MAX_BUFFER];
int run = 0;
int cnt = 0;
typedef struct R_NODE* RUN_NODE;
typedef struct R_NODE //RUN의 노드
{
	int key; //다른 필드 
}R_NODE;

typedef struct S_NODE* SELECT_NODE; //WiNNER의 노드
typedef struct S_NODE
{
	int key;
	short run_number; //해당 키가 속하는 run의 번호.
	short index; //해당 키가 속하는 run의 record index
}S_NODE;

void Winner_tree(R_NODE **RUN, int nRUN);
void open();
void print(int n);
void iterinorder();
void Restructuring(R_NODE **RUN, int nRUN);
SELECT_NODE selcTree;

int main()
{
	open();
	R_NODE **RUN; //RUN 2차원 배열 
	RUN = (R_NODE**)malloc(sizeof(R_NODE*) * MAX_BUFFER);
	for (int i = 0; i < MAX_BUFFER; i++)
		RUN[i] = (R_NODE*)malloc(sizeof(R_NODE*) * MAX_BUFFER);

	for (int i = 0; i < run; i++)
		for (int j = 0; j < cnt; j++)
			RUN[i][j].key = TEMP[i][j];

	Winner_tree(RUN, cnt);

	printf("Level Order : ");
	print(run);
	printf("\nInorder  :    ");
	iterinorder();
	printf("\n");

	Restructuring(RUN, cnt); //빠진 자리 채워넣기

	printf("Level Order : ");
	print(run);
	printf("\nInorder  :    ");
	iterinorder();
	printf("\n");
	free(RUN); //메모리 해제

	return 0;
}
void open()
{
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &run);

	int i = 0, j = 0;
	int item;
	while (fscanf(fp, "%d", &item) != EOF)
	{
		TEMP[i][j] = item;
		j++;
		if (item == -1)
		{
			i++;
			if (cnt < j) cnt = j;
			j = 0;
		}
	}
}

void Winner_tree(R_NODE **RUN, int nRun)
{
	// selection tree pointer
	int i, j;
	int compare; // 그 level의 비교 횟수

	selcTree = (SELECT_NODE)malloc(sizeof(S_NODE)*run * 2);


	for (i = 0; i<run; i++) //배열 초기화 작업
	{
		selcTree[i + run].index = 0;
		selcTree[i + run].run_number = i;
		selcTree[i + run].key = RUN[i][selcTree[i + run].index].key;
	}

	i = run;
	compare = run / 2;

	while (i>1)
	{
		for (j = 0; j<compare; j++)
		{
			selcTree[i / 2] = ((selcTree[i].key<selcTree[i + 1].key) ? selcTree[i] : selcTree[i + 1]);
			i += 2;  // 작은것(승자)이 부모로
		}
		i = compare;
		compare /= 2;
	}
	printf("Winner  :     %3d \n", selcTree[1].key);
}

void iterinorder()
{
	int i = 1;
	int top = -1;
	while (1) {
		while (run * 2 > i) {
			top++;
			stack[top] = i;
			i = i * 2;
		}
		if (top == -1)
			return;
		i = stack[top];
		top--;
		printf("%3d ", selcTree[i].key);
		i = i * 2 + 1;
	}
}
void print(int n)
{
	int i;
	for (i = 1; i < n * 2; i++)
		printf("%3d ", selcTree[i].key);
}
void Restructuring(R_NODE **RUN, int nRun)
{
	int i, j;
	int compare; // 그 level의 비교 횟수
	SELECT_NODE winner;
	i = run;
	compare = run / 2;

	winner = selcTree + 1;
	if (winner->index<run - 1)
	{
		// key 값 복사
		selcTree[run + winner->run_number].key =
			RUN[winner->run_number][(winner->index) + 1].key;
		++(selcTree[run + winner->run_number].index); // 승자가 속한 런내의 인덱스포인터 증가
	}
	else //런내의 레코드가 남아 있지 않을 경우
	{
		// 최댓값으로 리셋
		selcTree[run + winner->run_number].key = INT_MAX;
		--nRun;
	}
	while (i>1)
	{
		for (j = 0; j<compare; j++)
		{
			selcTree[i / 2] = ((selcTree[i].key<selcTree[i + 1].key) ? selcTree[i] : selcTree[i + 1]);
			i += 2;
		}
		i = compare;
		compare /= 2;
	}
	printf("Winner  :     %3d \n", selcTree[1].key);
}

