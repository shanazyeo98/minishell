/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:44:30 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/14 02:28:48 by shayeo           ###   ########.fr       */
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

int	ft_assignstr(char *newstr, char **args)
{
	if (*args != NULL)
	{
		*args = newstring(*args, newstr);
		if (*args == NULL)
			return (FAIL);
	}
	else
	{
		*args = ft_strdup(newstr);
		if (*args == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	splitbasic(char *str, char **args, int *i)
{
	char	**split;

	split = ft_split(str, ' ');
	if (split == NULL)
		return (FAIL);
	while (*split != NULL)
	{
		if (ft_assignstr(*split, args + *i) == FAIL)
			return (FAIL);
		(*i)++;
		split++;
	}
	return (SUCCESS);
}

int	fill(t_cmd *cmd)
{
	int		i_arg;
	t_token	*token;
	int		grp;

	i_arg = 0;
	token = cmd->start;
	while (token != cmd->end)
	{
		if (token->type == REDIRECTOR)
		{
			if (redirection(cmd, &token, cmd->redir) == FAIL)
				return (FAIL);
			if (token == cmd->end)
				break ;
			grp = token->wordgrp;
		}
		if (token->wordgrp != grp)
			i_arg++;
		grp = token->wordgrp;
		if (token->type == BASIC)
		{
			if (splitbasic(token->str, cmd->args, &i_arg))
				return (FAIL);
			i_arg--;
		}
		else
			ft_assignstr(token->str, cmd->args + i_arg);
		token = token->next;
	}
	return (SUCCESS);
}

int main(void)
{
    t_token a;
    t_token b;
    t_token c;
    t_token d;
    t_cmd   cmd;
	t_redir	*redir[2];
	char	*array[3];
	int		i;

    a.str = "<";
    a.type = REDIRECTOR;
    a.wordgrp = 0;
    b.str = "hello test";
    b.type = BASIC;
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
//	array[3] = NULL;
    cmd.start = &a;
    cmd.end = NULL;
	cmd.args = array;
	redir[0] = NULL;
	redir[1] = NULL;
	cmd.redir = redir;
	fill(&cmd);
	i = 0;
	while (i < 3)
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
