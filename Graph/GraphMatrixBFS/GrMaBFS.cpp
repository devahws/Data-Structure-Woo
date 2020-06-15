#include <stdio.h>
#include <stdlib.h>
#include "myqueue.h"

#define MAX_VERTICES 50

typedef struct GraphType {
	int n; // 정점의 개수
	bool visitied[MAX_VERTICES];
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

GraphType* init() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	int r, c;	// row, collumn
	g->n = 0; // 초기 v 개수 0개
	for (r = 0; r < MAX_VERTICES; r++) {	// 인접행렬 초기화
		g->visitied[r] = false;
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
	}
	return g;
}

void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;	// 노드의 개수 하나 추가
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;	// 인접행렬이기 때문에
	g->adj_mat[end][start] = 1;
}

void bfs(GraphType* g, int v) {
	Queue* newQueue = initQ();
	enqueue(newQueue, v);
	int w;
	g->visitied[v] = true;
	while (!isEmpty(newQueue)) {	// 큐가 empty 상태가 되기 전까지 반복
		w = dequeue(newQueue);
		printf("V(%d) -> ", w);
		for(int i=0; i<g->n; i++)
			if (g->adj_mat[w][i] == 1 && !g->visitied[i]) {	// edge가 존재하고 방문하지 않은 노드에 대해서
				g->visitied[i] = true;		// 방문 표시
				enqueue(newQueue, i);		// queue에 집어넣음
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