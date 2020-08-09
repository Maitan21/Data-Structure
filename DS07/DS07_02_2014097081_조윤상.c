/*/*  DS07_02_2014097081_조윤상.c
author : 조윤상
Date : 2018.10.8
Description : postfix(후위 표기식) 계산
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

void open() // 파일 읽기
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
precedence gettoken(char *symbol, int *n) /* 스트링으로부터 토큰을 얻기 위함 */
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
	default: return operand; /* 에러 검사는 하지 않고 기본 값은 피연산자 */
	}
}

int eval(void)
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; /* 수식 스트링을 위한 카운터 */

	token = gettoken(&symbol, &n);

	while (token != eos)
	{
		if (token == operand)
			push(&top, symbol - '0'); /* 스택 삽입 -->피연산자(symbol)은 초기에는 하나의 문자이므로 한자리 정수로 변환시켜야 한다.*/
		else
		{
			op2 = pop(&top); /*스택 삭제*/
			op1 = pop(&top);

			switch (token) /*토큰 연산 실행*/
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
	return pop(&top); /*결과를 반환*/
}

int main(void)
{
	open();
	printf("Result : %d\n", eval());
}
