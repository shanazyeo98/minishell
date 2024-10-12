/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:44:30 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/12 05:09:20 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *newstring(char *str, char *addstr)
{
    char    *result;

    result = ft_strjoin(str, addstr);
    free(str);
    if (result == NULL)
        return (NULL);
    return (result);
}

int	ft_assignstr(char *newstr, char **args, int i)
{
	if (args[i] != NULL)
	{
		args[i] = newstring(args[i], newstr);
		if (args[i] == NULL)
			return (FAIL);
	}
	else
	{
		args[i] = ft_strdup(newstr);
		if (args[i] == NULL)
			return (FAIL);
	}
}

int	splitbasic(char *str, char **args, int *i)
{
	char	**split;
	int		j;

	split = ft_split(str, ' ');
	if (split == NULL)
		return (FAIL);
	j = 0;
	while (*split != NULL)
	{
		ft_assignstr(*split, args, *i);
		(*i)++;
		split++;
	}
}

int	fill(t_cmd *cmd, t_minishell *params)
{
	int		i_arg;
	int		i_redir;
	t_token	*token;
	int		grp;

	i_arg = 0;
	i_redir = 0;
	token = cmd->start;
	grp = 0;
	while (token != cmd->end)
	{
		if (token->wordgrp != grp)
			i_arg++;
		if (token->type == BASIC)
		{
			if (splitbasic(token->str, cmd->args, &i_arg))
				return (FAIL);
			i_arg--;
		}
		else
			ft_assignstr(token->str, cmd->args, i_arg);
		token = token->next;
	}
}

int main(void)
{
    t_token a;
    t_token b;
    t_token c;
    t_token d;
    t_cmd   cmd;
	char	*array[4];
	int		i;

    a.str = "echo hi";
    a.type = BASIC;
    a.wordgrp = 0;
    b.str = "hello test";
    b.type = DOUBLE;
    b.wordgrp = 0;
    a.next = &b;
    b.next = &c;
    c.str = "SINGLE";
    c.type = SINGLE;
    c.wordgrp = 0;
    c.next = &d;
    d.str = "file hi";
    d.type = SINGLE;
    d.wordgrp = 1;
    d.next = NULL;
	array[0] = NULL;
	array[1] = NULL;
	array[2] = NULL;
	array[3] = NULL;
    cmd.start = &a;
    cmd.end = NULL;
	cmd.args = array;
	fill(&cmd, NULL);
	i = 0;
	while (i < 4)
	{
		printf("%s\n", array[i]);
		i++;
	}
}


// int	main(void)
// {
// 	int	n;
// 	int	i;
// 	char	*args[n];
// 	int	index;
// 	char	*str;

// 	n = 4;
// 	i = 1;
// 	index = 0;
// 	str = malloc(3);
// 	str[0] = 'h';
// 	str[1] = 'i';
// 	str[2] = '\0';
// 	args[0] = str;
// 	while (i < n)
// 	{
// 		args[i] = NULL;
// 		i++;
// 	}
// 	splitbasic("echo hi hello", args, &index);
// 	i = 0;
// 	while (i < n - 1)
// 	{
// 		printf("%s\n", args[i]);
// 		i++;
// 	}
// }
