#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

void error(const char* message) {
	fprintf(stderr, "%s\n", message);
}

typedef int element;
typedef struct node {
	element data;
	struct node* rlink;
	struct node* llink;
}Node;

typedef struct deque {
	node* front;
	node* rear;
	int size;
}Deque;

Deque* init() {
	Deque* newDeq = (Deque*)malloc(sizeof(Deque));
	Node* dummy = (Node*)malloc(sizeof(Node));
	newDeq->front = dummy;
	newDeq->rear = dummy;
	// 초기 덱의 front 노드 설정
	newDeq->front->rlink = dummy;
	newDeq->front->llink = NULL;
	// 초기 덱의 rear 노드 설정
	newDeq->rear->llink = dummy;
	newDeq->rear->rlink = NULL;
	// 초기 덱의 크기 설정
	newDeq->size = 0;
	return newDeq;
}

bool isEmpty(Deque* deque) {
	if (deque->front == deque->rear)
		return true;
	else
		return false;
}

void fenqueue(Deque* deque, element data) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->rlink = deque->front;
	deque->front->llink = newnode;
	newnode->llink = NULL;
	deque->front = newnode;
	deque->size++;
}

void enqueue(Deque* deque, element data) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->llink = deque->rear->llink;
	newnode->rlink = deque->rear;
	deque->rear->llink->rlink = newnode;
	deque->rear->llink = newnode;
	deque->size++;
}

element fdequeue(Deque* deque) {
	if (isEmpty(deque))
		error("Deque is empty front");
	else {
		Node* tmp = deque->front;
		element tmpdata = tmp->data;
		deque->front = deque->front->rlink;
		deque->front->llink = NULL;
		free(tmp);
		deque->size--;
		return tmpdata;		
	}
	
}

element rdequeue(Deque* deque) {
	if (isEmpty(deque))
		error("Deque is empty rear");
	else {
		Node* tmp = deque->rear;
		element tmpdata = tmp->data;
		deque->rear = deque->rear->llink;
		deque->rear->rlink = NULL;
		free(tmp);
		deque->size--;
		return tmpdata;
	}

}

void printDeque(Deque* deque) {
	if (isEmpty(deque))
		error("Deque is empty whole");
	else {
		printf("size:%d |", deque->size);
		Node* tmp = deque->front;
		while (tmp->rlink != NULL) {
			printf("%d|", tmp->data);
			tmp = tmp->rlink;
		}
		printf("\n");
	}
}

int main()
{
	Deque* newDeq = init();

	for (int i = 0; i < 5; i++) {
		fenqueue(newDeq, i);
		printDeque(newDeq);
	}
	printf("pr1\n");
	for (int i = 0; i < 3; i++) {
		enqueue(newDeq, i);
		printDeque(newDeq);
	}
	printf("pr2\n");
	for (int i = 0; i < 9; i++) {
		rdequeue(newDeq);
		printDeque(newDeq);
	}
	printf("pr3\n");
	for (int i = 0; i < 5; i++) {
		fdequeue(newDeq);
		printDeque(newDeq);
	}
	printf("pr4\n");
}