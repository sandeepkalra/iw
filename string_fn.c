#include <stdio.h>
#include <stdlib.h>

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

char *StrDup(char *s, int sz)
{
	char *p = (char*) malloc(sz+1);
	if(!p) return 0;
	StrCpy(p,s);
	p[sz]='\0';
	return p;
}
char *StrCat(char *Dest, char *Src) /*Dest big-enough to hold additional Src char */
{
	char *p = Dest; 
	int sz_d = StrLen(Dest);
	int sz_s = StrLen(Src);
	int i=0;
	for(i=0 ; i < sz_s ; ++i) Dest[i + sz_d ] =  Src[i];
	Dest[sz_d + sz_s] = '\0';
	return p;
}

char *StrReverse(char *Src)
{
	int sz = StrLen(Src);
	int i=0;
	while(i<sz/2) {
		char t = Src[i];
		Src[i] = Src[sz-i-1];
		Src[sz-i-1] = t;
		i++;
	}
	return Src;
}

char *StrNReverse(char *Src, int n)
{
	int sz = StrLen(Src);
	int i=0;
	if (n>sz) n = sz;
	while(i<n/2) {
		char t = Src[i];
		Src[i] = Src[n-i-1];
		Src[n-i-1] = t; i++;
	}
	return Src;
}

char *StrWordReverse(char *src)
{
	int sz = StrLen(src);//we need to do end-of loop.
	char *reverse = StrReverse(src);//Reverse Everything.
	// now look for delimter  = ' ' (space). and then reverse from currrect to that .
	char *p = reverse;
	char c = ' ';
	while(p && *p!='\0') {
		char *word_end= StrChr(p,c);
		int sz_word = word_end - p;
		p = StrNReverse(p,sz_word);
		p = p + sz_word + 1 ;
	}
	return reverse;
}

int main() 
{	
	char arr[] = "This is a string that need some reversal";
	char arr1[] = "1234 5678 9101112" ;
	printf("%s \n" , StrWordReverse(arr));
	printf("%s \n" , StrWordReverse(arr1));
}
