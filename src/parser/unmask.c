/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmask.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:14:03 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unmask_herdocs(t_token *tok)
{
	size_t	idx;
	int		herdoc;

	herdoc = 0;
	while (tok)
	{
		idx = 0;
		while (tok->type == WORD && idx < tok->len)
		{
			if (herdoc)
				tok->xpand = HERDOC_EXPANDABLE;
			if (herdoc && tok->start[idx] == variable)
				tok->start[idx] = '$';
			else if (herdoc && tok->start[idx] == exit_status)
				tok->start[idx] = '$';
			else if (herdoc && tok->start[idx] == single_quote)
				tok->xpand = LITERAL;
			else if (herdoc && tok->start[idx] == double_quote)
				tok->xpand = LITERAL;
			idx++;
		}
		herdoc = tok->type == HERDOC;
		tok = tok->next;
	}
}
