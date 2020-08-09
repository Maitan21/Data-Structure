/*/*  DS07_02_2014097081_������.c
author : ������
Date : 2018.10.8
Description : postfix(���� ǥ���) ���
*/
#include<stdio.h> 
#include<stdlib.h> 

#define MAX_STACK_SIZE 100 
#define BUFFER_SIZE 100 

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

int stack[MAX_STACK_SIZE];
char postfix[BUFFER_SIZE];
int top = -1;

void open() // ���� �б�
{
	FILE *fp = fopen("input1.txt", "r");
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
precedence gettoken(char *symbol, int *n) /* ��Ʈ�����κ��� ��ū�� ��� ���� */
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

int eval(void)
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; /* ���� ��Ʈ���� ���� ī���� */

	token = gettoken(&symbol, &n);

	while (token != eos)
	{
		if (token == operand)
			push(&top, symbol - '0'); /* ���� ���� -->�ǿ�����(symbol)�� �ʱ⿡�� �ϳ��� �����̹Ƿ� ���ڸ� ������ ��ȯ���Ѿ� �Ѵ�.*/
		else
		{
			op2 = pop(&top); /*���� ����*/
			op1 = pop(&top);

			switch (token) /*��ū ���� ����*/
			{
			case plus: push(&top, op1 + op2);
				break;
			case minus: push(&top, op1 - op2);
				break;
			case times: push(&top, op1*op2);
				break;
			case divide: push(&top, op1 / op2);
				break;
			case mod: push(&top, op1%op2);
			}
		}
		token = gettoken(&symbol, &n);
	}
	return pop(&top); /*����� ��ȯ*/
}

int main(void)
{
	open();
	printf("Result : %d\n", eval());
}
