#include <stdio.h>
#include <stdlib.h>

typedef struct _data
{
	int value;
	int min;
}data;

typedef struct _stack
{
	int top;
	int calloc_size;
	data *data;
}stack_t;

stack_t * stack_init(int size)
{
	stack_t *re = calloc(1, sizeof(stack_t));
	re->top = 0;
	re->calloc_size = size;
	re->data = calloc(size, sizeof(data));
}

void stack_free(stack_t *s)
{
	if(s)
	{
		if(s->data)
			free(s->data);
		free(s);
	}
}

void stack_push(stack_t *s, int value)
{
	data data;
	if(s->top == 0)
	{
		data.min = value;
	}
	else
	{
		if(s->data[s->top - 1].min > value)
			data.min = value;
	}
	data.value = value;
	s->data[s->top++] = data;
}

int stack_pop(stack_t *s)
{
	if(s->top == 0)
		return 0;
	
	return s->data[--(s->top)].value;
}

int stack_min(stack_t *s)
{
	if(s->top == 0)
		return 0;

	return s->data[s->top - 1].min;
}

int main()
{
	stack_t *s = stack_init(8);
	stack_push(s, -1);
	stack_push(s, 1);
	stack_push(s, -10);
	stack_push(s, 15);
	stack_push(s, 17);
	stack_push(s, -11);
	stack_push(s, -100);
	stack_push(s, 100);
	printf("min---->%d\n", stack_min(s));

	while(s->top)
	{
		printf("pop---->%d\n", stack_pop(s));
	}
	stack_free(s);
	return 0;
}

