/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:14:09 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_token(t_token *tok);
char	**form_content(t_var *values);
void	free_values_list(t_var *values);
size_t	expand_exit_status(t_var **list);
size_t	expand_variable(t_var **list, int *bytes, int flag);
size_t	get_literals(t_var **list, int *bytes, size_t token_len, int *flag);

void	expander(t_token *toks)
{
	while (g_root.error->code == 0 && toks)
	{
		if (toks->type == WORD)
			expand_token(toks);
		toks = toks->next;
	}
}

void	expand_token(t_token *tok)
{
	size_t	i;
	t_var	*values;
	int		split;

	split = 1;
	i = 0;
	values = NULL;
	while (g_root.error->code == 0 && i < tok->len)
	{
		if (tok->start[i] == variable)
			i += expand_variable(&values, &tok->start[i + 1], split) + 1;
		else if (tok->start[i] == exit_status)
			i += expand_exit_status(&values);
		else
			i += get_literals(&values, &tok->start[i], tok->len - i, &split);
	}
	if (g_root.error->code != 0)
	{
		free_values_list(values);
		return ;
	}
	tok->content = form_content(values);
	free_values_list(values);
}

void	free_values_list(t_var *values)
{
	t_var	*tmp;

	while (values)
	{
		tmp = values->next;
		if (values->freeable)
			free(values->mask);
		free(values);
		values = tmp;
	}
}
