#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
	FILE *fp = NULL;
	char ch;
	
	
	if((fp = fopen("test.c", "a+")) == NULL)
	{
		fprintf(stderr, "file open failed!%s\n", strerror(errno));
		return -1;
	}
	
	while(!feof(fp) && !ferror(fp))
	{
		ch = fgetc(fp);
		if(ch != EOF)
			putchar(ch);

	}
	
	fclose(fp);
	return 0;
}
