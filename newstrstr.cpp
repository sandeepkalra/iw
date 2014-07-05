#include <iostream>
#include <assert.h>

using namespace std;

#define MAX(a,b) ((a>b)?(a):(b))

class CStringSearch {

	int jmp [255];	
	int key [255];	

	int strlen(char *s) {
		int l = 0;
		assert(s);
		while (*s++ != '\0') l++;
		return l;
	}

	void ProcessPattern(char *pattern, int sz)
	{
		char *p = pattern;
		int index=0;
		for (int i=sz-1;i>=0;--i)
		{
			key[i] = static_cast<int> (*(p+i));
			jmp[i] =  MAX(1, sz - 1 - i);
		}
	}
	

public:
	CStringSearch() { for (int i = 0; i < 255; ++i) jmp[i] = 0; }
	char *strstr(char *text, char *needle)
	{
		assert(text); 
		assert(needle);
		char *p = text;
		int sz_t = strlen(text);
		int sz_p = strlen(needle);
		int j = 0;
		ProcessPattern(needle, sz_p);
		int skip = 0;
		for (int i = 0; i < (sz_t - sz_p + 1); i+=skip)
		{
			skip = 0;
			p = p+i;
			for (j = 0; j != (sz_p - 1); ++j)
			{
				if (*(needle+j) != *(p+j))
				{
					skip = jmp[j];
					if (skip == 0) skip = sz_p;
					break;
				}
			}
			if (j == 0) return &text[i];
		}
		return 0;
	}
};

int main()
{
	char *p = "needle";
	char *t = "finding the needle in hay using Boyce Moore's Algorithm!";
	CStringSearch searcher;
	char * answer  = searcher.strstr(t, p);
	if(answer) cout << answer << endl;
	else cout << "not found!"<<endl;
	return 0;
}
