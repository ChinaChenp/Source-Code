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


list_node *list_init()
{
	list_node *head = calloc(1, sizeof(list_node));
	head->key = 0;
	head->next = NULL;

	return head;
}

/*
** 带头结点的链表合并:大致思想是用一个虚拟节点顺序(升序)串联两个链表中的
** 节点,每次记录当前节点的位置
** h1-->:   1---4---7 ---12 
** h2-->:   3---9---13---14
*/
list_node *list_merger(list_node *h1, list_node *h2)
{
	if(!h1)	return h2;
	if(!h2) return h1;

	/*
	** @head节点记录两个链表中较小的那个头结点
	*/
	list_node * head;
	if (h1->key > h2->key) 
	{
		head = h2;   
		h2 = h2->next;
	}
	else
	{
		head = h1; 
		h1 = h1->next;
	}

	list_node * current = head;
	while (h1 != NULL || h2 != NULL) 
	{
		/*
		** current节点一直指向最后连接的节点
		** (1)如果链表@h1先遍历完,直接把链表@h2后面节点连接到@current后面
		*/
		if (h1 == NULL || (h2 != NULL && h1->key > h2->key)) 
		{
			current->next = h2;      /*把@h2节点连接到@current节点后面*/ 
			current = current->next; /*调整@current指针,指向最新连接的节点*/
			h2 = h2->next;           /*过滤掉已经被连接过的节点*/
		}
		else 
		{
			current->next = h1; 
			current = current->next;
			h1 = h1->next;
		} 
	}
	current->next = NULL;
	return head->next;
}

void list_display(list_node *head)
{
    list_node *p = head->next;
    printf("list:");
	int count = 0;
    while(p != NULL)
    {
        printf(" %d", p->key);
        p = p->next;
		count++;
    }
	printf(" --->[%d]", count);
    printf("\n");
}

int main(int argc, char *argv[])
{
	list_node *list1 = list_init();
	list_node *list2 = list_init();

	list_insert(list1, 1);
	list_insert(list1, 4);
	list_insert(list1, 7);
//	list_insert(list1, 12);
//	list_insert(list1, 19);
	list_insert(list1, 61);
	
	list_insert(list2, 3);
	list_insert(list2, 9);
	list_insert(list2, 13);
//	list_insert(list2, 14);
//	list_insert(list2, 61);

    list_display(list1);
    list_display(list2);

	list_node *all = list_merger(list1, list2);
	list_display(all);

	return 0;
}
