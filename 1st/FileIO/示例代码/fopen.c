#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
	FILE *fp = NULL;
	
//	fp = fopen("haha", "r+");
	
	if((fp = fopen("test.c", "a+")) == NULL)
	{
		fprintf(stderr, "file open failed!%s\n", strerror(errno));
		return -1;
	}

	fprintf(fp, "xixixi!%d\n", 55);

	//将标准输出重定向到haha文件
	freopen("haha", "a+", stdout);
	printf("fp->_fileno = %d\n", fp->_fileno);

//再把标准输出重定位到屏幕输出
	freopen("/dev/tty", "w+", stdout);
	printf("要下课了！\n");
	fclose(fp);
#if 0
	int i;
	for(i=0; i<300; i++ )
		printf("%d ", i);

	while(1);

#endif

	return 0;
}
