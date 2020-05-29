#include "shell.h"

int		compare_input(char *input, char *command)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] != command[i])
			return (-1);
		i++;
	}
	if (command[i] != '\0')
		return (-1);
	return (0);
}

int	parse_input(char *input)
{
	char *command[3];
	int i;
	
	i = 0;
	command[0] = "pwd";
	command[1] = "cd";
	command[2] = "weekend";
	i = 0;
	while (i < 3)
	{
		if (compare_input(input, command[i]) == 0)
			return (i) ;
		i++;
	}
	return (-1);
}

void	pwd_command(void)
{
	size_t size;
	char *path;

	size = pathconf(".", _PC_PATH_MAX);
	path = malloc(sizeof(char) * (size + 1));
	write(1, getcwd(path, size), size);
	write(1, "\n", 1);
	return ;
}

void	path(int i)
{
	if (i == 0)
		pwd_command();
	if (i == 1)
		write(1, "cd\n", 3);
	if (i == 2)
		write(1, "BIJNA WEEKEND\n", 14);
}

int main(void)
{
	int   	ret;
	char	*input;
	// TODO: Turn off ctrl-c / ctrl-z / ctrl-d to prevent user exiting shell
	while (1)
	{
		write(1, "minishell> $ ", 13);
		ret = next_line(0, &input);
		if (ret == -1)
		{
			errno = 0;
			break ;
		}
		write(1, "minishell> $ ", 13);
		ret = parse_input(input);
		printf("[%c]", *input);
		// write(1, "HOI", 3);
		if (ret == -1)
			write(1, "unrecognised input.\n", 20);
		path(ret);
		//printf("+++ %s +++\n", input); // Remove
		// TODO: lexic analysis
		// TODO: Parse result of lexic analysis into "syntax tree/command table"
		// TODO: Execute "syntax tree/command table"
	}
	// TODO: free everything
	return 0;
}