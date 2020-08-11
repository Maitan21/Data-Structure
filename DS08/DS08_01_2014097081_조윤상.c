/*  DS08_01_2014097081_������.c
author : ������
Date : 2018.10.8
Description : 2���� linked list �ۼ� �� concatenate(ü�ο���) �� invert (��) ���� ����
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

Node *head = NULL; // ù ��ũ ���
Node *Head = NULL; // �ι�° ��ũ ���
node *ptr1 = NULL; // linked list 1�� ���� �κ� 
node *ptr2 = NULL; // linked list 2�� �Ӹ� �κ�

void open(); //����� �Լ�
void Linked_List_First(); // ù ��ũ�� ����Ʈ
void Linked_List_Second(); // �ι�° ��ũ�� ����Ʈ
void print(Node *head);  // ��� �Լ�
void concatenate(struct node *ptr1, struct node *ptr2); //ü�� ���� �Լ�
void invert(struct node **head); // �� �Լ�

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
	ptr1 = link; //���� �κ� ������ ����

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
	ptr2 = link2; //���κ� ������ ����
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