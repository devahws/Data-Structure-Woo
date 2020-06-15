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
		if (c == '{')		// ����#1 ���� ��ȣ�� �����ϸ� ���ÿ� ����
			push(stack, '}');
		else if (c == '(')
			push(stack, ')');
		else if (c == '[')
			push(stack, ']');
		else if (c == '}' || c == ')' || c == ']') {		// ����#2 ������ ��ȣ�� �����ϸ� ������ top�� ��
			if (isEmpty(stack)) {
				printf("��ȣ�� ������ �˸��� �ʽ��ϴ�.");
				return false;
			}
			char bracket = stack->data[(stack->top) - 1];
			if (bracket == c)						// �����ϴٸ� �ش� ��ȣ�� pop
				pop(stack);
			else {									// �������� �ʴٸ� �ùٸ��� ���� �����̱� ������ false return
				printf("��ȣ�� ������ �ùٸ��� �ʽ��ϴ�.");
				return false;;
			}
		}
		i++;
	}
	if (isEmpty(stack))
		return true;
	else {
		printf("��ȣ�� ������ �˸��� �ʽ��ϴ�.");
		return false;
	}
}

int main()
{
	Stack* newStack = init();

	printf("$ ������ �Է��ϼ��� >> ");
	char* poly = readline(stdin, MAX_NUM);
	if (verifyPoly(newStack, poly))
		printf("�ùٸ� �����Դϴ�.");

}
