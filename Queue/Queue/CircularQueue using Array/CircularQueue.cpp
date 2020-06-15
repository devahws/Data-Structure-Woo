#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

// front -> 첫 번째 요소, rear-> 마지막 요소 하나 뒤(empty space)
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
}

typedef int element;
typedef struct queue {
	element data[SIZE];
	int front;
	int rear;
} Queue;

Queue* init() {
	Queue* newQ = (Queue*)malloc(sizeof(Queue));
	newQ->front = 0;
	newQ->rear = 0;

	return newQ;
}

bool isEmpty(Queue* queue) {
	if (queue->front == queue->rear)
		return 1;
	else
		return 0;
}

bool isFull(Queue* queue) {
	if ((queue->rear+1)%SIZE == queue->front)
		return true;
	else
		return false;
}

void enqueue(Queue* queue, element data) {
	if (isFull(queue))
		error("Queue is full");
	else {
		queue->data[queue->rear] = data;
		queue->rear = (queue->rear + 1) % SIZE;
	}
}

element dequeue(Queue* queue) {
	if (isEmpty(queue))
		error("Queue is empty");
	else {
		element rdata = queue->data[queue->front];
		queue->front = (queue->front + 1) % SIZE;
		return rdata;
	}
}

void printQueue(Queue* queue) {
	int i = queue->front;
	if (isEmpty(queue))
		error("Queue is empty");
	else {
		if (queue->front < queue->rear)
			while (i < queue->rear)
				printf("%d ", queue->data[i++]);
		else {
			while (i < SIZE)
				printf("%d ", queue->data[i++]);
			i = 0;
			while (i < queue->rear)
				printf("%d ", queue->data[i++]);
		}
		printf("\n");
	}
}

int main()
{
	Queue* newQ = init();
	for (int i = 0; i < 9; i++) {
		enqueue(newQ, i);
		printQueue(newQ);
	}

	for (int i = 0; i < 10; i++) {
		dequeue(newQ);
		printQueue(newQ);
	}

	for (int i = 0; i < 5; i++) {
		enqueue(newQ, i);
		printQueue(newQ);
	}
}