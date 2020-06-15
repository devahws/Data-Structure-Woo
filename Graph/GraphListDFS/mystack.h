#pragma once
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef int element;

typedef struct snode {
	element data;
	struct snode* link;
}StNode;

typedef struct stack {
	StNode* top;
}Stack;


// initStack
Stack* initStack() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	newStack->top = NULL;

	return newStack;
}

// empty
bool isEmpty(Stack* stack) {
	if (stack->top == NULL)
		return true;
	else
		return false;
}

// push
void push(Stack* stack, element data) {
	if (isEmpty(stack)) {
		StNode* newnode = (StNode*)malloc(sizeof(StNode));
		newnode->data = data;
		newnode->link = NULL;
		stack->top = newnode;
	}
	else {
		StNode* newnode = (StNode*)malloc(sizeof(StNode));
		newnode->data = data;
		newnode->link = stack->top;
		stack->top = newnode;
	}
}

// pop
int pop(Stack* stack) {
	if (!isEmpty(stack)) {
		element data = stack->top->data;
		StNode* removed = stack->top;	// 기존 top의 위치를 저장
		stack->top = removed->link;	// top의 포인터를 다음 노드로 이동
		free(removed);			// pop된 기존의 top을 삭제
		return data;
	}
	else
		printf("Stack is empty\n");
}