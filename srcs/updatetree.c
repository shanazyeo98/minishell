/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:21:02 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/11 09:08:13 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char    *newstring(char *str, char *addstr)
// {
//     char    *result;

//     result = ft_strjoin(str, addstr);
//     free(str);
//     if (result == NULL)
//         return (NULL);
//     return (result);
// }

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

void    countredir(int *redir, t_token **token, t_cmd *cmd)
{
    int grp;
    
    (*redir)++;
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
            countredir(redir, &token, cmd);
            if (token == cmd->end)
                break ;
        }
        if (token->wordgrp != grp)
            (*args)++;
        grp = token->wordgrp;
        if (token->type == BASIC)
        {
            spaces = countspaces(token->str);
            if (spaces != 0)
                *args+= spaces;
        }
        token = token->next;
    }
}

void    updatetree(t_cmd *cmd)
{
    int args;
    int redir;

    args = 0;
    redir = 0;
    count(&args, &redir, cmd);
    printf("args: %d\n", args);
    printf("redir: %d\n", redir);
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