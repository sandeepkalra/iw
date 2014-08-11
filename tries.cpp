#include <iostream>
#include <string>
using namespace std;

struct node {
	char c;
	bool isEnd; 
	node *next[256];
	node(char ch) : c(ch) { memset(next,0, sizeof(node)*256); }
};

static node start('%');

void Insert(const char *c)
{
	if(!c) return;
	char *s = c;
	node *p = start.next[tolower(*s)];
	
	while(*s!='\0') {
		if(!p) p = new node(*s);
		s++;
		if(*s != '\0') p = p->next[tolower(*s)];
	}
	p->isEnd = true;
}

bool Find(const char *c)
{
	char *s=c;
	node *p = start.next[tolower(*s)];
	while(*s!='\0' && p) { s++; p = p->next[tolower(*s)]; }
	if(*s=='\0' && p && p->isEnd) return true; else return false;
}

int main()
{
	string names[]={"sandeep","kalra","gurgaon"};
	for(auto i: names) Insert(i.c_str());
	cout<<"Find(SANDEEP)="<<Find(string("SANDEEP").c_str())<<endl;
}
