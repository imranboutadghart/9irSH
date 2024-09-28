/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_literals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:12:23 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*get_literal_value(int *arr, size_t t_len, size_t *offset, int *flag);
t_var	*create_and_fill_var(int *literal, size_t literal_index, int freeable);

size_t	get_literals(t_var **list, int *bytes, size_t token_len, int *flag)
{
	t_var	*loop;
	t_var	*new;
	size_t	offset;

	offset = 0;
	new = get_literal_value(bytes, token_len, &offset, flag);
	if (!new)
		return (0);
	loop = *list;
	if (loop == NULL)
		*list = new;
	else
	{
		while (loop->next)
			loop = loop->next;
		loop->next = new;
	}
	return (offset);
}

t_var	*get_literal_value(int *arr, size_t t_len, size_t *offset, int *flag)
{
	size_t	index;
	size_t	literal_index;
	t_var	*var;
	int		*literal;

	index = 0;
	literal_index = 0;
	literal = (int *)malloc((t_len + 1) * sizeof(int));
	if (!literal)
		return (return_error(malloc_fail));
	while (index < t_len)
	{
		if (arr[index] == variable || arr[index] == exit_status)
			break ;
		if (arr[index] == double_quote)
			*flag = !*flag;
		literal[literal_index++] = arr[index];
		index++;
	}
	literal[literal_index] = 0;
	var = create_and_fill_var(literal, literal_index, 1);
	*offset = index;
	return (var);
}

t_var	*create_and_fill_var(int *literal, size_t literal_index, int freeable)
{
	t_var	*var;

	var = (t_var *)malloc(1 * sizeof(t_var));
	if (!var)
		return (return_error(malloc_fail));
	var->next = NULL;
	var->mask = literal;
	var->len = literal_index;
	var->splittable = 0;
	var->freeable = freeable;
	return (var);
}
