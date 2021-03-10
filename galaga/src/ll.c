#include "ll.h"

struct node_t* LL_init() {
	struct node_t* pHead = malloc(sizeof(struct node_t));
	pHead->value = NULL;
	pHead->next = NULL;

	return pHead;
}

void LL_append(struct node_t* h, void* foo) {
	while(h->next != NULL) {
		h = h->next;
	}

	if (h->value == NULL) {
		h->value = foo;
		return;
	}

	struct node_t* newNode = malloc(sizeof(struct node_t));
	newNode->next = NULL;
	newNode->value = foo;

	h->next = newNode;
}

void LL_remove(struct node_t* h) {
	while(h->next->next != NULL) {
		h = h->next;
	}

	h->next = NULL;
}

void LL_print(struct node_t* h) {
	printf("%d -> ", (int*)h->value); 
	if (h->next) LL_print(h->next);
	else printf("N\n");
}

void LL_destroy(struct node_t** h) {
	struct node_t* pNext;
	struct node_t* pCurr = *h;

	while (pCurr->next != NULL) {
		pNext = pCurr->next;
		free(pCurr);
		pCurr = pNext;    
	}

	free(pCurr);
	*h = NULL;
}
