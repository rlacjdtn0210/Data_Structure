#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

using namespace std;

#pragma warning(disable:4996)

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

	printf("Node with data %s is created\n", newNode->data);
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
void Insert(DList *list, const char *x)
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
		list->datacount++;
	}
	// List has at least one node
	else {
		newNode->next = list->head->next;
		newNode->prev = list->head;
		list->head->next->prev = newNode;
		list->head->next = newNode;
		list->datacount++;
	}
	return;
}

DNode *Search(DList *list, const char *str) {
	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return NULL;
	}
	else {
		list->crnt = list->head->next;
		for (int i = 0; i < list->datacount; i++) {
			if (strcmp(list->crnt->data, str) == 0) {
				printf("Find the app.\n");
				return list->crnt;
			}
			else
				list->crnt = list->crnt->next;
		}
	}
	printf("No app found.\n");
	return NULL;
}

void Remove(DList *list, DNode *p) {
	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return;
	}
	else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
		list->datacount--;
		list->crnt = list->head;
		printf("Found app is removed.\n");
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
	int flag = 0;

	DList list;
	DNode *temp = NULL;

	Initialize(&list);

	while (true) {
		char appname[] = { 0 };
		switch (flag) {
		case 0:
			printf("1: Insert // 2: Remove // 3: Search // 4: CountList // 5: PrintList // -1: Exit => ");
			cin >> flag;
			break;
		case 1:
			printf("Input app name : ");
			scanf("%s", appname);
			Insert(&list, appname);
			flag = 0;
			break;
		case 2:
			if(temp == NULL) printf("No searched apps.\n");
			else Remove(&list, temp);
			flag = 0;
			break;
		case 3:
			printf("Input appname for search : ");
			scanf("%s", appname);
			temp = Search(&list, appname);
			flag = 0;
			break;
		case 4:
			CountList(&list);
			flag = 0;
			break;
		case 5:
			PrintList(&list);
			flag = 0;
			break;
		case -1:
			exit(1);
		}
	}
	return 0;
}