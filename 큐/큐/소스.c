#include <stdio.h>
#include <stdlib.h>


#define SIZE 100
#define TRUE 1
#define FALSE 0
typedef struct intQ
{
	int max;
	int front;
	int rear;
	int *que;
}IntQ;

int initializeQ(IntQ *q, int max) {
	q->front = -1;
	q->rear = -1;
	q->que = (int*)calloc(max, sizeof(int));
	if (q->que == NULL) {
		q->max = 0;
		return -1;
	}
	q->max = max;
	return 0;
}

void terminateQ(IntQ *q) {
	

	if (q->que != NULL) {
		q->max = 0;
		free(q->que);

	}
	return;
}
int isQEmpty(IntQ *q) {
	return(q->rear == -1 && q->front == -1) ? TRUE : FALSE;
}
int isQFull(IntQ *q) {
	return(q->rear == q->max - 1 && q->rear != -1) ? TRUE : FALSE;
}

int enqueue(IntQ *q,int x) {
	if (isQFull(q))
		return -1;
	if (isQEmpty(q)) {
		q->front += 1;
		q->rear += 1;
		q->que[q->rear] = x; 
	}
	
	else
	{
		q->rear += 1;
		q->que[q->rear] = x;
	}
	return 0;

}
void printQ(IntQ *q) {
	int i,start,end;
	start = q->front;
	end = q->rear;
	if (isQEmpty(q))
		return;
	for (i = start; i <= end; i++)
		printf("%d\n", q->que[i]);
}
int dequeue(IntQ *q, int *temp) {
	if (isQEmpty(q)) {
		printf("Q is empty\n");
		return -1;
	}
	*temp = q->que[q->front];
	if (q->front == q->rear) {
		q->front = -1;
		q->rear = -1;
	}
	else
		q->front += 1;
	return 0;
}
int countQ(IntQ *q) {

	int i, cnt = 0;
	if (!isQEmpty(q)) {
		for (i = q->front; i <= q->rear; i++) {
			cnt++;
		}
	}
	return cnt;
}
int main(void) {
	IntQ myq;
	int temp;
	initializeQ(&myq, SIZE);
	if (myq.que != NULL && myq.max != 0) {
		printf("Q 초기화 성공!\n");
		printf("Q size : %d\n", myq.max);\

		if (isQEmpty(&myq))
			printf("Q is empty\n");
		else
			printf("Q is not empty\n");

		if (isQFull(&myq))
			printf("Q is Full\n");
		else
			printf("Q is not Full\n");
	}
	else {
		printf("Q 초기화 실패!\n");
		printf("Q size : %d\n", myq.max);
	}
	enqueue(&myq, 3);
	enqueue(&myq, 5);
	enqueue(&myq, 2);
	enqueue(&myq, -3);
	printQ(&myq);
	printf("No of data in Q : %d\n", countQ(&myq));
	if (dequeue(&myq, &temp) != -1)
		printf("dequeue succe! : %d\n", temp);
	if (dequeue(&myq, &temp) != -1)
		printf("dequeue succe! : %d\n", temp);
	if (dequeue(&myq, &temp) != -1)
		printf("dequeue succe! : %d\n", temp);
	if (dequeue(&myq, &temp) != -1)
		printf("dequeue succe! : %d\n", temp);
	if (dequeue(&myq, &temp) != -1)
		printf("dequeue succe! : %d\n", temp);


	terminateQ(&myq);
	return 0;
}