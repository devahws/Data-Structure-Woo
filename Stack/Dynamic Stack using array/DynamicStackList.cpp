#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 5

typedef int element;
typedef struct stack {
	element* data;
	element top;
	element capacity;
} Stack;

Stack* init() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	newStack->data = (int*)malloc(sizeof(element) * STACK_SIZE);
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
		stack->data = (int*)realloc(stack->data, sizeof(element) * stack->capacity);
		stack->data[(stack->top)++] = data;
	}
	else {
		stack->data[(stack->top)++] = data;
	}
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
	for (int i = 0; i < 11; i++) {
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

	while (newStack->top > 0)
		pop(newStack);

	return 0;
}