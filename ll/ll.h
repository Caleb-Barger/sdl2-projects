#include <stdio.h>
#include <stdlib.h>

struct node {
	void* value;
	struct node* next;
};

struct node* initList();
void addItem(struct node*, void*);
void printList(struct node*);
void destroyList(struct node**);





struct node* initList() {

	struct node* pHead = malloc(sizeof(struct node));
	pHead->value = (int*)0;
	pHead->next = NULL;

	return pHead;
}

void addItem(struct node* h, void* foo) {

	while(h->next != NULL) {
		h = h->next;
	}

	struct node* newNode = malloc(sizeof(struct node));
	newNode->next = NULL;
	newNode->value = foo;

	h->next = newNode;
}

void printList(struct node* h) {
	printf("%d -> ", (int*)h->value); 
	if (h->next) printList(h->next);
	else printf("N\n");
}

void destroyList(struct node** h) {
	struct node* pNext;
	struct node* pCurr = *h;

	while (pCurr->next != NULL) {
		pNext = pCurr->next;
		free(pCurr);
		pCurr = pNext;    
	}

	free(pCurr);
	*h = NULL;
}
