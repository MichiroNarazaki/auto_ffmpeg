#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "../gnl/get_next_line.h"
#include "../libft/includes/libft.h"

int isDigitContinue(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == '.')
	{
		i++;
	}
	return (i);
}

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

//"silence_end:"を含んでいるかどうか判別
bool contains_end(char *str, int *index)
{
	char *ans = "silence_end:";

	*index = 0;
	while (str[*index])
	{
		if (ft_strncmp(ans, str + *index, ft_strlen(ans)) == 0)
		{
			// printf("\ncontains end in this : %s\n", str + *index);
			return (true);
		}
		(*index)++;
	}
	return (false);
}

int write_main(int *fd)
{
	int i, j, result, k;
	char *line;
	char *tmp;
	int index;
	int prefix_len = ft_strlen("silence_end:");
	j = 0;
	k = 0;
	while (1)
	{
		j++;
		// printf("A");
		if ((result = get_next_line(fd[0], &line)) < 0) //error(-1) or EOF(0)の場合break
			break;
		if (!contains_end(line, &index))
		{
			k++;
			free(line);
			if (result == 0)
				return (0);
			continue;
		}
		// printf("contains silent_end at %d\n", j);
		// printf("%d\n", j - k);
		// printf("result : %d\n",result);
		// if (j == 47 || j==48)
		// 	printf("=> %c%c%c%c%c%c%c%c%c\n",line[0],line[1],line[2],line[3],line[4],line[5],line[6],line[7],line[8]);
		// if (ft_strncmp(line, "[silencedetect ", 14) != 0)
		// {
		// 	if(j == 55)
		// 	{
		// 		printf(":::::::::::::::::::::::::::::::::::::::::::::::::::: ");
		// 		printf("%s\n",line);
		// 		printf("00000000000000000000000000000000000000000000000000 ");
		// 	}
		// 	free(line);
		// 	if (result == 0)
		// 		break;
		// 	continue;
		// }
		// i = 0;
		// // printf("%d : %s\n", j, line + 33);
		// while (line[i])
		// {
		// 	if (ft_strncmp(line + i, "silence_end: ", 11) == 0)
		// 	{
		// 		// printf("%d,(%d)\n", j, i);
		// 		break;
		// 	}
		// 	i++;
		// }
		// if (line[i] == '\0') //一致せずncmpで最後まで見た場合=出力しなくていい
		// {
		// 	// printf("%d :(%d): %s\n", j, i, line + i);
		// 	continue;
		// }
		// // printf("%s\n", line + i + 12);
		// tmp = ft_substr(line, i + 12, isDigitContinue(line + i + 12));
		// // printf("%d\n", isDigitContinue(line + i + 12));
		// free(line);
		// line = tmp;
		write(fd[1], line + index + prefix_len, isDigitContinue(line + index + prefix_len)); // ファイル書き込み
		write(fd[1], "\n", 1);																 // ファイル書き込み
		free(line);
		if (result == 0)
			break;
	}
	// printf("j : %d\n", j);
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
	return 0;
}
