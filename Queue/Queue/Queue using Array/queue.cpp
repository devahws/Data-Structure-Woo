#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

typedef int element;
typedef struct queue {
	element array[SIZE];
	int front;
	int rear;
}Queue;

Queue* init() {
	Queue* newQ = (Queue*)malloc(sizeof(Queue));
	newQ->front = -1;
	newQ->rear = -1;

	return newQ;
}

bool isEmpty(Queue* queue) {
	if (queue->front ==queue->rear)
		return true;
	else
		return false;
}

bool isFull(Queue* queue) {
	if (queue->rear == SIZE - 1)
		return true;
	else
		return false;
}

void enqueue(Queue* queue, element data) {
	if (isFull(queue)) {
		error("Queue is full");
		return;
	}
	queue->array[++queue->rear] = data;
}

element dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		error("Queue is empty");
		return -1;
	}
	element item = queue->array[++queue->front];
	return item;
		
}

void printQueue(Queue* queue) {
	int index = queue->front+1;
	if (isEmpty(queue))
		error("Queue is empty");
	else
		while (index <= queue->rear)
			printf("%d ", queue->array[index++]);
		printf("\n");
}

int main()
{
	Queue* newQue = init();
	for (int i = 0; i < 7; i++) {
		enqueue(newQue, i);
	}
	for (int i = 0; i < 3; i++) {
		dequeue(newQue);
	}
	printQueue(newQue);
}