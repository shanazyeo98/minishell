/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:46:28 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/29 15:34:45 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	searchstar(char *str, int start)
{
	int	i;

	i = start;
	while (str[i] != '\0')
	{
		if (str[i] == '*')
			return (i);
		i++;
	}
	return (-1);
}

int	addwcnode(char *str, t_list **wclist, int start, int end)
{
	t_list	*node;
	char	*substr;
	t_list	*last;

	substr = NULL;
	last = ft_lstlast(*wclist);
	if (str != NULL)
	{
		substr = ft_substr(str, start, end - start);
		if (substr == NULL)
			return (FAIL);
	}
	if (substr != NULL && last != NULL && last->content != NULL)
	{
		last->content = newstring(last->content, substr);
		free(substr);
	}
	else
	{
		node = ft_lstnew(substr);
		if (node == NULL)
			return (free(substr), FAIL);
		ft_lstadd_back(wclist, node);
	}
	return (SUCCESS);
}

int	genwildcardlist(t_token *token, t_list **wclist)
{
	int		o_index;
	int		n_index;
	int		len;

	o_index = -1;
	len = ft_strlen(token->str);
	while (1)
	{
		n_index = searchstar(token->str, o_index + 1);
		if (n_index == -1)
			break ;
		if (n_index != o_index + 1 && \
		addwcnode(token->str, wclist, o_index + 1, n_index) == FAIL)
			return (ft_lstclear(wclist, &free), FAIL);
		if (addwcnode(NULL, wclist, 0, 0) == FAIL)
			return (ft_lstclear(wclist, &free), FAIL);
		o_index = n_index;
	}
	if (o_index != len - 1 && \
	addwcnode(token->str, wclist, o_index + 1, len) == FAIL)
		return (ft_lstclear(wclist, &free), FAIL);
	return (SUCCESS);
}

int	replacestrs(t_token *tokenlist, char *newstr, int wordgrp)
{
	t_token	*token;

	token = ret_tokenwordgrp(wordgrp, tokenlist);
	free(token->str);
	token->str = newstr;
	token = token->next;
	while (token != NULL && token->wordgrp == wordgrp)
	{
		free(token->str);
		token->str = ft_strdup("");
		if (token->str == NULL)
			return (FAIL);
		token = token->next;
	}
	return (SUCCESS);
}

int	wildcard_expansion(int grp, t_minishell *params)
{
	t_list	*wclist;
	t_token	*token;
	int		status;
	char	*newstr;

	wclist = NULL;
	token = ret_tokenwordgrp(grp, *params->tokenlist);
	while (token != NULL && token->wordgrp == grp && token->type != OPERATOR)
	{
		if (token->type == BASIC)
			status = genwildcardlist(token, &wclist);
		else
			status = addwcnode(token->str, &wclist, 0, ft_strlen(token->str));
		if (status == FAIL)
			return (ft_lstclear(&wclist, &free), FAIL);
		token = token->next;
	}
	newstr = NULL;
	status = searchdir(&newstr, wclist, params->cwd);
	ft_lstclear(&wclist, &free);
	if (status == SUCCESS)
		status = replacestrs(*params->tokenlist, newstr, grp);
	return (status);
}

// int	main(void)
// {
	// t_token *token;
//	t_token *token2;
	// t_minishell params;
//	t_token *token3;

	// token = malloc(sizeof(t_token));
//	token2 = malloc(sizeof(t_token));
//	token3 = malloc(sizeof(t_token));
	// token->str = ".*";
	// token->wordgrp = 0;
	// token->type = BASIC;
	// token->next = NULL;
	// token2->str = "t";
	// token2->wordgrp = 0;
	// token2->type = SINGLE;
	// token2->next = NULL;
//	token3->str = "ests";
//	token3->wordgrp = 0;
//	token3->type = DOUBLE;
//	token3->next = NULL;
	// params.cwd = getcwd(NULL, 0);
	// params.tokenlist = &token;
	// wildcard_expansion(0, &params);
	// printf("str: %s\n", token->str);
//	printf("str: %s\n", token2->str);
//	printf("str: %s\n", token3->str);
	// free(token->str);
	// free(token2->str);
//	free(token3->str);
	// free(params.cwd);
	// free(token);
	// free(token2);
//	free(token3);
// }
