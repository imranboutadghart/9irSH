/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:12:15 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tokens(t_token **tokens, int *bytes);
void	set_token(t_token *tok, int *start, size_t len, int type);
int		get_token_type(int *bytes, size_t *index);
int		is_not_separator(int byte);
size_t	check_syntax(t_token *tokens);
void	unmask_herdocs(t_token *tok);

t_token	*tokenizer(int *bytes)
{
	t_token	*tokens;
	size_t	syntax_code;

	tokens = NULL;
	syntax_code = 0;
	get_tokens(&tokens, bytes);
	if (g_root.error->code)
		return (tokens);
	if (!tokens)
	{
		g_root.error->code = empty_prompt;
		return (tokens);
	}
	syntax_code = check_syntax(tokens);
	if (syntax_code)
	{
		g_root.error->code = syntax_err;
		g_root.error->data = (void *)syntax_code;
		return (tokens);
	}
	unmask_herdocs(tokens);
	return (tokens);
}

void	get_tokens(t_token **tokens, int *bytes)
{
	t_token	*tok;
	size_t	index;
	size_t	len;
	int		type;

	index = 0;
	while (bytes[index])
	{
		if (bytes[index] != whitespace)
		{
			len = 1;
			tok = allocate(sizeof(t_token), NULL, NULL);
			if (!tok)
				return ;
			type = get_token_type(bytes + index, &index);
			while (type == WORD && is_not_separator(bytes[index + len]))
				len++;
			set_token(tok, bytes + index, len, type);
			add_token(tokens, tok);
			index += len;
			continue ;
		}
		index++;
	}
}

void	set_token(t_token *tok, int *start, size_t len, int type)
{
	tok->type = type;
	if (type == WORD)
		tok->start = start;
	tok->len = len;
	tok->next = NULL;
}

int	get_token_type(int *bytes, size_t *index)
{
	if (*bytes == pipe_mask)
		return (PIPE);
	if (*bytes == input)
		return (INPUT);
	if (*bytes == output)
		return (OUTPUT);
	if (*bytes == herdoc)
	{
		*index += 1;
		return (HERDOC);
	}
	if (*bytes == append)
	{
		*index += 1;
		return (APPEND);
	}
	return (WORD);
}

int	is_not_separator(int byte)
{
	if (byte == 0)
		return (0);
	if (byte == whitespace)
		return (0);
	else if (byte == pipe_mask)
		return (0);
	else if (byte == input)
		return (0);
	else if (byte == output)
		return (0);
	else if (byte == herdoc)
		return (0);
	else if (byte == append)
		return (0);
	return (1);
}
