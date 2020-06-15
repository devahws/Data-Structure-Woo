#include <stdio.h>
#include <stdlib.h>
#include "myqueue.h"
#define MAX_VERTICES 50

typedef struct node {
	int num;			// vertex�� ����
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

void bfs(Graph* g, int v) {
	Queue* newQueue = initQ();
	Node* tmp;
	g->visited[v] = true;
	enqueue(newQueue, v);
	while (!isEmpty(newQueue)) {	// queue�� empty ���°� �Ǳ� ������ ��� �ݺ�
		tmp = g->vertex[dequeue(newQueue)];	// ť�� ���� �տ� �ִ� ��Ҹ� dequeue
		printf("V(%d) -> ", tmp->num);
		// tmp�� ������ ������ ��� ť�� ����
		while (tmp != NULL) {
			if (g->visited[tmp->num] == false) {	// ���� �湮���� ���� �����
				enqueue(newQueue, tmp->num);	// ť�� ����
				g->visited[tmp->num] = true;
			}
			tmp = tmp->link;
		}
	}

}

int main() {
	Graph* g = initGraph();			// �׷��� ����
	for (int i = 1; i < 9; i++) {	// ��� 7�� ����
		insert_vertex(g, i);
	}
	insert_edge(g, 1, 4);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 3);
	insert_edge(g, 3, 2);
	insert_edge(g, 1, 6);
	insert_edge(g, 3, 5);
	insert_edge(g, 6, 8);
	bfs(g, 1);

}