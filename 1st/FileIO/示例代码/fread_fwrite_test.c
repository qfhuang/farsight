#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	FILE *fp = NULL;
	float data[6] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
	float ret;
	
	if((fp=fopen("test.txt","wb+")) == NULL)
	{
		fprintf(stderr, "fopen fp failed!:%s\n", strerror(errno));
		return -1;
	}
	
	if(fwrite(&data[1], sizeof(float), 4, fp) != 4)
	{
		fprintf(stderr, "fwrite fp failed!:%s\n", strerror(errno));
		return -1;
	}

	printf("ftell:%ld\n", ftell(fp));
	//rewind(fp);
	fseek(fp, 4, SEEK_SET);
	printf("ftell:%ld\n", ftell(fp));
	
	if(fread(&ret, sizeof(float), 1, fp) != 1)
	{
		fprintf(stderr, "fread fp failed!:%s\n", strerror(errno));
		return -1;
	}

	printf("ret = %f\n", ret);
	
	fclose(fp);

	return 0;
}
