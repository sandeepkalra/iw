#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
	string s("sandeep"), k("deepsan");
	sort(begin(s),end(s));
	sort(begin(k),end(k));
	if(s==k) cout<<"isSame"<<endl;
	/* ------------------------------ */
	int cnt[256];
	const char *p="sandeep";
	const char *q="deepsan";
	memset(cnt, 0 , sizeof(int)*256);
	if(strlen(p) != strlen(q)) cout<<"not same";
	for(int i=0; i < strlen(p); ++i) cnt[p[i]] ++;
	for(int i=0; i < strlen(q); ++i) {
	if(cnt[q[i]] == 0) {cout<<"NOTSAME" <<endl; return false;}
		else cnt[q[i]] --;
	}
}
