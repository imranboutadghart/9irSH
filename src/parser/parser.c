/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:12:31 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	*check_ambiguous_redirs(t_token *tok);
void	form_cmds(t_token *tok, t_cmd **command, size_t count);

t_cmd	*parser(char *line)
{
	int		*bytes;
	t_cmd	*cmds;
	t_token	*tokens;

	cmds = NULL;
	tokens = NULL;
	bytes = masker(line);
	if (g_root.error->code)
		return (delete_tokens(tokens, 1), free(bytes), NULL);
	tokens = tokenizer(bytes);
	if (g_root.error->code)
	{
		delete_tokens(tokens, 1);
		return (free(bytes), NULL);
	}
	expander(tokens);
	if (g_root.error->code)
		return (delete_tokens(tokens, 1), free(bytes), NULL);
	check_ambiguous_redirs(tokens);
	if (g_root.error->code)
		return (delete_tokens(tokens, 1), free(bytes), NULL);
	form_cmds(tokens, &cmds, 0);
	delete_tokens(tokens, 0);
	free(bytes);
	return (cmds);
}
