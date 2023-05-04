#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int ac, char **argv)
{
	int i = 0;
	while (argv[1][i])
	{
		argv[1][i] -= i;
		i++;
	}
	printf("%s\n", argv[1]);
}
