/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:21:45 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*syntax_err_str(size_t code);

void	parser_handler(void *data, int code)
{
	char	*s;

	s = (char *)data;
	if (code == empty_prompt)
		return ;
	g_root.exit_status = 2;
	if (!s && code == single_quote_err)
		s = "'";
	else if (!s && code == double_quote_err)
		s = "\"";
	if (code == single_quote_err)
		print_error("unexpected EOF while looking for matching ", s);
	else if (code == double_quote_err)
		print_error("unexpected EOF while looking for matching ", s);
	else if (code == syntax_err)
	{
		s = syntax_err_str((size_t)data);
		print_error("syntax error near unexpected token ", s);
	}
	if (code == child_proc_interepted_sigint)
		g_root.exit_status = 130;
}

char	*syntax_err_str(size_t code)
{
	char	*s;

	s = NULL;
	if (code == EOT)
		s = "newline";
	else if (code == PIPE)
		s = "|";
	else if (code == INPUT)
		s = "<";
	else if (code == OUTPUT)
		s = ">";
	else if (code == APPEND)
		s = ">>";
	else if (code == HERDOC)
		s = "<<";
	return (s);
}
