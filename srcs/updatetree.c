/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:21:02 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/14 10:46:02 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initarray(void *array, int type, int n)
{
	int	i;
	char	*chararray;
	t_redir	*redirarray;

	i = 0;
	if (type == 0)
	{
		chararray = (char *) array;
		while (i < n)
		{
			chararray = NULL;
			i++;
			chararray++;
		}
	}
	else
	{
		redirarray = (t_redir *) array;
		while (i < n)
		{
			redirarray = NULL;
			i++;
			redirarray++;
		}
	}
}

int     countargs(char *str, t_token *token, t_cmd *cmd)
{
    int i;
	int	j;

    i = 0;
	j = 0;
    while (str[j] != '\0')
    {
        if (j == 0 && str[j] == ' ')
		{
			if (token != cmd->start && token->wordgrp == (token->prev)->wordgrp)
				i++;
		}
		else if (str[j + 1] == '\0' && str[j] == ' ')
		{
			if (token->next != cmd->end && \
			token->wordgrp == (token->next)->wordgrp)
				i++;
		}
		else if (j != 0 && str[j] != ' ' && str[j - 1] == ' ')
			i++;
        j++;
    }
    return (i);
}

void    skipredir(t_token **token, t_cmd *cmd)
{
    int grp;

    *token = (*token)->next;
    grp = (*token)->wordgrp;
    while ((*token) != cmd->end && (*token)->wordgrp == grp)
        *token = (*token)->next;
}

void    count(int *args, int *redir, t_cmd *cmd)
{
    t_token *token;
    int     grp;

    token = cmd->start;
    grp = -1;
    while (token != cmd->end)
    {
        if (token->type == REDIRECTOR)
        {
            (*redir)++;
			skipredir(&token, cmd);
            if (token == cmd->end)
                break ;
        }
        if (token->wordgrp != grp)
            (*args)++;
        grp = token->wordgrp;
        if (token->type == BASIC)
            *args += countargs(token->str, token, cmd);
        token = token->next;
    }
}

void    updatetree(t_cmd *cmd), t_minishell *params)
{
    int args;
    int redir;

    args = 0;
    redir = 0;
    count(&args, &redir, cmd);
    // printf("args: %d\n", args);
    // printf("redir: %d\n", redir);
	cmd->args = malloc(sizeof(char *) * (args + 1));
	if (cmd->args == NULL)
		spick_and_span(params, FAIL);
	initarray(*cmd->args, 0, args);
	cmd->redir = malloc(sizeof(t_redir) * (redir + 1));
	if (cmd->redir == NULL)
		spick_and_span(params, FAIL);
	initarray(*cmd->redir, 1, redir);
	if (fill(cmd) == FAIL)
		spick_and_span(params, FAIL)
}

// int main(void)
// {
//     t_token a;
//     t_token b;
//     t_token c;
//     t_token d;
//     t_cmd   cmd;

//     a.str = "echo hi";
//     a.type = BASIC;
//     a.wordgrp = 0;
//     b.str = "hello ";
//     b.type = BASIC;
//     b.wordgrp = 0;
//     a.next = &b;
// 	b.prev = &a;
//     b.next = &c;
//     c.str = "file";
//     c.type = BASIC;
//     c.wordgrp = 0;
//     c.next = &d;
// 	c.prev = &b;
//     d.str = "file hi";
//     d.type = BASIC;
//     d.wordgrp = 1;
//     d.next = NULL;
// 	d.prev = &c;
//     cmd.start = &a;
//     cmd.end = NULL;
//     updatetree(&cmd);
// }
