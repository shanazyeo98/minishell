/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:23:10 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/30 13:32:14 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkifending(char a, t_minishell *params, t_token *opentoken)
{
	if (opentoken->type == token(SINGLE) && a == '\'')
		return (exitstat(SUCCESS));
	if (opentoken->type == token(DOUBLE) && a == '"')
		return (exitstat(SUCCESS));
	if (opentoken->type == token(OPERATOR))
	{
		if (chartype(a, params) != token(OPERATOR))
			return (exitstat(SUCCESS));
	}
	if (opentoken->type == token(REDIRECTOR))
	{
		if (chartype(a, params) != token(REDIRECTOR))
			return (exitstat(SUCCESS));
	}
	if (opentoken->type == token(BASIC))
	{
		if (a == '\'' || a == '"' || chartype(a, params) != token(OTHERS))
			return (exitstat(SUCCESS));
	}
	return (exitstat(ERROR));
}

//echo hi - start_i: 0, i = 4
//echo "hi" - start_i: 6, i = 8
// << heredoc - start_i: 0, i = 2

int	closetoken(t_minishell *params, t_tokendets *info, int i, t_token *open)
{
	open->str = ft_substr(info->prompt, info->start_i, i - info->start_i);
	if (open->str == NULL)
		return (exitstat(FAIL));
	return (exitstat(SUCCESS));
}

// &&, || , >, <, >>, <<, |

int	checkvalidopre(char *str, t_minishell *params)
{
	int	i;

	i = 0;
	while ((params->validopre)[i] != NULL)
	{
		if (ft_strcmp(str, (params->validopre)[i]) == 0)
			return (exitstat(SUCCESS));
		i++;
	}
	return (exitstat(ERROR));
}

int	readchar(char a, t_minishell *params, t_tokendets *info, int *i)
{
	t_token *open;

	open = lsttoken(*(params->tokenlist));
	if (checkifending(a, params, open) == exitstat(SUCCESS))
	{
		if (closetoken(params, info, *i, open) == exitstat(FAIL))
			return (exitstat(FAIL));
		info->status = CLOSED;
		if (open->type == token(OPERATOR) || open->type == token(REDIRECTOR))
		{
			if (checkvalidopre(open->str, params) == exitstat(ERROR))
				return (exitstat(ERROR));
		}
		if (open->type == token(SINGLE) || open->type == token(DOUBLE))
			(*i)++;
	}
	return (exitstat(SUCCESS));
}
