/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:23:11 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 02:05:58 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

/***************** MACROS *****************/

# define BLANK "\t\n\v "
# define SUCCESS 0
# define EXIT_FAILURE 1
# define FAIL EXIT_FAILURE
# define NAME "9irSH"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

/***************** ENUMS *****************/

typedef enum e_masks
{
	single_quote = 7000,
	double_quote,
	variable,
	pipe_mask,
	input,
	output,
	herdoc,
	append,
	exit_status,
	whitespace
}	t_masks;

typedef enum s_usefull
{
	EXPECT_WORD = 1,
	EXPECT_REDIR = 2,
	EXPANDABLE = 3,
	FIELD_SPLITABLE = 4,
	HERDOC_EXPANDABLE = 5,
	LITERAL	= 0
}	t_expect;

typedef enum e_token_type
{
	WORD = 700,
	PIPE,
	HERDOC,
	APPEND,
	INPUT,
	OUTPUT,
	EOT,
	SKIP
}	t_token_type;

typedef enum e_error_codes
{
	single_quote_err = -1,
	double_quote_err = -2,
	permision_denied_err = -3,
	no_file_or_dir_err = -4,
	cmd_not_found_err = -5,
	bad_fd_error = -6,
	too_many_args_err = -7,
	empty_prompt = -8,
	malloc_fail = -9,
	syntax_err = -10,
	child_proc_interepted_sigint = -11,
	cant_open_file = -12,
	cant_read_from_file = -13,
	cannot_create_tmp_herdoc = -14,
	fork_failure = -15,
	invalid_env = -16
}	t_error_codes;

/***************** PARSING *****************/

typedef struct s_var
{
	int				*mask;
	size_t			len;
	struct s_var	*next;
	int				splittable;
	int				freeable;
}	t_var;

typedef struct s_token
{
	int				*start;
	char			*original;
	size_t			len;
	int				xpand;
	int				type;
	char			*str;
	char			**content;
	struct s_token	*next;
}	t_token;

typedef struct s_error
{
	void	(*handler)(void *data, int code);
	void	*data;
	int		code;
}	t_error;

/***************** CMD *****************/

typedef struct s_file
{
	char			*filename;
	char			*original;
	char			*buffer;
	int				type;
	int				expandable;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**words;
	size_t			word_count;
	t_file			*files;
	struct s_cmd	*next;
}	t_cmd;

/***************** MINISHELL *****************/

typedef struct s_minishell
{
	int		exit_status;
	t_error	*error;
	t_cmd	*cmds;
	size_t	env_size;
	size_t	env_count;
	char	**env;
}	t_minishell;

extern t_minishell	g_root;

/***************** ATTRIBUTES *****************/
void	destructor(void);
void	constructor(void) __attribute__ ((constructor));
/***************** ATTRIBUTES *****************/
void	clean_exit(void);
void	sig_handler_parent(int signal);
void	sig_handler_herdoc(int signal);
/***************** ENV *****************/
void	copy_environ(void);
char	*get_env(char *key);
void	free_env(char **env);
char	**realloc_env(char **old_env, int freeable);
/***************** PARSER *****************/
t_cmd	*parser(char *line);
void	handle_herdocs(void);
int		*masker(char *line);
t_token	*tokenizer(int *bytes);
void	expander(t_token *toks);
/***************** ERROR *****************/
void	parser_handler(void *data, int code);
int		set_err(t_error *e, void (*fn)(void *d, int c), int c, void *d);
/***************** ERROR *****************/
void	*return_error(int code);
void	print_error(char *str, char *word);
/***************** PROMPT *****************/
void	manage_history(char *str);
/***************** UTILS *****************/
char	*ft_itoa(int n);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
void	reset_prompt(void);
int		is_whitespace(int c);
int		*ft_custom_itoa(int n);
int		ft_atoi(const char *str);
size_t	mask_len(const int *str);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*get_key_value(char *key, char *value);
void	delete_tokens(t_token *toks, int flag);
int		ft_strcmp(const char *s1, const char *s2);
t_token	*add_token(t_token **list, t_token *token);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*allocate(size_t size, void (*fn)(void *ptr, void *data), void *data);
/*************** EXECUTE ***************/
int		execute(t_cmd *cmd);
int		error(char *input, char *error);
/*************** BUILTINS ***************/
int		unset_env(int ac, char **av);
int		__unset_env(const char *name);
int		set_env(char *key, char *value);

#endif
