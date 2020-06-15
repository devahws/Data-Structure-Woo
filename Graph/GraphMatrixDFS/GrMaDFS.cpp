// ���� ��ķ� ������ �׷���
// DFS 
//	1) Recursion
//	2) Iteration(Stack)
#include <stdio.h>
#include <stdlib.h>
#include "mystack.h"

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

void dfs_recur(GraphType* g, int v) {
	int w;
	g->visitied[v] = true;
	printf("���� %d -> ", v);
	for (w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w] && !g->visitied[w])
			dfs_recur(g, w);
	}
}

void dfs_stack(GraphType* g, int v) {
	int tmp;
	Stack* newStack = initStack();	// 
	push(newStack, v);				// ���� ��� v�� push
	
	while (!isEmpty(newStack)) {	// ���ÿ��� ��� ���� ������� ������
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

	//dfs_recur(g, 1);	// recursion�� ����� DFS
	dfs_stack(g, 1);	// iteration(stack)�� ����� DFS
}