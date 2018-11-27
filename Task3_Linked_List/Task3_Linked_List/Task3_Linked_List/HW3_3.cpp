#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>

using namespace std;

#pragma warning(disable:4996)

#define SIZE 100	// Max size of array stack
#define TRUE 1	// insted of booliantype
#define FALSE 0 // insted of bolliantype

typedef struct {
	int max; // size of array
	int top; // index of data added last
	int *stk; // address of array stack in heap
}IntStack;

// Initialize stack pointer with max array size
// Return value: 0 if succeeded; -1 if failed to get memory from heap
int initialize(IntStack *s, int max) {
	s->top = -1;
	s->stk = (int *)calloc(max, sizeof(int));
	if (s->stk == NULL) { //Failed to get memory from heap
		s->max = -1;
		return -1;
	}
	s->max = max;

	return 0;
}

// Check is stack is full
// Return TRUE(1) if stack is full; Otherwise return FALSE(0)
int isFull(IntStack *s) {
	if (s == NULL) {
		return -1;
	}
	return (s->max == s->top + 1) ? TRUE : FALSE;
}

// Check is stack is empty
// Return TRUE(1) if stack is full; Otherwise return FALSE(0)
int isEmpty(IntStack *s) {
	if (s == NULL) {
		return -1;
	}
	return (s->top == -1) ? TRUE : FALSE;
}

// Print all the data in stack
void printStack(IntStack *s) {
	for (int i = 0; i <= s->top; i++)
		printf("%d\n", s->stk[i]);

	return;
}

// Push the data
int push(IntStack *s, int x) {
	//error check
	if (isFull(s)) {
		return -1;
	}

	s->stk[s->top + 1] = x;
	s->top += 1;
	printf("Pushed data : %d \n", x);
	return 0;
}

// Pop the data
int pop(IntStack *s, int *data) {
	//error check
	if (isEmpty(s))
		return -1;

	*data = s->stk[s->top];
	printf("Poped data : %d \n", s->stk[s->top]);
	s->top -= 1;
	
	return 0;
}

// Peek the data
int peek(IntStack *s, int *data) {
	//error check
	if (isEmpty(s))
		return -1;

	*data = s->stk[s->top];

	return 0;
}

typedef struct Dnode {
	char *data;
	struct Dnode *next;
	struct Dnode *prev;
}DNode;

typedef struct Dlist {
	int datacount;
	DNode *head;		// pointer to the Dummy head
	DNode *tail;		// pointer to the Dummy tail
	DNode *crnt;		// pointer to the current node
}DList;

// Dynamically allocate memory for a node
// Set x into data member of the allocated node
// Returns pointer to newly created node, if succeeded
// Returns NULL, if failed
DNode *CreateNode(const char *x) {
	DNode *newNode;
	char *tempname;

	newNode = (DNode *)calloc(1, sizeof(DNode));
	if (newNode == NULL)
		return NULL;

	tempname = (char *)calloc(1, sizeof(x));
	if (tempname == NULL)
		return NULL;

	newNode->data = tempname;
	strcpy(newNode->data, x);
	newNode->next = NULL;
	newNode->prev = NULL;

	printf("Pushed data : %s. \n", newNode->data);
	return newNode;
}

// Initialize member values of list
void Initialize(DList *list) {
	DNode *dummyHnode;
	DNode *dummyTnode;

	dummyHnode = (DNode *)calloc(1, sizeof(DNode));
	if (dummyHnode == NULL)
		return;

	dummyTnode = (DNode *)calloc(1, sizeof(DNode));
	if (dummyTnode == NULL)
		return;

	list->head = dummyHnode;
	list->tail = dummyTnode;
	list->crnt = dummyHnode;
	list->datacount = 0;

	dummyHnode->data = NULL;
	dummyHnode->next = dummyTnode;
	dummyHnode->prev = NULL;

	dummyTnode->data = NULL;
	dummyTnode->next = NULL;
	dummyTnode->prev = dummyHnode;

	printf("List is initialized\n");
	return;
}

unsigned int CountList(DList *list) {
	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return -1;
	}
	else {
		printf("Datas in list : %d\n", list->datacount);
		return list->datacount;
	}
	return 0;
}

// Create a node with x, and then insert it at front
void Push(DList *list, const char *x)
{
	DNode *newNode;

	// 노드 생성
	newNode = CreateNode(x);

	// List is empty
	if (list->datacount == 0) {
		list->head->next = newNode;
		newNode->prev = list->head;
		newNode->next = list->tail;
		list->tail->prev = newNode;
		list->crnt = newNode;
		list->datacount++;
	}
	// List has at least one node
	else {
		newNode->next = list->head->next;
		newNode->prev = list->head;
		list->head->next->prev = newNode;
		list->head->next = newNode;
		list->crnt = newNode;
		list->datacount++;
	}
	return;
}

void Pop(DList *list) {
	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("Stack is empty.\n");
		return;
	}
	else {
		printf("Poped data : %s.\n", list->crnt->data);
		list->crnt->prev->next = list->crnt->next;
		list->crnt->next->prev = list->crnt->prev;
		free(list->crnt);
		list->datacount--;
		list->crnt = list->head->next;
		return;
	}
}

// Print all the nodes from the first node
void PrintList(DList *list)
{
	if (list->datacount == 0) {
		printf("List is empty\n");
		return;
	}
	else {
		list->crnt = list->head->next;
		for (int i = 0; i < list->datacount; i++) {
			printf("%s ", list->crnt->data);
			list->crnt = list->crnt->next;
		}
	}
	printf("\n");
	return;
}

int main(void)
{
	clock_t start, finish;
	double durationlist;
	double durationarray;

	char data[] = "data";
	int intdata = 1;

	DList list;
	IntStack stack;

	Initialize(&list);
	initialize(&stack, SIZE);

	start = clock();
	for (int i = 0; i < 1000000; i++) {
		Push(&list, data);
		Pop(&list);
	}
	finish = clock();
	durationlist = (double)(finish - start) / CLOCKS_PER_SEC;

	start = clock();
	for (int i = 0; i < 1000000; i++) {
		push(&stack, intdata);
		pop(&stack, &intdata);
	}
	finish = clock();
	durationarray = (double)(finish - start) / CLOCKS_PER_SEC;

	// 배열은 인덱스를 활용한 직접접근이 가능하지만 리스트의 경우엔 접근 방식이 모두 포인터를 활용하게 되므로
	// push와 pop의 수행시간이 배열보다 더 길어질 수 밖에 없다.
	printf("List기반 Stack의 수행 시간은 %f 초 입니다. \n", durationlist);
	printf("Array기반 Stack의 수행 시간은 %f 초 입니다. \n", durationarray);
	system("pause");
	return 0;
}