#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int SIZE = 20;

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
}Node;

Node** init() {
	Node** tree = (Node**)malloc(sizeof(Node*) * SIZE);
	for (int i = 0; i < SIZE; i++) {
		tree[i] = NULL;
	}

	return tree;
}

Node** remake(Node** root) {
	Node** r = root;
	int i = SIZE;
	SIZE = (2 * SIZE)+1;
	realloc(root, sizeof(Node*) * SIZE);
	for (int j = i; j < SIZE; j++)
		root[j] = NULL;
	free(r);
	printf("pr4\n");
	return root;
}

Node* makeNode(char* name, int num, char* major) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->name = name;
	newnode->studentID = num;
	newnode->major = major;

	return newnode;
}

void insert(Node** root, Node* node, int index) {	
	if (root[1] == NULL)
		root[1] = node;
	else {
		if (strcmp(root[index]->name, node->name) < 0) {
			if (root[2 * index + 1] == NULL)
				root[2 * index + 1] = node;
			else {
				if (index * 2 + 1 >= SIZE) {
					root = remake(root);
					root[2 * index + 1] = node;
				}
				else {
					insert(root, node, 2 * index + 1);
				}
			}		
		}
		else if (strcmp(root[index]->name, node->name) > 0) {
			if (root[2 * index] == NULL)
				root[2 * index] = node;
			else {
				if (index * 2 >= SIZE) {
					root = remake(root);
					root[2 * index] = node;
				}
				else {
					insert(root, node, 2 * index);
				}
			}
		}
		else {
			printf("pr2\n");
			if (root[index]->studentID < node->studentID) {
				if (root[2 * index + 1] == NULL)
					root[2 * index + 1] = node;
				else {
					if (index * 2 + 1 >= SIZE) {
						root = remake(root);
						printf("pr1\n");
					}
					if(root[2 * index + 1] == NULL)
						root[2 * index + 1] = node;
					else {
						insert(root, node, 2 * index + 1);
					}	
				}
			}
			else if (root[index]->studentID > node->studentID) {
				if (index * 2 >= SIZE) {
					root = remake(root);
					printf("pr1\n");
				}
				printf("pr3\n");
				if (root[2 * index] == NULL)
					root[2 * index] = node;
				else
					insert(root, node, 2 * index);
			}
		}
	}
}

void findNode(Node** root, char* name, int num, int index) {
	if (root[index] == NULL)
		printf("찾는 학생이 존재하지 않습니다.\n");
	else {
		if (strcmp(root[index]->name, name) < 0)
			findNode(root, name, num, index * 2 + 1);
		else if (strcmp(root[index]->name, name) > 0)
			findNode(root, name, num, index * 2);
		else {
			if (root[index]->studentID < num)
				findNode(root, name, num, index * 2 + 1);
			else if (root[index]->studentID > num)
				findNode(root, name, num, index * 2);
			else
				printf("Name: %s StudentID: %d\n", root[index]->name, root[index]->studentID);
		}
	}
}

int main()
{
	FILE* fp = fopen("list.txt", "r");

	Node** tree = init();
	for (int i = 0; i<5; i++) {
		char* name = 0;
		int id = 0;
		char* major = 0;

		readline(fp, &name, &id, &major);

		Node* newnode = makeNode(name, id, major);

		insert(tree, newnode, 1);
		printf("insert %s %s\n", name, tree[1]->name);
	}

	for (int i = 0; i < 5; i++) {
		printf("$ 찾는 학생의 정보를 입력하시오 >> ");
		char* name = 0;
		int id = 0;
		readline2(stdin, &name, &id);
		findNode(tree, name, id, 1);
	}

}
