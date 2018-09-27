#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
#define TRUE 1
#define FALSE 0
typedef struct intStack {
	int max; //stack array size
	int top; //lastly inserted data index in array
	int *stk;
} IntStack;

int initialize(intStack *s, int max)
{
	s->top = -1;
	s->stk = (int *)calloc(max, sizeof(int));
	if (s->stk == NULL)
	{
		s->max = 0;
		return -1;
	}

	s->max = max;
	return 0;
}

int isFull(intStack *s)
{
	return s->top + 1 == s->max ? TRUE : FALSE;
}
int push(IntStack *s, int x)
{
	if (isFull(s))
		return -1;

	s->top += 1;
	s->stk[s->top] = x;

	return 0;
}
int isEmpty(intStack *s)
{
	return s->top == -1 ? TRUE : FALSE;
}
int pop(IntStack *s, int *x) {
	if (isEmpty(s)) 
		return -1;
	
	*x = s->stk[s->top];
	s->top -= 1;
}
void printStack(IntStack *s)
{
	int i;
	if (isEmpty(s))
		printf("No data\n");
	for (i = 0; i <= s->top;i++)
		printf("%d\n", s->stk[i]);
	return;
}
void peek(IntStack *s, int *x) {
	if (isEmpty(s))
		return;

	*x = s->stk[s->top];
	s->top -= 1;
}
void terminate(intStack *s) {
	if(s->stk!=NULL)
		free(s->stk);
	s->max = 0;
	return;
}

int main(void)
{
	intStack mystack;
	int temp; //To store int value

	initialize(&mystack, SIZE);
	if (mystack.stk != NULL)
		printf("Array-based stack is succeeded!! size %d\n", mystack.max);

	if (isEmpty(&mystack))
		printf("Stack is empty\n");
	else
		printf("Stack is not empty\n");
	push(&mystack, 1);
	push(&mystack, 3);
	push(&mystack, 5);
	push(&mystack, 7);
	printStack(&mystack);
	if (pop(&mystack, &temp) != -1) 
		printf("Date %d is popped!!\n", temp);

	if (pop(&mystack, &temp) != -1)
		printf("Date %d is popped!!\n", temp);

	printStack(&mystack);
	
	terminate(&mystack);
	return 0;
}