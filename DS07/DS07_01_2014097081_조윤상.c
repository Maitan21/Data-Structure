/*/*  DS07_02_2014097081_조윤상.c
author : 조윤상
Date : 2018.10.8
Description : Infix notation 식을 입력받아 Postfix notation으로 변환하는 프로그램 구현
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

void open() // 파일 읽기
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
int gettoken(char *symbol, int *n) /* 스트링으로부터 토큰을 얻기 위함 */
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
void printToken(int p) /* 연산 출력 */
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
void Postfix(void) /*수식을 후위 표기식으로 출력*/
{
	char symbol;
	int token;
	int n = 0;
	int  top = 0; /*eos를 스택에 삽입*/
	stack[0] = eos;
	token = gettoken(&symbol, &n);
	for (; token != eos; token = gettoken(&symbol, &n))
	{
		if (token == operand) /* 토큰이 피 연산자 일때*/
			printf("%c", symbol);
		else if (token == rparen) /*왼쪽 괄호가 나올 때까지 토큰들을 제거해서 출력시킴*/
		{
			while (stack[top] != lparen)
				printToken(pop(&top));
			pop(&top); /*왼쪽 괄호를 버린다.*/
		}
		else
		{
			while (isp[stack[top]] >= icp[token]) /*스택에 있는 연산자의 우선순위가 들어오는 연산자의 우선순위보다 높거나 같으면 pop()*/
				printToken(pop(&top));
			push(&top, token); /* 들어오는 연산자 */
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
