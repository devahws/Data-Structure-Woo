#include <stdio.h>
#include <stdlib.h>
#include "myqueue.h"

#define MAX_VERTICES 50

typedef struct GraphType {
	int n; // ������ ����
	bool visitied[MAX_VERTICES];
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

GraphType* init() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	int r, c;	// row, collumn
	g->n = 0; // �ʱ� v ���� 0��
	for (r = 0; r < MAX_VERTICES; r++) {	// ������� �ʱ�ȭ
		g->visitied[r] = false;
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
	}
	return g;
}

void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;	// ����� ���� �ϳ� �߰�
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;	// ��������̱� ������
	g->adj_mat[end][start] = 1;
}

void bfs(GraphType* g, int v) {
	Queue* newQueue = initQ();
	enqueue(newQueue, v);
	int w;
	g->visitied[v] = true;
	while (!isEmpty(newQueue)) {	// ť�� empty ���°� �Ǳ� ������ �ݺ�
		w = dequeue(newQueue);
		printf("V(%d) -> ", w);
		for(int i=0; i<g->n; i++)
			if (g->adj_mat[w][i] == 1 && !g->visitied[i]) {	// edge�� �����ϰ� �湮���� ���� ��忡 ���ؼ�
				g->visitied[i] = true;		// �湮 ǥ��
				enqueue(newQueue, i);		// queue�� �������
			}
	}
}

int main() {
	GraphType* g = init();
	for (int i = 0; i < 10; i++)
		insert_vertex(g, i);

	insert_edge(g, 1, 4);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 2, 3);
	insert_edge(g, 1, 6);
	insert_edge(g, 4, 7);
	insert_edge(g, 3, 4);
	insert_edge(g, 6, 8);
	insert_edge(g, 1, 9);

	bfs(g, 1);

}