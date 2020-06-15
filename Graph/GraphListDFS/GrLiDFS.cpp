#include <stdio.h>
#include <stdlib.h>
#include "mystack.h"
#define MAX_VERTICES 50

typedef struct node {
	int num;		// vertex�� ����
	struct node* link;
}Node;

typedef struct Graph {
	Node* vertex[MAX_VERTICES];	// ����� ������ �����ϴ� ��ũ
	int n;						// �׷����� �����ϴ� ������ ����
	bool visited[MAX_VERTICES];	// DFS���� ����� visited �迭
}Graph;

Node* initNode() {		// ���
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->link = NULL;
	return tmp;
}

Graph* initGraph() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->vertex[i] = NULL;	// ó���� ������ NULL ������ ä����
		g->visited[i] = false;
	}

	return g;
}

void insert_vertex(Graph* g, int n) {	// �׷����� ��带 �߰�
	if ((g->n) + 1 > MAX_VERTICES) {	// �׷����� n�� �� á�� ��
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->vertex[n] = initNode();
	g->vertex[n]->num = n;
	g->n++;	// ����� ���� �ϳ� �߰�
}

void insert_edge(Graph* g, int start, int end) {
	if (g->vertex[start] == NULL || g->vertex[end] == NULL) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	Node* tmp1 = g->vertex[start];
	while (tmp1->link != NULL)
		tmp1 = tmp1->link;
	Node* newNode1 = initNode();
	newNode1->num = end;		// end ��带 start ���� ����
	tmp1->link = newNode1;

	Node* tmp2 = g->vertex[end];
	while (tmp2->link != NULL)
		tmp2 = tmp2->link;
	Node* newNode2 = initNode();
	newNode2->num = start;		// start ��带 end ���� ����
	tmp2->link = newNode2;
}

void dfs_recur(Graph* g, int v) {
	Node* w;
	g->visited[v] = true;
	printf("���� %d -> ", v);
	for (w = g->vertex[v]; w->link; w = w->link)	// w ��忡 ����� ��尡 �����Ѵٸ�
		if (!g->visited[w->link->num])
			dfs_recur(g, w->link->num);
}

void dfs_stack(Graph* g, int v) {
	if (g->vertex[v] != NULL) {			// ������ ��尡 �����ϴ� ����� ��
		Stack* newStack = initStack();
		push(newStack, v);
		printf("V(%d) -> ", v);
		g->visited[v] = true;

		Node* tmp = g->vertex[v]->link;
		while (!isEmpty(newStack)) {
			if (tmp == NULL) {	// ����� ��尡 ���ٸ�
				tmp = g->vertex[pop(newStack)];	// stack�� top�� ��ġ�ϴ� ���(���� �湮 ���)�� ���ư�
			}
			else {		// ����� ��尡 ������ ��
				if (!g->visited[tmp->num]) {	// �ش� ��带 �湮���� �ʾ��� ��
					printf("V(%d) -> ", tmp->num);
					push(newStack, tmp->num);	// visited Stack�� push
					g->visited[tmp->num] = true;	// �湮�� ���� ǥ��
					tmp = g->vertex[tmp->num]->link; // ���� ���� �̵�
				}
				else {	// �̹� �湮�� ����� ��
					tmp = tmp->link;
				}
			}
		}
	}
	else
		printf("�ش� ��尡 �������� �ʽ��ϴ�.");	// ������ ��尡 �������� ���� ��
}

void dfs_stack2(Graph* g, int v) {
	Stack* newStack = initStack();
	push(newStack, v);
	Node* tmp;
	while (!isEmpty(newStack)) {
		tmp = g->vertex[pop(newStack)];
		g->visited[tmp->num] = true;
		printf("V(%d) -> ", tmp->num);
		while (tmp != NULL) {
			if (g->visited[tmp->num] == false) {
				push(newStack, tmp->num);
			}
			tmp = tmp->link;
		}
	}
}

int main() {
	Graph* g = initGraph();
	for (int i = 1; i < 8; i++) {
		insert_vertex(g, i);
	}

	insert_edge(g, 1, 4);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 3);
	insert_edge(g, 3, 2);
	insert_edge(g, 1, 6);
	insert_edge(g, 3, 5);

	/*dfs_recur(g, 1);*/
	dfs_stack(g, 1);
	//dfs_stack2(g, 1);

}