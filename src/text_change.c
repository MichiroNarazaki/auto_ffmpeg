#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "../gnl/get_next_line.h"
#include "../libft/includes/libft.h"

static int isDigitContinue(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == '.')
		i++;
	return (i);
}

static int open_file(int *fd, char *writefile, char *readfile)
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
	return (0);
}

//"silence_end:"を含んでいるかどうか判別
static bool contains_end(char *str, int *index)
{
	char *ans = "silence_end:";

	*index = 0;
	while (str[*index])
	{
		if (ft_strncmp(ans, str + *index, ft_strlen(ans)) == 0)
			return (true);
		(*index)++;
	}
	return (false);
}

static int write_main(int *fd)
{
	int j;
	int result;
	char *line;
	int index;
	int prefix_len = ft_strlen("silence_end:");

	j = 0;
	while (1)
	{
		j++;
		if ((result = get_next_line(fd[0], &line)) < 0) //error(-1) or EOF(0)の場合break
			break;
		if (!contains_end(line, &index))
		{
			free(line);
			if (result == 0)
				return (0);
			continue;
		}
		write(fd[1], line + index + prefix_len, isDigitContinue(line + index + prefix_len)); // ファイル書き込み
		write(fd[1], "\n", 1);																 // ファイル書き込み
		free(line);
		if (result == 0)
			break;
	}
	return (0);
}

//第2引数:読み込みファイル ,第3引数:出力ファイル
int main(int ac, char **av)
{
	int fd[2];
	char *writefile = "time.txt";

	if (ac != 2)
	{
		printf("error : bad arg num\n");
		return (-1);
	}
	if (open_file(fd, writefile, av[1]) == -1)
		return (-1);
	if (write_main(fd) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	close(fd[0]);
	close(fd[1]);
	printf("done. you can see result in %s.\n", writefile);
	return (0);
}
