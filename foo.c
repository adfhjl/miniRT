#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int		fd;
	char	buf[3];

	(void)argc;
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		printf("access() error:\n");
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("open() error:\n");
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	if (read(fd, buf, 2) == -1)
	{
		printf("read() error:\n");
		close(fd);
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	close(fd);
	if (buf[0] == 'a')
	{
		if (buf[1] == 'b')
		{
			void	*ptr = malloc(1);
			free(ptr);
			free(ptr);
			printf("Double free'd! %p\n", ptr);
		}
	}
	buf[2] = '\0';
	printf("<%s>\n", buf);
	return (EXIT_SUCCESS);
}
