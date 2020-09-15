#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "gnl/get_next_line.h"
#include "libft/includes/libft.h"


int open_file(int *fd, char *writefile, char *readfile)
{
	fd[0] = open(readfile, O_RDONLY);
	if (fd[0] < 0)
	{
		printf("error : Reading file is already exist\n");
		return (-1);
	}
	fd[1] = open(writefile, O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);
	if (fd[1] < 0)
	{
		printf("error : Writing file is already exist\n");
		return (-1);
	}
	return 0;
}

int main()
{
	int fd[2];
	char *writefile="time"
	return 0;
}