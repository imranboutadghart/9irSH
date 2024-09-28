/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:12:35 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:40:57 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define ERR_FORK         "Could not fork\n"
# define ERR_PIPE         "Could not pipe\n"
# define ERR_OPEN         "Can't open file\n"
# define ERR_DUP          "Could not dup file descriptors\n"
# define ERR_EXIST        "No such file or directory\n"
# define ERR_PERM         "Permission denied\n"
# define ERR_NOT_FND      "Command not found\n"
# define ERR_AMBIG        "Ambiguous file\n"
# define ERR_ISDIR        "Is a directory\n"

# define FAIL EXIT_FAILURE

# define MAX_PATH_NAME 4096

typedef struct s_filedes
{
	int	pipes[2];
	int	og_fds[2];
}	t_fds;

/************************ EXEC ************************** */
int		execute(t_cmd *cmd);

int		handle_pipe(t_cmd *cmd, t_fds *fds, int *p_input);
int		handle_files(t_file *files);
int		save_fds(int fds[2]);
int		restore_fds(int fds[2]);

int		execute_regular(char **words, int is_piped, t_fds fds, int *pid);
int		is_builtin(char *command);
int		execute_builtin(char **words, int is_piped, t_fds fds, int *pid);

int		get_child_exit(int pid);
int		get_children_exit(int pid);

int		get_existence(char *filename, int print);
int		get_read_access(char *filename);
int		get_write_access(char *filename);
int		get_exec_access(char *filename);
int		is_dir(char *dir);

int		get_words_len(char **words);

char	*get_cmd_path(char *cmd);
int		is_path_complete(char *path);

int		internal_error(char *input, char *error);

char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strcmp(const char *s1, const char *s2);
char	**imbo_split(char *string, char del);

/************************ BUILTINS ************************** */
int		echo(int ac, char **av);
int		cd(int ac, char **av);
int		ft_exit(int ac, char **av);
int		pwd(int ac, char **av);
int		env(int ac, char **av);
int		unset_env(int ac, char **av);
int		export(int ac, char **av);

#endif