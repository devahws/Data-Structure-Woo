#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// pop
void pop(Stack* stack) {
	if (!isEmpty(stack)) {
		Node* removed = stack->top;	// ���� top�� ��ġ�� ����
		stack->top = removed->link;	// top�� �����͸� ���� ���� �̵�
		free(removed);			// pop�� ������ top�� ����
	}
	else
		printf("Stack is empty\n");
}

bool verifyPoly(Stack* stack, char* poly) {
	char c;
	int i = 0;

	while ((c = poly[i]) != '\0') {
		if (c == '{')		// ����#1 ���� ��ȣ�� �����ϸ� ���ÿ� ����
			push(stack, '}');
		else if(c== '(')
			push(stack, ')');
		else if (c == '[')
			push(stack, ']');
		else if (c == '}' || c == ')' || c == ']') {		// ����#2 ������ ��ȣ�� �����ϸ� ������ top�� ��
			if (isEmpty(stack)) {
				printf("��ȣ�� ������ �˸��� �ʽ��ϴ�.");
				return false;
			}
			char bracket = stack->top->data;
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
