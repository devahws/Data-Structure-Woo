#pragma once
#define STACK_SIZE 100

typedef struct node {
	char* name;
	int studentID;
	char* major;

	struct node* left;
	struct node* right;
}Node;

typedef struct treestack {
	int top;
	Node** stack;
} TStack;

TStack* init() {
	TStack* stack = (TStack*)malloc(sizeof(TStack));
	stack->top = -1;
	stack->stack = (Node**)malloc(sizeof(Node*) * STACK_SIZE);
	return stack;
}

void push(TStack* tstack, Node* node) {
	if (tstack->top < STACK_SIZE - 1)
		tstack->stack[++tstack->top] = node;
	else
		printf("stack is full\n");
}

Node* pop(TStack* tstack) {
	if (tstack->top > -1)
		return tstack->stack[tstack->top--];
	else
		return NULL;
}