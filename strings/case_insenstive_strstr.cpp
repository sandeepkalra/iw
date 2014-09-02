#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX(a,b) ((a>b)?(a):(b))

char *strIstr(char *text, char *needle)
{
	int sz_t = 0;
	int sz_p = 0;
	int skip = 0;
	int i=0,j=0, index = 0;
	char *n = needle;
	static int jmp [256];	//UTF-8 chars

	if(!text) return 0; 
	if(!needle) return 0;

	sz_t = strlen(text);
	sz_p = strlen(needle);
	
	memset(jmp,0,sizeof(jmp)*sizeof(int));

	while (*n != '\0') /* BM Table */
	{
		i = (int)(tolower(*n));
		jmp[i] = MAX(1, sz_p - 1 - index);
		index++;
		n++;
	}

	for (i = 0; i < (sz_t - sz_p + 1); i+=skip)
	{
		skip = 0;
		for (j = sz_p-1; j >= 0; --j)
		{
			if (tolower(text[i + j]) != tolower(needle[j]))
			{
				skip = jmp[(int)(tolower(text[i + j]))];
				if (skip == 0) skip = sz_p;
				break;
			}
		}
		if (j < 0) return &text[i];
	}
	return 0;
}

int main()
{
	char *p = "Needle";
	char *t = "Finding Needle in hay";
	char * answer  = strIstr(t, p);
	if(answer) printf("%s\n", answer);
	else printf(" String not found \n");
	return 0;
}
