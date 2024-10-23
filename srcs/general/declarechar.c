/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declarechar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:03:54 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/21 16:36:58 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: The below is to initialize the different arrays to store
the different characters belonging to the different types*/

void	declareconnector(t_minishell *params)
{
	params->connector[0] = '(';
	params->connector[1] = ')';
	params->connector[2] = ' ';
	params->connector[3] = '\0';
}

void	declareoperator(t_minishell *params)
{
	params->operator[0] = '&';
	params->operator[1] = '|';
	params->operator[2] = '\0';
}

void	declareredirector(t_minishell *params)
{
	params->redirector[0] = '<';
	params->redirector[1] = '>';
	params->redirector[2] = '\0';
}

void	declarevalidopre(t_minishell *params)
{
	params->validopre[0] = "&&";
	params->validopre[1] = "||";
	params->validopre[2] = ">";
	params->validopre[3] = "<";
	params->validopre[4] = ">>";
	params->validopre[5] = "<<";
	params->validopre[6] = "|";
	params->validopre[7] = NULL;
}

void	declarearray(t_minishell *params)
{
	declareconnector(params);
	declareoperator(params);
	declareredirector(params);
	declarevalidopre(params);
}
