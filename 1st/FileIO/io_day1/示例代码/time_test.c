#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	time_t tloc;
	struct tm *ptm;

	while(1)
	{
	time(&tloc);
	
	printf("time(sec)=%ld\n", tloc);

	//ptm = localtime(&tloc);
	ptm = gmtime(&tloc);

	printf("%d-%d-%d %d:%d:%d\n", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

	printf("asctime:%s", asctime(ptm));
	printf("ctime:%s", ctime(&tloc));

	printf("\n");

	sleep(1);
	}

	return 0;
}
