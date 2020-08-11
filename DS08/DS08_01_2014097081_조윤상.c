/*  DS08_01_2014097081_조윤상.c
author : 조윤상
Date : 2018.10.8
Description : 2개의 linked list 작성 후 concatenate(체인연결) 과 invert (역) 연산 실행
*/
#include<stdio.h> 
#include<stdlib.h> 

#define BUFFER_SIZE 6

typedef struct node {
	int data;
	struct node* next;
};
typedef struct node Node;

int temp[BUFFER_SIZE];

Node *head = NULL; // 첫 링크 헤더
Node *Head = NULL; // 두번째 링크 헤더
node *ptr1 = NULL; // linked list 1의 꼬리 부분 
node *ptr2 = NULL; // linked list 2의 머리 부분

void open(); //입출력 함수
void Linked_List_First(); // 첫 링크드 리스트
void Linked_List_Second(); // 두번째 링크드 리스트
void print(Node *head);  // 출력 함수
void concatenate(struct node *ptr1, struct node *ptr2); //체인 연결 함수
void invert(struct node **head); // 역 함수

int main(void)
{
	open();
	Linked_List_First();
	Linked_List_Second();
	printf("First : \n");
	print(head);
	printf("Second : \n");
	print(Head);
	concatenate(ptr1, ptr2);
	printf("Concatenate : \n");
	print(head);
	invert(&head);
	printf("Invert : \n");
	print(head);
}
void open()
{
	int n = 0;
	FILE *fp = fopen("input1.txt", "r");
	FILE *fps = fopen("input2.txt", "r");
	if (fp != NULL) {

		while ((fscanf(fp, "%d", &temp[n]) != EOF)) {
			n++;
		}
		while ((fscanf(fps, "%d", &temp[n]) != EOF)) {
			n++;
		}
	}
	fclose(fp);
}
void Linked_List_First()
{
	head = (Node *)malloc(sizeof(Node));
	head->data = temp[1];
	head->next = NULL;

	Node *link = (Node *)malloc(sizeof(Node));

	link->data = temp[2];
	link->next = NULL;
	head->next = link;
	ptr1 = link; //꼬리 부분 포인터 저장

	link = (node *)malloc(sizeof(node));
	link->data = temp[0];
	link->next = head;
	head = link;

}
void Linked_List_Second()
{

	Head = (Node *)malloc(sizeof(Node));
	Head->data = temp[4];
	Head->next = NULL;

	Node *link2 = (Node *)malloc(sizeof(Node));

	link2->data = temp[5];
	link2->next = NULL;
	Head->next = link2;

	link2 = (node *)malloc(sizeof(node));
	link2->data = temp[3];
	link2->next = Head;
	Head = link2;
	ptr2 = link2; //헤드부분 포인터 저장
}
void print(Node *head)
{
	Node *address = head;
	while (address != NULL) {
		printf("(%p , %d, %p) ", address, address->data, address->next);
		address = address->next;
	}
	printf("\n\n");
}

void concatenate(struct node *ptr1, struct node *ptr2)
{
	if (ptr1->next == NULL)
		ptr1->next = ptr2;
	else
		concatenate(ptr1->next, ptr2);
}

void invert(struct node **head)
{
	struct node *p, *q, *r;

	p = q = r = *head;
	p = p->next->next;
	q = q->next;
	r->next = NULL;
	q->next = r;

	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	*head = q;
}