// 인접 행렬로 구현한 그래프
// DFS 
//	1) Recursion
//	2) Iteration(Stack)
#include <stdio.h>
#include <stdlib.h>
#include "mystack.h"

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

void dfs_recur(GraphType* g, int v) {
	int w;
	g->visitied[v] = true;
	printf("정점 %d -> ", v);
	for (w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w] && !g->visitied[w])
			dfs_recur(g, w);
	}
}

void dfs_stack(GraphType* g, int v) {
	int tmp;
	Stack* newStack = initStack();	// 
	push(newStack, v);				// 시작 노드 v를 push
	
	while (!isEmpty(newStack)) {	// 스택에서 모든 값이 사라지기 전까지
		tmp = pop(newStack);
		if (g->visitied[tmp] == false) {
			printf("V(%d) -> ", tmp);
			g->visitied[tmp] = true;
			for(int w=0; w<MAX_VERTICES; w++)
				if(g->adj_mat[tmp][w] == true)
					if (g->visitied[w] == false) {
						g->visitied[w] == true;
						push(newStack, w);
					}
		}
	}
}

int main() {
	GraphType* g = init();
	for (int i = 0; i < 8; i++)
		insert_vertex(g, i);

	insert_edge(g, 1, 4);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 2, 3);
	insert_edge(g, 1, 6);
	insert_edge(g, 4, 7);
	insert_edge(g, 3, 4);

	//dfs_recur(g, 1);	// recursion을 사용한 DFS
	dfs_stack(g, 1);	// iteration(stack)을 사용한 DFS
}