#include "../srcs/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	t_list	*list;
	t_list	*curr;
	char	**stray;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("Environment var: %s\n", envp[i]);
		i++;
	}
	printf("=================Converting array of strings to linked list=================\n");
	list = stray_to_llist(envp);
	curr = list;
	while (curr != NULL)
	{
		printf("Curr: %s\n", (char *)curr->content);
		curr = curr->next;
	}
	printf("=================Converting linked list to array of strings=================\n");
	stray = llist_to_stray(list);
	i = 0;
	while (stray[i] != NULL)
	{
		printf("Stray: %s\n", stray[i]);
		i++;
	}

}
