#include <stdio.h>
#include <stdlib.h>
int main()
{
	char filename[100];
	printf("\nEnter the file you want to read: ");
	scanf(" %[^\t\n]", filename);
	FILE *fp = fopen(filename, "rw");
	if(!fp) {
		printf("Cannot open file. Ending.... \n");
		return 0;
	}
	char buffer[20000];
	int index_in_buffer = 0; 
	int bytes_read = 0 ;
	int cond = 1 ;
	while(cond) {
		bytes_read = fread(buffer + index_in_buffer, 1, 100 ,fp);
		index_in_buffer += bytes_read;
		if(bytes_read <= 0 ) cond = 0;
	}
	buffer[index_in_buffer]='\0';
	
	char *p = buffer;
	for(int i=0;i<index_in_buffer;++i) printf("%c",*p++);
	
	printf("File Reading complete. Total bytes = %d", index_in_buffer);

	fclose(fp);
return 0;
}
