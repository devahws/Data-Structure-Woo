// Array를 사용한 Deque를 Double linked list처럼 운용하는 프로그램
#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

void error(const char* message) {
	fprintf(stderr, "%s\n", message);
}

typedef int element;
typedef struct queue {
	element* array;
	int front;
	int rear;
	int size;
}Queue;

Queue* init() {
	Queue* newQ = (Queue*)malloc(sizeof(Queue));
	newQ->size = SIZE;
	newQ->array = (element*)malloc(sizeof(element) * SIZE);
	newQ->front = 0;
	newQ->rear = 0;

	return newQ;
}

bool isEmpty(Queue* queue) {
	if (queue->front == queue->rear)
		return true;
	else
		return false;
}

bool isFullrear(Queue* queue) {
	if (queue->rear == queue->size - 1)
		return true;
	else
		return false;
}

bool isFullfront(Queue* queue) {
	if (queue->front == 0)
		return true;
	else
		return false;
}

void enqueue(Queue* queue, element data) {
	if (isFullrear(queue)) {
		error("queue is full rear. reallocation");
		queue->size *= 2;
		queue->array = (element*)realloc(queue->array, sizeof(element) * queue->size);
		queue->array[queue->rear] = data;
		queue->rear++;
	}
	else {
		queue->array[queue->rear] = data;
		queue->rear++;
	}
}

void fenqueue(Queue* queue, element data) {
	if (isFullfront(queue)) {
		error("queue is full front. reallocation");
		int size = queue->size;
		queue->size *= 2;
		element* rarray = queue->array;
		element* newarr = (element*)malloc(sizeof(element) * queue->size);
		int i = 0;
		while (i < queue->rear) {
			newarr[i + size] = queue->array[i];
			i++;
		}
		newarr[size - 1] = data;
		queue->front = size - 1;
		queue->rear = queue->rear + size;
		queue->array = newarr;
		free(rarray);
	}
	else {
		queue->array[--queue->front] = data;
	}
}

element dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		error("Queue is empty");
	}
	else {
		element item = queue->array[++queue->front];
		return item;
	}
}

element rdequeue(Queue* queue) {
	if (isEmpty(queue))
		error("Queue is empty");
	else {
		element item = queue->array[--queue->rear];
		return item;
	}
}

void printQueue(Queue* queue) {
	int index = 0;
	if (isEmpty(queue)) {
		while (index < queue->size) {
			printf(" |");
			index++;
		}
	}
	else
		while (index < queue->size) {
			if (index < queue->front || index >= queue->rear) {
				printf(" |");
				index++;
			}	
			else
				printf("%d|", queue->array[index++]);
		}
			
	printf("\n");
}

int main()
{
	Queue* newQue = init();
	for (int i = 0; i < 4; i++) {
		fenqueue(newQue, i);
		printQueue(newQue);
	}

	for (int i = 0; i < 3; i++) {
		dequeue(newQue);
		printQueue(newQue);
	}
	
	for (int i = 0; i < 6; i++) {
		enqueue(newQue, i);
		printQueue(newQue);
	}

	for (int i = 0; i < 7; i++) {
		rdequeue(newQue);
		printQueue(newQue);
	}
}