#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>

struct node_t{
	void* value;
	struct node_t* next;
};

struct node_t* LL_init(void);
void LL_append(struct node_t* head, void* item);
void LL_remove(struct node_t* head);
void LL_print(struct node_t* head);
void LL_destroy(struct node_t** head);


#endif
