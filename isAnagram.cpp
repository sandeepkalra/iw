#include <iostream>
#include <string>
using namespace std;

bool isAnagram(char *a, char *b)
{
	int cnt[256]; memset(cnt, 0, 256*4);
	if(strlen(a)!=strlen(b)) return false;
	char *p = a;
	while(*p!='\0') {cnt[*p]++; p++; }
	p = b;
	while(*p!='\0') { if(cnt[*p]==0) return false; cnt[*p]--; p++;}
	return true;
	
}


int main ()
{
	char * first = "depeans";
	char * second = "sandeep";
	cout<<"isAnagram: "<< isAnagram(first,second)<<endl;
}
