#include <stdio.h>

int StrLen( char *p)
{
  int sz=0;
  while(p && *p!='\0') { sz++; p++;}
  return sz;
}

void StrCpy(char *dest, char *src)
{
  while((*dest++ = *src++) != '\0') { }
}

int StrCmp( char *p,  char *q) 
{
  while(*p!='\0' && *q!= '\0' && (*p++ == *q++)) { }
  return (*p-*q);
}

char *StrStr(char *hay, char *needle)
{
	int i=0;
	int sz_h = StrLen(hay); 
	int sz_n = StrLen(needle);
	if(sz_h < sz_n) return 0;
	for(i =0 ; i < sz_h - sz_n + 1; ++i)
	{
		int j=0;
		for(j=0;j<sz_n;++j)
		{
			if(hay[i+j]!=needle[j]) break;
		}
		if(j==sz_n) return &hay[i];
	}
	return 0;
}

char *StrChr(char *hay, char c)
{
	while(*hay!= '\0' && (*hay != c)) { hay++; }
	return hay;
}

int main() 
{
}
