#pragma once
#define QSIZE 10

typedef struct node {
	char* name;
	int studentID;
	char* major;

	struct node* left;
	struct node* right;
}Node;

typedef Node* element;

void error(const char* message) {
	fprintf(stderr, "%s\n", message);
}

typedef struct queue {
	element data[QSIZE];
	int front;
	int rear;
	char flag;
} Queue;

Queue* init() {
	Queue* newQ = (Queue*)malloc(sizeof(Queue));
	newQ->front = 0;
	newQ->rear = 0;
	newQ->flag = 'f';

	return newQ;
}

bool isEmpty(Queue* queue) {
	if (queue->front == queue->rear && queue->flag == 'f')
		return 1;
	else
		return 0;
}

bool isFull(Queue* queue) {
	if (queue->front == queue->rear && queue->flag == 'r')
		return 1;
	else
		return 0;
}

void enqueue(Queue* queue, element data) {
	if (isFull(queue))
		error("Queue is full");
	else {
		queue->data[queue->rear] = data;
		queue->rear = (queue->rear + 1) % QSIZE;
		queue->flag = 'r';
	}
}

element dequeue(Queue* queue) {
	if (isEmpty(queue))
		error("Queue is empty");
	else {
		element rdata = queue->data[queue->front];
		queue->front = (queue->front + 1) % QSIZE;
		queue->flag = 'f';
		return rdata;
	}
}