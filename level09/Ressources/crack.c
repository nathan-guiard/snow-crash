#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **argv)
{
		static char	str[40];

		int fd = open(argv[1], O_RDONLY);
		if (fd <= 0)
				return (1);
		read(fd, str, 40);
		int i = 0;
		while (str[i])
		{
				str[i] -= i;
				i++;
		}
		printf("%s\n", str);
}
