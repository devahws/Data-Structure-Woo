// Array를 사용한 Deque
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

// front -> 첫 번째 요소, rear-> 마지막 요소
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
}

typedef int element;
typedef struct queue {
	int data[SIZE];
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
		queue->rear = (queue->rear + 1) % SIZE;
		queue->flag = 'r';
	}
}

void fenqueue(Queue* queue, element data) {
	if (isFull(queue))
		error("Queue is full");
	else {
		queue->front = ((queue->front - 1) + SIZE) % SIZE;
		queue->data[queue->front] = data;
		queue->flag = 'r';
	}
}

element dequeue(Queue* queue) {
	if (isEmpty(queue))
		error("Queue is empty");
	else {
		element rdata = queue->data[queue->front];
		queue->front = (queue->front + 1) % SIZE;
		queue->flag = 'f';
		return rdata;
	}
}

element rdequeue(Queue* queue) {
	if (isEmpty(queue))
		error("Queue is empty");
	else {
		queue->rear = ((queue->rear - 1) + SIZE) % SIZE;
		element rdata = queue->data[queue->rear];
		queue->flag = 'f';
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
	for (int i = 0; i <7 ; i++) {
		enqueue(newQ, i);
		printQueue(newQ);
	}

	for (int i = 0; i <4 ; i++) {
		fenqueue(newQ, i);
		printQueue(newQ);
	}

	for (int i = 0; i < 5; i++) {
		dequeue(newQ);
		printQueue(newQ);
	}

	for (int i = 0; i < 6; i++) {
		rdequeue(newQ);
		printQueue(newQ);
	}
}