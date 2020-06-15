#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 5
#define MAX_NUM 100

char* readline(FILE* fp, int max) {
	char* buff = (char*)malloc(sizeof(char) * MAX_NUM);
	int c, i = 0;
	while ((c = fgetc(fp)) != EOF && c != '\n')
		buff[i++] = c;

	buff[i] = '\0';

	return buff;
}

typedef char element;
typedef struct stack {
	element* data;
	element top;
	element capacity;
} Stack;

Stack* init() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	newStack->data = (element*)malloc(sizeof(element) * STACK_SIZE);
	newStack->top = 0;
	newStack->capacity = STACK_SIZE;

	return newStack;
}

bool isFull(Stack* stack) {
	if (stack->top == stack->capacity)
		return true;
	else
		return false;
}

bool isEmpty(Stack* stack) {
	if (stack->top == 0)
		return true;
	else
		return false;
}

void push(Stack* stack, element data) {
	if (isFull(stack)) {
		stack->capacity *= 2;
		stack->data = (element*)realloc(stack->data, sizeof(element) * stack->capacity);
		stack->data[(stack->top)++] = data;
	}
	else {
		stack->data[(stack->top)++] = data;
	}
}

void pop(Stack* stack) {
	while (!isEmpty(stack)) {
		stack->top--;
		return;
	}
	printf("Stack is Empty\n");
}

bool verifyPoly(Stack* stack, char* poly) {
	char c;
	int i = 0;

	while ((c = poly[i]) != '\0') {
		if (c == '{')		// 조건#1 왼쪽 괄호가 등장하면 스택에 저장
			push(stack, '}');
		else if (c == '(')
			push(stack, ')');
		else if (c == '[')
			push(stack, ']');
		else if (c == '}' || c == ')' || c == ']') {		// 조건#2 오른쪽 괄호가 등장하면 스택의 top과 비교
			if (isEmpty(stack)) {
				printf("괄호의 개수가 알맞지 않습니다.");
				return false;
			}
			char bracket = stack->data[(stack->top) - 1];
			if (bracket == c)						// 동일하다면 해당 괄호를 pop
				pop(stack);
			else {									// 동일하지 않다면 올바르지 않은 수식이기 때문에 false return
				printf("괄호의 순서가 올바르지 않습니다.");
				return false;;
			}
		}
		i++;
	}
	if (isEmpty(stack))
		return true;
	else {
		printf("괄호의 개수가 알맞지 않습니다.");
		return false;
	}
}

int main()
{
	Stack* newStack = init();

	printf("$ 수식을 입력하세요 >> ");
	char* poly = readline(stdin, MAX_NUM);
	if (verifyPoly(newStack, poly))
		printf("올바른 수식입니다.");

}
