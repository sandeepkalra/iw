#include <stdio.h>

int StrLen(const char *s)
{
  int sz=0;
  char *p = s;
  while(p && *p!='\0') { sz++; p++;}
  return sz;
}

void StrCpy(char *dest, char *src)
{
  while((*dest++ = *src++) != '\0') { }
}


int main() 
{
}
