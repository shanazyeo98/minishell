/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:48:45 by mintan            #+#    #+#             */
/*   Updated: 2024/11/16 13:12:21 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Desription: Prints out a node as well as the members of the AST structure
   given an AST node as input. This function is used for general debugging.
*/

void	print_ast_node(t_ast *node)
{
	char	*type;
	char	*op_type;

	op_type = NULL;
	if (node->type == CMD)
		type = "CMD";
	else
	{
		type = "OP";
		if (node->op == 0)
			op_type = "&&";
		else if (node->op == 1)
			op_type = "||";
		else if (node->op == 2)
			op_type = "|";
		else
			op_type = "Nil";
	}
	printf("Node - ");
	printf("ID: %d | Type: %s | Op Type: %s\n", node->id, type, op_type);
}

/* Desription: Prints out a command arguments in the contents of t_list *cmds
   in a cmd node. Takes in the linked list of commands and prints out the
   contents. This function is used for general debugging.
*/

void	print_ast_cmd(t_list *cmds)
{
	t_list	*curr;
	int		i;

	curr = cmds;
	printf("Cmd Linked list:\n");
	while (curr != NULL)
	{
		printf("Args:\n");
		i = 0;
		while (((t_cmd *)(curr->content))->args[i] != NULL)
		{
			printf("%s\n", ((t_cmd *)(curr->content))->args[i]);
			i++;
		}
		curr = curr->next;
	}
}

/* Desription: Prints out a command by joining all the tokens in the
   command structure. Takes in the start and end token as inputs. This function
   is used for general debugging.
*/

void	print_ast_tkn(t_token *start, t_token *end)
{
	t_token	*curr;

	curr = start;
	printf("Cmd: ");
	while (curr != end)
	{
		printf("%s ", curr->str);
		curr = curr->next;
	}
	printf("\n");
}

/* Description: Prints the AST starting from the highest level. Levels are
   denoted by indentation. Nodes and commands are ordered from left to right.
*/

void	print_ast(t_ast *node, int ctr)
{
	int	in_ctr;

	in_ctr = ctr;
	if (node->type != CMD)
	{
		while (in_ctr > 0)
		{
			printf("--");
			in_ctr--;
		}
		ctr++;
		print_ast_node(node);
		print_ast(node->left, ctr);
		print_ast(node->right, ctr);
	}
	else
	{
		while (in_ctr > 0)
		{
			printf("--");
			in_ctr--;
		}
		print_ast_tkn(node->cmdnode->start, node->cmdnode->end);
		print_ast_cmd(node->cmdnode->cmds);
	}
}

/* Description: Traverses the AST starting from the first command to the
   last command.
*/

void	traverse_ast(t_ast *node, t_minishell *params)
{
	if (node->type != CMD)
	{
		traverse_ast(node->left, params);
		if ((node->op == AND && params->exitstatus == SUCCESS) \
		|| (node->op == OR && params->exitstatus != SUCCESS))
			traverse_ast(node->right, params);
	}
	else
	{
		params->exitstatus = execute(node->cmdnode, params);
		free(params->pid);
		params->pid = NULL;
		if (params->exitstatus == FAIL)
			spick_and_span(params, FAIL, TRUE);
	}
}
