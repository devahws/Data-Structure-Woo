#include <stdio.h>
#include <stdlib.h>
#include "myqueue.h"
#define MAX_VERTICES 50

typedef struct node {
	int num;			// vertex의 숫자
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

void bfs(Graph* g, int v) {
	Queue* newQueue = initQ();
	Node* tmp;
	g->visited[v] = true;
	enqueue(newQueue, v);
	while (!isEmpty(newQueue)) {	// queue가 empty 상태가 되기 전까지 계속 반복
		tmp = g->vertex[dequeue(newQueue)];	// 큐의 제일 앞에 있는 요소를 dequeue
		printf("V(%d) -> ", tmp->num);
		// tmp에 인접한 노드들을 모두 큐에 저장
		while (tmp != NULL) {
			if (g->visited[tmp->num] == false) {	// 아직 방문하지 않은 노드라면
				enqueue(newQueue, tmp->num);	// 큐에 저장
				g->visited[tmp->num] = true;
			}
			tmp = tmp->link;
		}
	}

}

int main() {
	Graph* g = initGraph();			// 그래프 생성
	for (int i = 1; i < 9; i++) {	// 노드 7개 생성
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