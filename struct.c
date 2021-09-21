#include <stdio.h>
#include <stdlib.h>

struct List
{
	int d;
	struct List* next;
	struct List* pred;
};

void print_list(struct List* list)
{
	struct List* tmp;
	tmp = list;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->d);
		tmp = tmp->next;
	}
}

int find_elem(struct List* list, int k)
{
	struct List*  p;
	p = list;
	int i = 1;
	while (p != NULL)
	{
		if (p -> d == k)
		{
			return i;
		}
		p = p->next;
		i++;
	}
	return 0;
}

void del_value_list(struct List** tmp_p, int value)
{
	struct List* tmp_new, * tmp_t, * tmp_ui;
	tmp_t = *tmp_p;
	tmp_new = *tmp_p;
	if (*tmp_p == NULL)
	{
		return;
	}

	if ((*tmp_p) -> d == value)
	{
		*tmp_p = (*tmp_p)->next;
		if (*tmp_p != NULL) 
		{
			(*tmp_p)->pred = NULL;
		}
		free(tmp_new);
		return;
	}

	while ((tmp_new != NULL) && (tmp_new -> d != value))
	{
		tmp_t = tmp_new;
		tmp_new = tmp_new->next;
	}
	if (tmp_new != NULL)
	{
		tmp_t->next = tmp_new->next;
		if (tmp_new->next != NULL)
		{
			tmp_new->next->pred = tmp_t;
		}
		free(tmp_new);
	}
	return;
}

void add_elem(struct List** tmp_p, int elem)
{
	struct List* tmp_new, * tmp_in;
	tmp_new = (struct List*)malloc(sizeof(struct List));
	tmp_new->d = elem;

	if (*tmp_p == NULL)
	{
		*tmp_p = tmp_new;
		(*tmp_p)->pred = NULL;
		(*tmp_p)->next = NULL;
		free(tmp_new);
		return;
	}

	if (elem <= ((*tmp_p)->d))
	{
		(*tmp_p)->pred = tmp_new;
		tmp_new->next = *tmp_p;
		*tmp_p = tmp_new;
		tmp_new->pred = NULL;
		free(tmp_new);
		return;
	}
	tmp_in = *tmp_p;
	while(((tmp_in ->next) != NULL) && (elem > ((tmp_in)->next->d)))
	{
		tmp_in = tmp_in->next;
	}
	
	tmp_new->next = tmp_in->next;
	if (tmp_in->next != NULL)
	{
		tmp_in->next->pred = tmp_new;
	}
	tmp_new->pred = tmp_in;
	tmp_in->next = tmp_new;
	free(tmp_new);
	return;
}

int main(void) 
{

	struct List* p = NULL;

	int x;
	printf("Write elements, which you want to add: ");
	scanf("%d", &x);
	while (x != 0) 
	{
		add_elem(&p, x);
		scanf("%d", &x);
	}

	struct List* tmp;
	tmp = p;
	printf("Our list: \n");
	print_list(tmp);
	printf("Write element, which you want to find in the list: ");
	scanf("%d", &x);
	int f = find_elem(p, x);
	if (f == 0)
	{
		printf("Sorry, our list doesn't have this element\n");
	}
	else
	{
		printf("Number of this element in the list: %d\n", f);
	}
	printf("Write elements, which you want to delete: ");
	scanf("%d", &x);
	while (x != 0) 
	{
		del_value_list(&p, x);
		scanf("%d", &x);
	}
	tmp = p;
	printf("New list after DELETE: \n");
	print_list(tmp);

	while (p != NULL)
	{
		del_value_list(&p, p->d);
	}

	return 0;
}