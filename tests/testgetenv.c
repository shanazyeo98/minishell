#include "../srcs/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("Environment var: %s\n", envp[i]);
		i++;
	}
}
