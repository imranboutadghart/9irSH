/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:19:34 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_token(t_token **list, t_token *token)
{
	t_token	*loop;

	loop = *list;
	if (loop == NULL)
		*list = token;
	else
	{
		while (loop->next)
			loop = loop->next;
		loop->next = token;
	}
	return (token);
}

void	delete_tokens(t_token *toks, int flag)
{
	t_token	*next;
	size_t	index;

	while (toks)
	{
		if (flag)
		{
			index = 0;
			while (toks->content && toks->content[index])
			{
				free(toks->content[index]);
				index++;
			}
			free(toks->original);
			free(toks->str);
		}
		free(toks->content);
		next = toks->next;
		free(toks);
		toks = next;
	}
}
