#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct node {
	char c;
	bool isEnd; 
	node *next[256];
	node(char ch) : c(ch) 
	{ 
		memset(this->next, 0 , sizeof(node*)*256); 
		if(c=='$') 
			isEnd = true; 
		else isEnd=false;
	}
};

static node start('%');

void Insert(const char *c)
{
	if(!c) return;
	char *s=const_cast<char*>(c);
	node *curr = &start;
	
	while(*s != '\0' && curr) 
	{
		node *next = curr->next[tolower(*s)];
		if(next == nullptr) 
		{ 			
			curr->next[tolower(*s)] = new node(*s); 
		}
		curr = curr->next[tolower(*s)];		
		++s; 		
	}
	curr->next['$'] = new node('$');
}

bool Find(const char *c)
{
	char *s=const_cast<char*>(c);
	node *curr = &start;

	while(*s!='\0' && curr) 
	{ 
		curr = curr->next[tolower(*s)];
		s++;
	}
	if(*s=='\0' && curr && curr->next[tolower('$')]->isEnd) 
		return true; 
	else 
		return false;
}

int main()
{
	string names[]={"india","delhi","gurgaon"};
	for(int i=0; i<3;++i) Insert(names[i].c_str());
	cout<<"Find(Delhi)="<<Find(string("Delhi").c_str())<<endl;
	cout<<"Find(USA)="<<Find(string("USA").c_str())<<endl;
}
