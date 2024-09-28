/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:00:34 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str);
char	*get_value(char *str);
void	print_exported(void);
int		set_empty_env(char *key);
int		unvalid_identifier(char *str);

int	export(int ac, char **av)
{
	int		index;
	char	*key;
	char	*value;

	index = 1;
	g_root.exit_status = 0;
	if (ac == 1)
		print_exported();
	while (index < ac)
	{
		key = get_key(av[index]);
		if (!key)
			return (FAIL);
		value = get_value(av[index]);
		if (set_env(key, value) == 1)
			g_root.exit_status = unvalid_identifier(av[index]);
		else if (value == NULL)
			set_empty_env(ft_strdup(key));
		free(key);
		index++;
	}
	return (g_root.exit_status);
}

char	*get_key(char *str)
{
	size_t	len;
	size_t	index;
	char	*key;

	len = 0;
	index = 0;
	while (str[len] && str[len] != '=')
		len++;
	key = (char *)malloc((len + 1) * sizeof(char));
	if (!key)
		return (return_error(malloc_fail));
	while (str[index] && str[index] != '=')
	{
		key[index] = str[index];
		index++;
	}
	key[index] = '\0';
	return (key);
}

char	*get_value(char *str)
{
	size_t	index;

	index = 0;
	while (str[index] && str[index] != '=')
		index++;
	if (str[index] == '=')
		return (str + index + 1);
	return (NULL);
}

void	print_exported(void)
{
	size_t	index;
	int		i;

	index = 0;
	while (g_root.env && g_root.env[index])
	{
		i = 0;
		while (g_root.env[index][i] && g_root.env[index][i] != '=')
			write(1, g_root.env[index] + (i++), 1);
		if (g_root.env[index][i])
		{
			write(1, "=", 1);
			printf("\"%s\"", g_root.env[index] + i + 1);
		}
		printf("\n");
		index++;
	}
}

int	unvalid_identifier(char *str)
{
	write(2, "export `", sizeof("export `"));
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "` not a valid identifier\n", \
	sizeof("` not a valid identifier\n"));
	return (1);
}
