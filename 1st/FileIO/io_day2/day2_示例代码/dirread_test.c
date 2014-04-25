
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

int main(void)
{
	DIR *dp;
	struct dirent* dsp;

	dp = opendir(".");

	while((dsp = readdir(dp)) != NULL)
		printf("%s ", dsp->d_name);


	return 0;
}
