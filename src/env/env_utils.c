/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:32:02 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/22 21:32:36 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_value(char *key, char *value)
{
	char	*key_value;
	size_t	index;
	size_t	len;
	size_t	str_index;

	len = ft_strlen(key) + 2;
	if (value)
		len += ft_strlen(value);
	key_value = (char *)malloc(len * sizeof(char));
	if (!key_value)
		return (return_error(malloc_fail));
	index = 0;
	str_index = 0;
	while (key[str_index])
		key_value[index++] = key[str_index++];
	key_value[index++] = '=';
	str_index = 0;
	while (value && value[str_index])
		key_value[index++] = value[str_index++];
	key_value[index] = '\0';
	return (key_value);
}
