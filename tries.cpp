#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct node {
	char c;
	bool isEnd; 
	node *next[256];
	node(char ch) : c(ch) { memset(this->next, 0 , sizeof(node*)*256); if(c=='$') isEnd = true; }
};

static node start('%');

void Insert(const char *c)
{
	if(!c) return;
	char *s=const_cast<char*>(c);
	node *curr = (&start)->next[tolower(*s)];
	while(*s != '\0') 
	{
		if(curr == nullptr) 
		{ 
			curr = new node(*s); 
		}
		++s; 
		curr = curr->next[tolower(*s)];
	}
	curr = new node('$');
}

bool Find(const char *c)
{
	char *s=const_cast<char*>(c);
	node *p = start.next[tolower(*s)];
	while(*s!='\0' && p) { p = p->next[tolower(*s)]; ++s; }
	if(*s=='\0' && p && p->isEnd) return true; else return false;
}

int main()
{
	string names[]={"sk","sandeep","gurgaon"};
	for(auto i: names) Insert(i.c_str());
	cout<<"Find(SANDEEP)="<<Find(string("SANDEEP").c_str())<<endl;
}
