/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expand_line_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:32:31 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_exitstatus_len(size_t *len);
size_t	get_var_len(char *line, size_t *len);
char	*get_var_key_name(char *line, size_t *length);

size_t	get_var_len(char *line, size_t *len)
{
	size_t	index;
	char	*key;
	char	*value;

	index = 0;
	key = get_var_key_name(line, &index);
	if (!key)
		return (index);
	value = get_env(key);
	free(key);
	if (value)
		*len += ft_strlen(value);
	index += 1;
	return (index);
}

char	*get_var_key_name(char *line, size_t *length)
{
	size_t	index;
	size_t	len;
	char	*key;

	len = 0;
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	*length = len;
	key = (char *)malloc(sizeof(char) * (len + 1));
	if (!key)
		return (return_error(malloc_fail));
	index = 0;
	while (index < len)
	{
		key[index] = (char)line[index];
		index++;
	}
	key[index] = 0;
	return (key);
}

size_t	get_exitstatus_len(size_t *len)
{
	char	*exit_status_value;

	exit_status_value = ft_itoa(g_root.exit_status);
	if (!exit_status_value)
		return (0);
	*len += ft_strlen(exit_status_value);
	free(exit_status_value);
	return (2);
}
