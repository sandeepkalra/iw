#include <stdio.h>
#include <stdlib.h>


struct node {
	struct node *prev;
	struct node *next;
	int data;
};

struct node *start;

void Insert(int i)
{
	if(!start)
	{
		start=malloc(sizeof(struct node*));
		start->prev = 0;
		start->next = 0;
		start->data = i; 
	} else {
		struct node *p = start;
		while (p->next) p = p->next;
		p->next = (struct node *) malloc(sizeof(struct node));
		p->next->next = 0;
		p->next->data = i;
		p->next->prev = p;
	}
}

void Delete(int i)
{
	if(!start) return;
	struct node *p = start;
	while(p && p->data != i) p = p->next;
	if(p && p->data==i) {
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
	}
}

void DeleteAll()
{
	while(start) {
		struct node *p = start->next;
		free(start);
		start = p;
	}
}

#define FOUND (0)
#define NOTFOUND (-1)
int Find(int i)
{
	struct node *p = start;
	while(p && p->data !=i ) p=p->next;
	if(p &&p->data ==i ) return FOUND;
return NOTFOUND;
}


void Reverse()
{
    struct node *temp = NULL; 
     struct node *current = start;
      
     /* swap next and prev for all nodes of
       doubly linked list */
     while (current !=  NULL)
     {
       temp = current->prev;
       current->prev = current->next;
       current->next = temp;             
       current = current->prev; //tricky, current->prev is now the new-current!!!!
     }     
      
     /* Before changing head, check for the cases like empty
        list and list with only one node */
     if(temp != NULL )
        start = temp->prev;
} 

void Printall(char *msg)
{
	struct node *p = start;
	printf("\n%s\n",msg);
	while(p) 
	{ 
			printf(" %x: content %d \n",p , p->data); 
			p = p->next; 
	}
}
void ReverseRecurrsion()
{
}		

int main ()
{
	Insert(1);
	Insert(2);
	Insert(10);
	Insert(12);
	Printall("before reverse");
	Reverse();
	Printall("after reverse");
}

	
	
	
