#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	FILE *fp = NULL;
	int count = 0;
	int ch;
	char buf[BUFSIZ];
	time_t tloc;
	struct tm *ptm;

	//如fp==NULL，说明打开文件失败
	if((fp = fopen("time.txt", "a+")) == NULL)
	{
		//进行出错处理
		fprintf(stderr,"open failed!%s\n", strerror(errno));
		return -1;
	}

	while(!feof(fp) && !ferror(fp))
	{
		ch = fgetc(fp);
		if(ch == '\n')
			count++;
	}

	while(1)
	{
		time(&tloc);
		ptm = localtime(&tloc);

		sprintf(buf, "%d: %d-%d-%d %d:%d:%d\n", count++, 
				ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
				ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

		fprintf(fp,"%s", buf);
		fprintf(stdout,"%s\n", buf);

		fflush(fp);

		sleep(1);
	}

	return 0;
}
