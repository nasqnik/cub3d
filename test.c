#include <fcntl.h>
#include <unistd.h>

int	main()
{
	int fd;

	fd = open("./src/texture1.txt\n", O_RDONLY);
	if (fd != -1)
		write(1, "OK\n" , 3);
	else
		write(1, "BAD\n", 3);
	
	close (fd);
	return 0;
}