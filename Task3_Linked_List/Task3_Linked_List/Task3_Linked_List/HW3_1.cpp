#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#pragma warning(disable:4996)

typedef struct node {
	int data;
	struct node *next;
}Node;

typedef struct list {
	Node *head;		// pointer to the first node in list
	Node *crnt;			// pointer to a node in list
	int datacount;
}List;

// Dynamically allocate memory for a node
// Set x into data member of the allocated node
// Returns pointer to newly created node, if succeeded
// Returns NULL, if failed
Node *CreateNode(int x) {
	Node *newNode;

	newNode = (Node *)calloc(1, sizeof(Node));
	if (newNode == NULL)
		return NULL;

	newNode->data = x;
	newNode->next = NULL;

	printf("Node with data %d is created\n", newNode->data);
	return newNode;
}

// Initialize member values of list
void Initialize(List *list) {
	list->head = NULL;
	list->crnt = NULL;
	list->datacount = 0;

	printf("List is initialized\n");
	return;
}

void Add(List *list, int item) {
	Node *temp;
	int tempdata = 0;

	temp = CreateNode(item);

	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		list->head = temp;
		list->crnt = temp;
		list->datacount++;
		printf("%d is added.\n", item);
	}
	else {
		list->crnt = list->head;
		while (list->crnt->next != NULL)
			list->crnt = list->crnt->next;

		list->crnt->next = temp;
		list->crnt = temp;
		list->datacount++;
		printf("%d is added.\n", item);
	}

	// 버블 정렬
	list->crnt = list->head;
	for (int i = 0; i < list->datacount -1 ; i++) {
		list->crnt = list->head;
		for (int j = 0; j < list->datacount-1 - i; j++) {
			if (list->crnt->data > list->crnt->next->data) {
				tempdata = list->crnt->data;
				list->crnt->data = list->crnt->next->data;
				list->crnt->next->data = tempdata;
				printf("Swaped.\n");
			}
			list->crnt = list->crnt->next;
		}
	}
}

void Delete(List *list, int item) {
	Node *temp;

	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return;
	}
	else {
		list->crnt = list->head;
		for (int i = 0; i < list->datacount; i++) {
			if (list->crnt->data == item) {
				if (list->crnt == list->head) {
					list->head = list->crnt->next;
					free(list->crnt);
					list->datacount--;
					printf("%d is deleted.\n", item);
					break;
				}
				else {
					temp = list->crnt;
					list->crnt = list->head;
					while (list->crnt->next != temp)
						list->crnt = list->crnt->next;
					list->crnt->next = temp->next;
					free(temp);
					list->datacount--;
					printf("%d is deleted.\n", item);
					break;
				}
			}
			list->crnt = list->crnt->next;
		}
	}
}

void Clear(List *list) {
	Node *temp;

	int tempcount = list->datacount;

	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return;
	}
	else {
		list->crnt = list->head;
		for (int i = 0; i < tempcount; i++) {
			temp = list->crnt->next;
			free(list->crnt);
			list->crnt = temp;
			list->datacount--;
		}
		printf("All data has been deleted.\n");
		return;
	}
}

int IsInList(List *list, int item) {

	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return -1;
	}
	else {
		list->crnt = list->head;
		for (int i = 0; i < list->datacount; i++) {
			if (list->crnt->data == item) {
				printf("Item exists.\n");
				return 1;
			}
			else 
				list->crnt = list->crnt->next;
		}
	}
	printf("Item does not exist.\n");
	return 0;
}

unsigned int GetLength(List *list) {
	printf("List length : %d\n", list->datacount);
	return list->datacount;
}

int IsEmpty(List *list) {

	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return true;
	}
	else {
		printf("List is not empty.\n");
		return false;
	}
}

// Print all the nodes from the first node
void Display(List *list)
{
	Node *temp;

	// 리스트가 비어 있는 경우
	if (list->datacount == 0) {
		printf("List is empty.\n");
		return;
	}

	temp = list->head;

	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
	return;
}

int main(void)
{
	int flag = 0;

	List list;

	Initialize(&list);

	while (flag != -1) {
		int temp = 0;
		switch (flag) {
		case 0:
			printf("1: Add // 2: Delete // 3: Clear // 4: Isinlist // 5: Getlength // 6: Isempty // 7: Display // -1: Exit => ");
			cin >> flag;
			break;
		case 1:
			printf("Input add data : ");
			cin >> temp;
			Add(&list, temp);
			flag = 0;
			break;
		case 2:
			printf("Input delete data : ");
			cin >> temp;
			Delete(&list, temp);
			flag = 0;
			break;
		case 3:
			Clear(&list);
			flag = 0;
			break;
		case 4:
			printf("Input serach data : ");
			cin >> temp;
			IsInList(&list, temp);
			flag = 0;
			break;
		case 5:
			GetLength(&list);
			flag = 0;
			break;
		case 6:
			IsEmpty(&list);
			flag = 0;
			break;
		case 7:
			Display(&list);
			flag = 0;
			break;
		}
	}
	return 0;
}