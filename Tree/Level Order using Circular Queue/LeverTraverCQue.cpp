#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myqueue.h"
#define SIZE 10



// Ʈ�� �ڷ���
void clearBuffer(void) {
	while (getchar() != '\n');
}

void readline(FILE* fp, char** name, int* studentID, char** major) {
	char* buffer = (char*)malloc(sizeof(char) * 100);
	int c, i = 0;
	while ((c = fgetc(fp)) != EOF && c != '\n')
		buffer[i++] = c;
	buffer[i] = '\0';
	*name = strtok(buffer, " ");
	*studentID = atoi(strtok(NULL, " "));
	*major = strtok(NULL, " ");
}

void readline2(FILE* fp, char** name, int* num) {
	char* buffer = (char*)malloc(sizeof(char) * 100);
	int c, i = 0;
	while ((c = fgetc(fp)) != EOF && c != '\n')
		buffer[i++] = c;
	buffer[i] = '\0';
	*name = strtok(buffer, " ");
	*num = atoi(strtok(NULL, " "));
}


typedef struct tree {
	Node* root;
	int size;
}Tree;

Node* makeNode(char* name, int id, char* major) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->name = name;
	newnode->studentID = id;
	newnode->major = major;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

void addNode(Node* root, Node* node) {
	if (strcmp(root->name, node->name) < 0) {	// ���ο� ����� �̸��� ��Ʈ�� �̸����� Ŭ ��
		if (root->right == NULL) {
			root->right = node;
			node->left = NULL;
			node->right = NULL;
		}
		else
			addNode(root->right, node);
	}
	else if (strcmp(root->name, node->name) > 0) {	// ���ο� ����� �̸��� ��Ʈ�� �̸����� ���� ��
		if (root->left == NULL) {
			root->left = node;
			node->left = NULL;
			node->right = NULL;
		}
		else
			addNode(root->left, node);
	}
	else {		// ���ο� ����� �̸��� ��Ʈ�� �̸��� ���� ��
		if (root->studentID < node->studentID) { // �й����� �� 
			if (root->right == NULL) {
				root->right = node;
				node->left = NULL;
				node->right = NULL;
			}
			else
				addNode(root->right, node);
		}
		else if (root->studentID > node->studentID) {
			if (root->left == NULL) {
				root->left = node;
				node->left = NULL;
				node->right = NULL;
			}
			else
				addNode(root->left, node);
		}
	}
}

void findNode(Node* root, char* name, int num) {
	Node* tmp = root;
	if (tmp == NULL)
		printf("ã�� ������ �л��� �������� �ʽ��ϴ�.\n");
	else {
		if (strcmp(tmp->name, name) < 0)
			findNode(tmp->right, name, num);
		else if (strcmp(tmp->name, name) > 0) {
			findNode(tmp->left, name, num);
		}
		else if (strcmp(tmp->name, name) == 0)
			if (tmp->studentID == num)
				printf("| Name: %s | StudentId: %d | Major: %s\n", tmp->name, tmp->studentID, tmp->major);
			else {
				if (tmp->studentID < num)
					findNode(tmp->right, name, num);
				else if (tmp->studentID > num)
					findNode(tmp->left, name, num);
			}
	}
}

// ���� ť 

typedef Node* element;

void levelOrder(Queue* queue, Node* root) {
	enqueue(queue, root);		// root�� ���� ť�� �ְ� ����
	while (!isEmpty(queue)) {	// ť�� empty ���°� �Ǳ� ������ ���� ����
		Node* tmp = dequeue(queue);	// ť�� ���� �տ� �����ϴ� ��带 dequeue �Ͽ� tmp�� ����
		printf("| Name: %s | StudentId: %d | Major: %s\n", tmp->name, tmp->studentID, tmp->major); // ���
		if (tmp->left)					// tmp�� ���� ��尡 �����ϸ�
			enqueue(queue, tmp->left);	// ť�� ���Ӱ� ����
		if (tmp->right)					// tmp�� ������ ��尡 �����ϸ�
			enqueue(queue, tmp->right);	// ť�� ���Ӱ� ����
	}
}

int main()
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->size = 0;
	FILE* fp = fopen("list.txt", "r");

	for (int i = 0; i < SIZE; i++) {
		char* name = 0;
		int id = 0;
		char* major = 0;

		readline(fp, &name, &id, &major);
		Node* newnode = makeNode(name, id, major);
		if (tree->size == 0) {
			tree->root = newnode;
			tree->size++;
		}
		else
			addNode(tree->root, newnode);
	}

	//for (int i = 0; i < 5; i++) {
	//	printf("$ ã�� �л��� ������ �Է��Ͻÿ� >> ");
	//	char* name = 0;
	//	int id = 0;
	//	readline2(stdin, &name, &id);
	//	findNode(tree->root, name, id);
	//}

	Queue* queue = init();
	levelOrder(queue, tree->root);
}