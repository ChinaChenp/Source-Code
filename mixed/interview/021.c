#include <stdio.h>
#include <stdlib.h>

typedef struct _list_node
{
	int        key;
	struct _list_node  *next;
}list_node;

void *list_insert(list_node *head, int key)
{
	list_node *p = head;
	while(p->next != NULL)
		p = p->next;
	list_node *node = calloc(1, sizeof(list_node));
	node->key = key;
	node->next = NULL;

	p->next = node;
}

void reverse_display(list_node *head)
{
	list_node *p = head->next;
	if(head->next != NULL)
		reverse_display(head->next);
	printf(" %d", head->key);
	printf("\n");
}

int main(int argc, char *argv[])
{
	list_node *head = calloc(1, sizeof(list_node));
	head->key = 0;
	head->next = NULL;

	list_insert(head, 1);	
	list_insert(head, 2);	
	list_insert(head, 3);	
	list_insert(head, 4);	
	list_insert(head, 5);
	
	reverse_display(head);
	free(head);
	return 0;
}
