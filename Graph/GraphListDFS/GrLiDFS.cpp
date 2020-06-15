#include <stdio.h>
#include <stdlib.h>
#include "mystack.h"
#define MAX_VERTICES 50

typedef struct node {
	int num;		// vertex의 숫자
	struct node* link;
}Node;

typedef struct Graph {
	Node* vertex[MAX_VERTICES];	// 연결된 노드들을 저장하는 링크
	int n;						// 그래프를 구성하는 노드들의 개수
	bool visited[MAX_VERTICES];	// DFS에서 사용할 visited 배열
}Graph;

Node* initNode() {		// 노드
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->link = NULL;
	return tmp;
}

Graph* initGraph() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->vertex[i] = NULL;	// 처음엔 노드들을 NULL 값으로 채워줌
		g->visited[i] = false;
	}

	return g;
}

void insert_vertex(Graph* g, int n) {	// 그래프에 노드를 추가
	if ((g->n) + 1 > MAX_VERTICES) {	// 그래프의 n이 꽉 찼을 때
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->vertex[n] = initNode();
	g->vertex[n]->num = n;
	g->n++;	// 노드의 개수 하나 추가
}

void insert_edge(Graph* g, int start, int end) {
	if (g->vertex[start] == NULL || g->vertex[end] == NULL) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	Node* tmp1 = g->vertex[start];
	while (tmp1->link != NULL)
		tmp1 = tmp1->link;
	Node* newNode1 = initNode();
	newNode1->num = end;		// end 노드를 start 노드와 연결
	tmp1->link = newNode1;

	Node* tmp2 = g->vertex[end];
	while (tmp2->link != NULL)
		tmp2 = tmp2->link;
	Node* newNode2 = initNode();
	newNode2->num = start;		// start 노드를 end 노드와 연결
	tmp2->link = newNode2;
}

void dfs_recur(Graph* g, int v) {
	Node* w;
	g->visited[v] = true;
	printf("정점 %d -> ", v);
	for (w = g->vertex[v]; w->link; w = w->link)	// w 노드에 연결된 노드가 존재한다면
		if (!g->visited[w->link->num])
			dfs_recur(g, w->link->num);
}

void dfs_stack(Graph* g, int v) {
	if (g->vertex[v] != NULL) {			// 선택한 노드가 존재하는 노드일 때
		Stack* newStack = initStack();
		push(newStack, v);
		printf("V(%d) -> ", v);
		g->visited[v] = true;

		Node* tmp = g->vertex[v]->link;
		while (!isEmpty(newStack)) {
			if (tmp == NULL) {	// 연결된 노드가 없다면
				tmp = g->vertex[pop(newStack)];	// stack의 top에 위치하는 노드(이전 방문 노드)로 돌아감
			}
			else {		// 연결된 노드가 존재할 때
				if (!g->visited[tmp->num]) {	// 해당 노드를 방문하지 않았을 때
					printf("V(%d) -> ", tmp->num);
					push(newStack, tmp->num);	// visited Stack에 push
					g->visited[tmp->num] = true;	// 방문한 노드로 표시
					tmp = g->vertex[tmp->num]->link; // 다음 노드로 이동
				}
				else {	// 이미 방문한 노드일 때
					tmp = tmp->link;
				}
			}
		}
	}
	else
		printf("해당 노드가 존재하지 않습니다.");	// 선택한 노드가 존재하지 않을 때
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