#include "ll.h"

int main(void) {
	struct node* pHead = initList();
    
	addItem(pHead, (int*)2);
	addItem(pHead, (int*)10);
	addItem(pHead, (int*)12);
	addItem(pHead, (int*)13);

	printList(pHead);

	destroyList(&pHead);

	return 0;
}
