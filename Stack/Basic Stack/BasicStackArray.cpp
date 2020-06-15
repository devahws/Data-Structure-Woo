#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 5

typedef int element;
typedef struct stack {
	element* data;
	element top;
} Stack;

Stack* init() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	newStack->data = (int*)malloc(sizeof(int) * STACK_SIZE);
	newStack->top = 0;

	return newStack;
}

bool isFull(Stack* stack) {
	if (stack->top == STACK_SIZE)
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
	while (!isFull(stack)) {
		stack->data[(stack->top)++] = data;
		return;
	}
	printf("Stack is Full\n");
}

void pop(Stack* stack) {
	while (!isEmpty(stack)) {
		printf("pop %d\n", stack->data[--(stack->top)]);
		return;
	}
	printf("Stack is Empty\n");
}

int main()
{
	Stack* newStack = init();
	for (int i = 0; i < 6; i++) {
		printf("$ 데이터를 입력하세요 >> ");
		int data;
		scanf("%d", &data);
		push(newStack, data);
	}
	int i = 0;
	while (i < newStack->top) {
		printf("%d ", newStack->data[i]);
		i++;
	}
	printf("\n");

	for (int i = 0; i < 6; i++) {
		pop(newStack);
	}
}