/*
Description : 히프(HEAP) 이해하기 --> 최대 히프(MAX_HEAP)에서의 삽입과 삭제, 스택으로 중위 순회
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 20
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

int Temp[MAX_ELEMENTS];
typedef struct ek {
	int key;
}element;

element heap[MAX_ELEMENTS];
int stack[MAX_ELEMENTS];

void push(element);
element pop(element[]);
void open();
void print(int);
void iterinorder(); // 스택을 이용한 inorder
					// void iterinorder_r(); /*재귀를 이용한 inorder*/
int count = 1; // heap 1부터 시작
int n = 0;

int main()
{
	open();

	printf("Level Order : "); print(count);
	printf("\n");
	printf("Inorder     : "); iterinorder(); //iterinorder_r();
	printf("\n");
	pop(heap); count--;
	printf("Level Order : "); print(count);
	printf("\n");
	printf("Inorder     : "); iterinorder(); //iterinorder_r();
	printf("\n");
	pop(heap); count--;
	printf("Level Order : "); print(count);
	printf("\n");
	printf("Inorder     : "); iterinorder(); //iterinorder_r();
	printf("\n");
	return 0;
}

void open()
{

	FILE *fp = fopen("input.txt", "r");
	if (fp != NULL)
	{
		while ((fscanf(fp, "%2d", &Temp[count])) != EOF)
			count++;
	}
	element item;
	for (int i = 1; i < count; i++) {
		item.key = Temp[i];
		push(item);
	}
}

void push(element item)
{
	int i;
	if (HEAP_FULL(n)) {
		fprintf(stderr, "The heap is full\n");
		exit(EXIT_FAILURE);
	}
	i = ++n;
	while ((i != 1) && (item.key > heap[i / 2].key)) { //부모랑 비교후 
		heap[i] = heap[i / 2]; // 자식이 큰경우 부모랑 자식 바꿈
		i /= 2; // 자식이였던 자리로 위치 이동
	}
	heap[i] = item; //비교 완료 후 자기 자리 이동
}

element pop(element heap[])
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(n)) {
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(n)--];
	parent = 1;
	child = 2;
	while (child <= n) {
		if ((child < n) && heap[child].key < heap[child + 1].key) //현재부모보다 큰 자식 탐색
			child++; //위로 올려줌 (root로 이동)
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];  //내려가면서 자기위치로
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void print(int n)
{
	int i;
	for (i = 1; i < n; i++)
		printf("%2d ", heap[i].key);
}

void iterinorder()
{
	int i = 1;
	int top = -1;
	while (1) {
		while (count > i) {
			top++;
			stack[top] = i;
			i = i * 2;
		}
		if (top == -1)
			return;
		i = stack[top];
		top--;
		printf("%2d ", heap[i].key);
		i = i * 2 + 1;
	}
}
/*   재귀 이용시
void iterinorder_r()
{
int i=1;
if (i <= 0 || count - 1<i)
return;

iterinorder_r(2 * i); // 왼쪽 자식
if (heap[i].key != 0)
printf("%2d ", heap[i].key);
iterinorder_r(2 * i + 1); //오른쪽 자식
}
*/