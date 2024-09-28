/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:17:49 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_syntax(t_token *tokens)
{
	t_token	*tmp;
	int		redir;
	int		flags;

	tmp = tokens;
	flags = EXPECT_WORD | EXPECT_REDIR;
	while (tmp)
	{
		redir = (tmp->type == INPUT || tmp->type == OUTPUT);
		redir |= (tmp->type == HERDOC || tmp->type == APPEND);
		if (flags & EXPECT_REDIR && redir)
			flags = 0;
		else if (flags & EXPECT_WORD && tmp->type == WORD)
			flags = 0;
		if (flags)
			return (tmp->type);
		if (redir)
			flags = EXPECT_WORD;
		if (tmp->type == PIPE)
			flags = EXPECT_WORD | EXPECT_REDIR;
		tmp = tmp->next;
	}
	if (flags)
		return (EOT);
	return (0);
}
/*



*/