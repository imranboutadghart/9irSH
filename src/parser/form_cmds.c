/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:12:46 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_words(char **words);
t_cmd	*add_cmd(t_cmd **cmds);
char	**add_words(t_token *toks, size_t *count, size_t *word_count);
t_file	*create_file(t_cmd *cmd, t_token *tok, int type);

void	form_cmds(t_token *tok, t_cmd **command, size_t count)
{
	t_token	*checkpoint;
	t_cmd	*cmd;

	cmd = add_cmd(command);
	checkpoint = tok;
	while (g_root.error->code == 0 && tok)
	{
		if (tok->type == PIPE)
		{
			cmd->words = add_words(checkpoint, &count, &cmd->word_count);
			checkpoint = tok->next;
			cmd = add_cmd(command);
		}
		else if (tok->type == HERDOC || tok->type == APPEND \
		|| tok->type == INPUT || tok->type == OUTPUT)
		{
			create_file(cmd, tok->next, tok->type);
			tok = tok->next;
		}
		else if (tok->type == WORD)
			count += count_words(tok->content);
		tok = tok->next;
	}
	if (checkpoint)
		cmd->words = add_words(checkpoint, &count, &cmd->word_count);
}

size_t	count_words(char **words)
{
	size_t	index;

	index = 0;
	while (words && words[index])
		index++;
	return (index);
}
