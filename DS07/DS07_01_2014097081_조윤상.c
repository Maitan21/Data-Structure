/*/*  DS07_02_2014097081_������.c
author : ������
Date : 2018.10.8
Description : Infix notation ���� �Է¹޾� Postfix notation���� ��ȯ�ϴ� ���α׷� ����
*/
#include<stdio.h> 
#include<stdlib.h> 

#define MAX_STACK_SIZE 100 
#define BUFFER_SIZE 100 

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

int stack[MAX_STACK_SIZE];
char postfix[BUFFER_SIZE];
int top = -1;

void open() // ���� �б�
{
	FILE *fp = fopen("input.txt", "r");
	if (fp != NULL)
	{
		fgets(postfix, MAX_STACK_SIZE, fp);
	}
	fclose(fp);
}

void push(int *top, int item)
{
	if (*top >= MAX_STACK_SIZE - 1)
		printf("Error: Stack is full\n");
	stack[++*top] = item;
}
int pop(int *top)
{
	if (*top == -1)
		printf("Error: Stack is empty\n");
	return stack[(*top)--];
}
int gettoken(char *symbol, int *n) /* ��Ʈ�����κ��� ��ū�� ��� ���� */
{
	*symbol = postfix[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case 0: return eos;
	default: return operand; /* ���� �˻�� ���� �ʰ� �⺻ ���� �ǿ����� */
	}
}
void printToken(int p) /* ���� ��� */
{
	switch (p)
	{
	case lparen: printf("("); break;
	case rparen: printf(")"); break;
	case plus: printf("+"); break;
	case minus: printf("-"); break;
	case times: printf("*"); break;
	case divide: printf("/"); break;
	case mod: printf("%"); break;
	case eos: printf(" "); break;
	default: break;
	}
}
void Postfix(void) /*������ ���� ǥ������� ���*/
{
	char symbol;
	int token;
	int n = 0;
	int  top = 0; /*eos�� ���ÿ� ����*/
	stack[0] = eos;
	token = gettoken(&symbol, &n);
	for (; token != eos; token = gettoken(&symbol, &n))
	{
		if (token == operand) /* ��ū�� �� ������ �϶�*/
			printf("%c", symbol);
		else if (token == rparen) /*���� ��ȣ�� ���� ������ ��ū���� �����ؼ� ��½�Ŵ*/
		{
			while (stack[top] != lparen)
				printToken(pop(&top));
			pop(&top); /*���� ��ȣ�� ������.*/
		}
		else
		{
			while (isp[stack[top]] >= icp[token]) /*���ÿ� �ִ� �������� �켱������ ������ �������� �켱�������� ���ų� ������ pop()*/
				printToken(pop(&top));
			push(&top, token); /* ������ ������ */
		}
	}
	while ((token = pop(&top)) != eos)
		printToken(token);
	printf("\n");
}

int main(void)
{
	open();
	Postfix();
}
