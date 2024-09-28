/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exitstatus_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:13:03 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*get_exit_status_value(void);

size_t	expand_exit_status(t_var **list)
{
	t_var	*loop;
	t_var	*new;

	new = get_exit_status_value();
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
	return (2);
}
/*
return (2) is there so the index in expand skips '?' which is right next to '$'
*/

t_var	*get_exit_status_value(void)
{
	int		*exit_status_value;
	t_var	*var;

	exit_status_value = ft_custom_itoa(g_root.exit_status);
	if (!exit_status_value)
		return (NULL);
	var = (t_var *)malloc(1 * sizeof(t_var));
	if (!var)
		return (return_error(malloc_fail));
	var->len = mask_len(exit_status_value);
	var->next = NULL;
	var->splittable = 0;
	var->mask = exit_status_value;
	var->freeable = 1;
	return (var);
}
