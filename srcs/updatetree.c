/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:21:02 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/12 03:19:39 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initarray(void **array, int type, int n)
{
	int	i;

	if (type == 0)
		array = (char **) array;
	else
		array = (t_redir **) array;
	i = 0;
	while (i < n)
	{
		array[i] = NULL;
		i++;
	}
}


int     countspaces(char *str)
{
    int i;

    i = 0;
    while (*str != '\0')
    {
        if (*str == ' ')
            i++;
        str++;
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
    int     spaces;

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
            *args+= countspaces(token->str);
        token = token->next;
    }
}

void    updatetree(t_cmd *cmd, t_minishell *params)
{
    int args;
    int redir;

    args = 0;
    redir = 0;
    count(&args, &redir, cmd);
    printf("args: %d\n", args);
    printf("redir: %d\n", redir);
	cmd->args = malloc(sizeof(char *) * (args + 1));
	if (cmd->args == NULL)
		spick_and_span(params, FAIL);
	initarray(cmd->args, 0, args);
	cmd->redir = malloc(sizeof(t_redir) * (redir + 1));
	if (cmd->redir == NULL)
		spick_and_span(params, FAIL);
	initarray(cmd->redir, 1, redir);
}

int main(void)
{
    t_token a;
    t_token b;
    t_token c;
    t_token d;
    t_cmd   cmd;

    a.str = "echo hi";
    a.type = BASIC;
    a.wordgrp = 0;
    b.str = "<<";
    b.type = REDIRECTOR;
    b.wordgrp = 0;
    a.next = &b;
    b.next = &c;
    c.str = "file";
    c.type = BASIC;
    c.wordgrp = 0;
    c.next = &d;
    d.str = "file hi";
    d.type = SINGLE;
    d.wordgrp = 0;
    d.next = NULL;
    cmd.start = &a;
    cmd.end = NULL;
    updatetree(&cmd);
}
