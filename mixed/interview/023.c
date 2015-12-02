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

void list_display(list_node *head)
{
    list_node *p = head->next;
    printf("list:");
    while(p != NULL)
    {
        printf(" %d", p->key);
        p = p->next;
    }
    printf("\n");
}

/*
** ͷ�巨
*/
list_node *list_reverse(list_node *head)
{
    list_node *p = head->next;
    list_node *q = NULL;
    head->next = NULL;
    while(p != NULL)
    {
        q = p->next;          /*������һ���ڵ�*/
        p->next = head->next; /*�ѽڵ���뵽ͷ������*/
        head->next = p;       /*ͷ���һֱָ�����²���Ľڵ�*/
        p = q;                /*����ָ�룬ָ����һ���ڵ�*/
    }
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

    list_display(head);
    list_reverse(head);
    list_display(head);
	return 0;
}
