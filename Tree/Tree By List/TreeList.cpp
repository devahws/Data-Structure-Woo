#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5

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

typedef struct node {
	char* name;
	int studentID;
	char* major;

	struct node* left;
	struct node* right;
}Node;

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

void findNode(Node* root, char* name, int num) {
	Node* tmp = root;
	if(tmp==NULL)
		printf("찾는 정보의 학생이 존재하지 않습니다.\n");
	else {
		if (strcmp(tmp->name, name) < 0)
			findNode(tmp->right, name, num);
		else if (strcmp(tmp->name, name) > 0) {
			findNode(tmp->left, name, num);
		}
		else if (strcmp(tmp->name, name) == 0)
			if (tmp->studentID == num)
				printf("| Name: %s | StudentId: %d | Major: %s\n", tmp->name, tmp->studentID, tmp->major);
			else{
				if (tmp->studentID < num)
					findNode(tmp->right, name, num);
				else if (tmp->studentID > num)
					findNode(tmp->left, name, num);
		}
	}
}

void findNodeIter(Node* root, char* name, int num) {
	Node* tmp = root;
	while (tmp != NULL) {
		if (strcmp(tmp->name, name) < 0)
			tmp = tmp->right;
		else if (strcmp(tmp->name, name) > 0)
			tmp = tmp->left;
		else {
			if (tmp->studentID < num)
				tmp = tmp->right;
			else if (tmp->studentID > num)
				tmp = tmp->left;
			else {
				printf("| Name: %s | StudentId: %d | Major: %s\n", tmp->name, tmp->studentID, tmp->major);
				return;
			}
		}
	}
	printf("찾는 학생이 존재하지 않습니다.\n");
}

int main()
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->size = 0;
	FILE* fp = fopen("list.txt", "r");
	
	for (int i = 0; i < 5; i++) {
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
	
	for (int i = 0; i < 5; i++) {
		printf("$ 찾는 학생의 정보를 입력하시오 >> ");
		char* name = 0;
		int id = 0;
		readline2(stdin, &name, &id);
		findNode(tree->root, name, id);
		findNodeIter(tree->root, name, id);
	}
}