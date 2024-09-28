/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:17:59 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*get_var_value(int *bytes, size_t *len, int splittable);
char	*get_var_key(int *bytes, size_t *length);
int		*mask_var_value(char *var_value, int splittable);

size_t	expand_variable(t_var **list, int *bytes, int splittable)
{
	t_var	*loop;
	t_var	*new;
	size_t	len;

	new = get_var_value(bytes, &len, splittable);
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
	return (len);
}

int	*mask_var_value(char *var_value, int splittable)
{
	int		*mask;
	size_t	index;

	index = 0;
	if (!var_value)
		return (NULL);
	mask = (int *)malloc((ft_strlen(var_value) + 1) * sizeof(int));
	if (!mask)
		return (return_error(malloc_fail));
	while (var_value[index])
	{
		mask[index] = (int)var_value[index];
		if (splittable && ft_strchr(BLANK, var_value[index]))
			mask[index] = whitespace;
		index++;
	}
	mask[index] = 0;
	return (mask);
}

t_var	*get_var_value(int *bytes, size_t *len, int splittable)
{
	char	*var_key;
	char	*var_value;
	t_var	*var;

	var_key = get_var_key(bytes, len);
	if (!var_key)
		return (NULL);
	var_value = get_env(var_key);
	free(var_key);
	var = (t_var *)malloc(1 * sizeof(t_var));
	if (!var)
		return (return_error(malloc_fail));
	var->next = NULL;
	var->mask = mask_var_value(var_value, splittable);
	var->len = 0;
	var->splittable = 0;
	var->freeable = 1;
	if (var_value)
		var->len = ft_strlen(var_value);
	if (var_value)
		var->splittable = splittable;
	return (var);
}

char	*get_var_key(int *bytes, size_t *length)
{
	size_t	index;
	size_t	len;
	char	*key;

	len = 0;
	while (bytes[len] < 127)
	{
		if (ft_isalnum(bytes[len]) == 0 && bytes[len] != '_')
			break ;
		len++;
	}
	*length = len;
	key = (char *)malloc(sizeof(char) * (len + 1));
	if (!key)
		return (return_error(malloc_fail));
	index = 0;
	while (index < len)
	{
		key[index] = (char)bytes[index];
		index++;
	}
	key[index] = 0;
	return (key);
}
