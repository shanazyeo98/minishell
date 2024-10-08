/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:48:45 by mintan            #+#    #+#             */
/*   Updated: 2024/10/08 18:50:48 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Desription: Prints out a node as well as the members of the ast structure
   given an ast. This function is used for general debugging.
   XXXXXXX ADD IN SOME TRAVERSAL STUFF LATER, LIKE TRAVERSE FROM FIRST TO LAST
   XXXXXXX
*/

void	print_ast_node(t_ast *node)
{
	printf("Operator node: \n");
	printf("ID: %d | Type: %d | OP: %d | Up: %p | Left: %p | Right: %p | Cmd: %p\n", node->id, node->type, node->op, node->up, node->left, node->right, node->cmd);
}

void	print_ast_cmd(t_token *start, t_token *end)
{
	t_token	*curr;

	curr = start;
	printf("Cmd:\n");
	while (curr != end)
	{
		printf("%s ", curr->str);
		curr = curr->next;
	}
	printf("\n");

}


/* Description: Traverses from left to
*/

void	print_cmds_first_last(t_ast *node)
{
	if (node->type != CMD)
	{
		print_cmds_first_last(node->left);
		print_cmds_first_last(node->right);
	}
	else
	{
		print_ast_cmd(node->cmd->start, node->cmd->end);
		print_ast_node(node);
	}
}



/*
fx(node)
{
	if node != cmd
	{
		fx(node.left)
		fx(node.right)
	}

	else
	{
		print(node.cmd)
	}
*/




