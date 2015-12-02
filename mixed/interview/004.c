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

list_node * list_return_node_by_key(list_node *head, int index)
{
	list_node * re = head->next;
	list_node * p = head;
	
	/*让返回节点指针先走index步*/
	int i=0;
	for(; i<index; ++i)
		p = p->next;
	
	/*遍历链表，当@l为NULL的时候@re刚好指向倒数第K个节点*/
	while(p->next != NULL)
	{
		p = p->next;
		re = re->next;
	}
	return re;
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
	
	list_node *node = list_return_node_by_key(head, 3);
	printf("node->key = %d\n", node->key);
	return 0;
}
