#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct node {
	element data;
	struct node* link;
}Node;

typedef struct stack {
	Node* top;
}Stack;


// init
Stack* init() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	newStack->top = NULL;

	return newStack;
}

// push
void push(Stack* stack, element data) {
	if (isEmpty(stack)) {
		Node* newnode = (Node*)malloc(sizeof(Node));
		newnode->data = data;
		newnode->link = NULL;
		stack->top = newnode;
	}
	else {
		Node* newnode = (Node*)malloc(sizeof(Node));
		newnode->data = data;
		newnode->link = stack->top;
		stack->top = newnode;
	}
}

// empty
bool isEmpty(Stack* stack) {
	if (stack->top == NULL)
		return true;
	else
		return false;
}

// pop
void pop(Stack* stack) {
	if(!isEmpty(stack)) {
		printf("pop %d\n", stack->top->data);
		Node* removed = stack->top;	// ���� top�� ��ġ�� ����
		stack->top = removed->link;	// top�� �����͸� ���� ���� �̵�
		free(removed);			// pop�� ������ top�� ����
	}
	else
		printf("Stack is empty\n");
}

int main()
{
	Stack* newStack = init();

	for (int i = 0; i < 5; i++) {
		printf("$ �����͸� �Է��ϼ��� >> ");
		element data;
		scanf("%d", &data);
		push(newStack, data);
	}

	while (!isEmpty(newStack))
		pop(newStack);

	return 0;
}