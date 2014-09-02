#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZEOF_Data(data) ( (char *)(&data +1) - (char *)(&data))
#define SIZEOF_Type(T) ((T*)0 + 1)
#define ALIGN16(p) (void*)(((uintptr_t)p +15) & ~ (uintptr_t)0x0f)
#define ALIGN32(p) (void*)(((uintptr_t)p +31) & ~ (uintptr_t)0x00ff)

struct node {
	char c;
	short s;
	int i;
};

int main()
{
	int i=0;
	printf("%d ",SIZEOF_Data(i)); 
	printf("%d ",SIZEOF_Type(struct node)); 
	char *mem = malloc(100);
	void *ptr = ALIGN32(mem);
	printf("%p, %p \n", mem, ptr);
}

