/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expand_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:32:33 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_len(char *line, size_t *len);
size_t	get_line_expanded_len(char *line);
char	*get_var_key_name(char *line, size_t *length);
size_t	get_exitstatus_len(size_t *len);
void	copy_line_real_value(char *new, char *line);
size_t	paste_var_value(char *line, char *new, size_t *idx, size_t *new_idx);

char	*expand_line(char *line)
{
	char	*new;
	size_t	len;

	len = get_line_expanded_len(line);
	new = (char *)malloc(sizeof(char) * (len + 3));
	if (!new)
		return (return_error(malloc_fail));
	copy_line_real_value(new, line);
	free(line);
	return (new);
}

size_t	get_line_expanded_len(char *line)
{
	size_t	idx;
	size_t	len;

	len = 0;
	idx = 0;
	while (g_root.error->code == 0 && line[idx])
	{
		if (line[idx] == '$' \
		&& (ft_isalpha(line[idx + 1]) || line[idx + 1] == '_'))
			idx += get_var_len(line + idx + 1, &len);
		else if (line[idx] == '$' && line[idx + 1] == '?')
			idx += get_exitstatus_len(&len);
		else
		{
			len += 1;
			idx++;
		}
	}
	return (len);
}

size_t	paste_exitstatus_value(char *new, size_t *idx, size_t *new_idx);

void	copy_line_real_value(char *new, char *line)
{
	size_t	idx;
	size_t	new_idx;

	new_idx = 0;
	idx = 0;
	while (g_root.error->code == 0 && line[idx])
	{
		if (line[idx] == '$' \
		&& (ft_isalpha(line[idx + 1]) || line[idx + 1] == '_'))
			paste_var_value(line + idx + 1, new + new_idx, &idx, &new_idx);
		else if (line[idx] == '$' && line[idx + 1] == '?')
			paste_exitstatus_value(new + new_idx, &idx, &new_idx);
		else
			new[new_idx++] = line[idx++];
	}
	new[new_idx] = '\n';
	new[new_idx + 1] = '\0';
}

size_t	paste_var_value(char *line, char *new, size_t *idx, size_t *new_idx)
{
	char	*key;
	char	*value;
	size_t	index;

	index = 0;
	key = get_var_key_name(line, &index);
	if (!key)
		return (FAILURE);
	*idx += index + 1;
	index = 0;
	value = get_env(key);
	free(key);
	if (value)
	{
		while (value[index])
		{
			new[index] = value[index];
			index++;
		}
	}
	*new_idx += index;
	return (SUCCESS);
}

size_t	paste_exitstatus_value(char *new, size_t *idx, size_t *new_idx)
{
	size_t	index;
	char	*exit_status_str;

	*idx += 2;
	index = 0;
	exit_status_str = ft_itoa(g_root.exit_status);
	if (!exit_status_str)
		return (FAILURE);
	while (exit_status_str[index])
	{
		new[index] = exit_status_str[index];
		index++;
	}
	free(exit_status_str);
	*new_idx += index;
	return (SUCCESS);
}
