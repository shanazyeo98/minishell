/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:44:30 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/14 10:44:42 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to consider the case where space is in front. for quotes, it will be taken as it is
//for basic tokens, it will spaces in the front will be removed and if there is
//a preceding token, the space indicates a new word

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

int	splitbasic(t_token *token, char **args, int *i, t_cmd *cmd)
{
	char	**split;
	int		j;
	int		k;

	if ((token->str)[0] == ' ' && args[*i] != NULL)
		(*i)++;
	split = ft_split(token->str, ' ');
	if (split == NULL)
		return (FAIL);
	k = 0;
	while (split[k] != NULL)
	{
		if (ft_assignstr(split[k], args + *i) == FAIL)
			return (ft_freearray(split), FAIL);
		k++;
		if (split[k] != NULL)
			(*i)++;
	}
	j = 0;
	while ((token->str)[j + 1] != '\0')
		j++;
	if ((token->str)[j] == ' ' && token->next != cmd->end && \
	token->wordgrp == (token->next)->wordgrp)
		(*i)++;
	return (ft_freearray(split), SUCCESS);
}

int	det_action(t_cmd *cmd, t_token **token, int *i_arg)
{
	if ((*token)->type == REDIRECTOR)
	{
		if (redirection(cmd, token, cmd->redir) == FAIL)
			return (FAIL);
	}
	else if ((*token)->type == BASIC)
	{
		if (splitbasic(*token, cmd->args, i_arg, cmd) == FAIL)
			return (FAIL);
	}
	else if ((*token)->type == SINGLE || (*token)->type == DOUBLE)
	{
		if (ft_assignstr((*token)->str, cmd->args + *i_arg) == FAIL)
			return (FAIL);
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
	grp = token->wordgrp;
	while (token != cmd->end)
	{
		if (token->wordgrp != grp)
			i_arg++;
		grp = token->wordgrp;
		if (det_action(cmd, &token, &i_arg) == FAIL)
			return (FAIL);
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
	t_token e;
    t_cmd   cmd;
	t_redir	*redir[2];
	char	*array[6];
	int		i;

    a.str = "echo hi ";
    a.type = BASIC;
    a.wordgrp = 0;
    b.str = " hello test ";
    b.type = BASIC;
    b.wordgrp = 0;
    a.next = &b;
    b.next = &c;
    c.str = "<";
    c.type = REDIRECTOR;
    c.wordgrp = 0;
    c.next = &d;
    d.str = " file hi ";
    d.type = SINGLE;
    d.wordgrp = 0;
    d.next = &e;
	e.str = " file hi ";
    e.type = SINGLE;
    e.wordgrp = 0;
    e.next = NULL;
	e.prev = &d;
	array[0] = NULL;
	array[1] = NULL;
	array[2] = NULL;
	array[3] = NULL;
//	array[4] = NULL;
//	array[5] = NULL;
//	array[6] = NULL;
    cmd.start = &a;
    cmd.end = NULL;
	cmd.args = array;
	redir[0] = NULL;
	redir[1] = NULL;
	cmd.redir = redir;
	fill(&cmd);
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
