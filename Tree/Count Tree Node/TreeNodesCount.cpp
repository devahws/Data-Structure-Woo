#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystack.h"
#define SIZE 10

void clearBuffer(void) {
	while (getchar() != '\n');
}
int fileEnd = 0;
void readline(FILE* fp, char** name, int* studentID, char** major) {
	char* buffer = (char*)malloc(sizeof(char) * 100);
	int c, i = 0;
	while ((c = fgetc(fp)) != EOF && c != '\n')
		buffer[i++] = c;
	if (c == EOF)
		fileEnd = 1;
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
	if (strcmp(root->name, node->name) < 0) {	// 새로운 노드의 이름이 루트의 이름보다 클 때
		if (root->right == NULL) {
			root->right = node;
			node->left = NULL;
			node->right = NULL;
		}
		else
			addNode(root->right, node);
	}
	else if (strcmp(root->name, node->name) > 0) {	// 새로운 노드의 이름이 루트의 이름보다 작을 때
		if (root->left == NULL) {
			root->left = node;
			node->left = NULL;
			node->right = NULL;
		}
		else
			addNode(root->left, node);
	}
	else {		// 새로운 노드의 이름과 루트의 이름이 같을 때
		if (root->studentID < node->studentID) { // 학번으로 비교 
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

int NodeCountRecur(Node* root) {
	int count = 0;
	if (root != NULL)
		count = 1 + NodeCountRecur(root->left) + NodeCountRecur(root->right);

	return count;
}

int NodeCountIter(TStack* stack, Node* root) {
	int count = 0;
	while (true) {
		while (root != NULL) {
			push(stack, root);
			root = root->left;
			count++;
		}
		root = pop(stack);
		if (root == NULL)
			break;
		root = root->right;
	}
	return count;
}


int main()
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->size = 0;
	FILE* fp = fopen("list.txt", "r");

	// 노드 추가
	while (fileEnd == 0) {
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
		
	TStack* tstack = init();
	printf("Node Count by RECURSION: %d\n", NodeCountRecur(tree->root));
	printf("Node Count by ITERATION: %d\n", NodeCountIter(tstack, tree->root));

}