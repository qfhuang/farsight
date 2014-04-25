#include <stdio.h>

int main(void)
{
	char a[10];

	fgets(a, 9, stdin);

	fputs(a, stdout);

	return 0;
}
