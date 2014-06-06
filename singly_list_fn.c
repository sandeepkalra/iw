#include <stdio.h>
#include <stdlib.h>

#define PASS (0)
#define FAIL (-1)

struct node {
 struct node*next;
 int data;
};

struct node*start=0;


int Insert_end(int v)
{
	if(!start)
	{
		start=malloc(sizeof(struct node));
		if(!start) return FAIL;
		start->next = 0; start->data=v;
		return PASS;
	}
	struct node *p = start;
	while(p->next) p = p->next;
	p->next = malloc(sizeof(struct node));
	if(!p->next) return FAIL;
	p->next->next = 0; p->next->data = v;
	return PASS;
}

int Del(int v)
{
	if(start->data == v) {
		struct node *new_start = start->next;
		free(start); start = new_start;
		return PASS;
	} 
	struct node *p=start;
	while(p->next) {
		if(p->next->data == v) break; else p = p->next;
	}
	if(p && p->next->data == v){
		struct node*next= p->next->next;
		free(p->next);
		p->next = next;
		return PASS;
	}
	return  FAIL;
}

void destroy_all()
{
	while(start) {
		struct node*new_start=start->next;
		free(start);
		start=new_start;
	}
}

int find(int n)
{
	struct node * p = start;
	while(p && p->data != n) p = p->next;
	if(!p) return FAIL; else return PASS;
}

int has_loop()
{
	struct node *p = start;
	struct node *pp = start;
	while(p && pp) { p = p->next; if(p) pp=p->next; if(pp == p) return PASS; }
	return FAIL;
}

void Insert_front(int n)
{
	struct node * p = malloc(sizeof(struct node));
	p->data = n;
	p->next = start;
	start = p;
}

struct node* reverse()
{
	struct node *new_list_head = 0;

	while(start) {
		struct node *p = new_list_head;
		new_list_head  = start;
		new_list_head->next = p;
		start = start->next;
	}
	return new_list_head;
}

void print_all()
{
	struct node *p = start;
	while(p) { printf("%d \n",p->data); p=p->next; }
}

int main()
{
	Insert_front(10);
	Insert_end(100);
	Insert_front(4);
	Insert_end(400);
	Del(10);
	Del(4);
	print_all();
	destroy_all();
}
