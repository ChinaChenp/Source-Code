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

void list_delete(list_node *del_node)
{
	list_node *p = del_node->next;
	del_node->key = p->key; /*copy data*/
	del_node->next = p->next;
	free(p);
}

void list_dispaly(list_node *head)
{
	list_node *p = head->next;
	printf("list:");
	while(p)
	{
		printf(" %d", p->key);
		p = p->next;
	}
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

	list_dispaly(head);	
	list_delete(head->next->next);
	list_dispaly(head);	
	return 0;
}
