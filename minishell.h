/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:51:23 by chourri           #+#    #+#             */
/*   Updated: 2024/10/11 10:13:23 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>
# define NON_PRINTABLE_CHAR '\x7F'

int	g_sig_received;

typedef enum s_type
{
	COMMAND = 1,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	ENV_VAR,
	EXIT_STATUS,
	INSIDE_SINGLE_QUOTE,
	INSIDE_DOUBLE_QUOTE,
	WORD,
	SPAACE,
	TAAB,
	DS
}				t_type;

typedef struct s_token
{
	char			*data;
	t_type			type;
	int				flag;
	int				sig_flag;
	int				should_be_exp;
	char			*exit_status;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef struct s_command
{
	char				**args;
	char				*ex;
	t_type				type;
	char				**last_envp;
	struct s_command	*next;
	int					fd_in;
	char				*infile;
	char				*outfile;
	int					pipe_fd[2];
	char				*file_name;
}						t_command;

typedef struct s_here_doc
{
	const char	*limiter;
	int			fd;
	char		*file_name;
	t_command	*cmd;
	char		**envp;
}				t_here_doc;

typedef struct s_redirect_fds
{
	int	input_fd;
	int	output_fd;
}		t_redirect_fds;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_var
{
	char	**array;
	int		i;
	size_t	len;
	int		num;
}			t_var;

typedef struct s_data
{
	size_t		exp_len;
	char		*start;
	size_t		var_len;
	char		*exp;
	char		*var;
	char		*ptr;
	char		*value;
	int			i;
	char		*ex;
	char		*var_name;
	char		*expanded;
	int			j;
	int			k;
	char		*new_arg;
	char		quote_char;
	int			in_quotes;
	t_command	*cmd;
	t_command	*head;
	t_command	*prev;
	t_token		*new;
	char		*combined;
}				t_data;

void		handle_quotes(char *input, char **new, int *i);
void		handle_dollar_sign(char *input, char **new, int *i);
void		handle_heredoc_append(char *input, char **new, int *i);
void		handle_pipe_in_out_redirections(char *input, char **new, int *i);
void		handle_exit_status(char *input, char **new, int *i);
void		handle_space_tab(char *input, char **new, int *i);
void		handle_star(char *input, char **new, int *i);
int			calculate_len(char *input);
void		add_npc_to_cmd(char *input, char **new_input);
void		handle_child_error(const char *limiter, t_token *lst);
int			should_open_heredoc(t_token *lst);
int			redirect_in_parsing(t_token *lst);
int			redirect_out_parsing(t_token *lst);
int			redirect_append(t_token *lst);
int			parse_quotes(char *s);
t_token		*build_token_list(char *output);
int			is_combined(char **tokens, int i);
void		update_last_token_quotes(t_token *lst, int in_quotes);
void		handle_combined_tokens(t_token **lst, char **tokens, int *i);
t_type		determine_redirect_or_special(char *token);
t_type		determine_quote_type(char *token, int *in_quotes);
int			parsing(t_token *lst);
size_t		expanded_len(char *data, char **envp);
char		*expand_variable(char *data, char **envp);
void		handle_token_expansion(t_token *token, char **envp);
void		ft_expand(t_token *token, char **envp);
void		expand_home(t_token *token);
t_token		*build_new_tokens_pipe(t_token *token);
t_command	*build_cmd(t_token *new_token);
void		remove_quotes_end(t_command *cmd);
void		sigint_handler(int s);
void		signal_handler_heredoc(int signal);
char		**f_update_envp(char **envp, char **last_envp);
void		free_2d_array(char **array);
char		**ft_split_tokens(char const *s, char c);
char		**ft_split_cmd(char const *s);
char		**ft_split_cmd_quote(char const *s);
void		free_word_array(char **array);
t_token		*build_token_list(char *output);
void		free_token_list(t_token *lst);
void		ft_lstadd_back(t_token **lst, t_token *new);
t_token		*ft_lstnew(char *data, t_type type);
t_token		*last_token(t_token *head);
int			parse_quotes(char *input);
int			is_alphabet(char c);
void		print_env(char **envp);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strcpy(char *dest, const char *src);
t_token		*last_token(t_token *head);
t_token		*ft_lstnew(char *data, t_type type);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		free_token_list(t_token *lst);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
long		ft_atoi(char *s);
int			is_alphabet(char c);
int			redirection_symbols(int type_symbol);
int			ft_linked_list_search_redirect_symbols(t_token *lst);
void		parse_error(char *msg);
int			is_alnum(char c);
int			is_digit(char c);
char		*ft_strndup(const char *s1, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			check_heredoc_presence(t_token *token);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin_space(char const *s1, char const *s2);
int			is_redirection_symbol(int type);
void		ft_lstadd_back_new(t_token **lst, t_type type, const char *data);
t_token		*free_list(t_token *list);
void		free_command_list(t_command *cmd_list);
char		*ft_itoa(int n);
void		child_process_execution(t_command *cmd, char **envp, int *input_fd);
int			not_last(t_command *first, int i);
char		*handle_exp(char *limiter, char *line, int flag, char **envp);
char		*remove_quotes_limiter(const char *arg);
void		signal_handler_heredoc(int signal);
int			create_tempfile(char *temp_filename, int file_counter);
void		handle_child(const char *limiter, int tmp_fd, char **envp);
int			process_input_her(int tmp_fd, char *limiter, int flag, char **envp);
char		**execute_cmd(t_command *cmd, char **envp);
char		*find_commande(char *cmd, char **envp);
char		**ft_split_lib(char const *s, char c);
int			count_commands(t_command *cmd);
void		handle_parent_signals(t_command *cmd);
char		**handle_builtin_cmd(t_command *cmd, char **envp);
char		**f_update_envp(char **envp, char **last_envp);
void		handle_signal_termination(int status);
void		wait_for_children(int *child_pids, int count);
void		handle_redirect_append(char *filename);
void		handle_redirect_out(char *filename);
void		handle_redirect_in(char *filename);
void		handle_redirects(t_command *cmd);
void		handle_here_doc_and_execute(t_command *cmd, char **envp);
void		handle_here_doc_redirect(t_command *cmd);
void		error(void);
void		cleanup_2darray(char **cmd_args1, char **cmd_args2);
char		**handle_builtin(t_command *cmd, char **envp);
char		**ft_envp_copy(char **envp);
char		**handle_exit(t_command *cmd, char **envp);
void		ft_putstr_fd(char *s, int fd);
int			count_env_vars(t_env *env);
int			is_builtin_out(char *cmd);
char		**handle_builtin_cmd_out(t_command *cmd, char **envp);
char		**handle_built_out(t_command *cmd, char **envp);
void		valid_and_prs_exprt(const char *arg, char **ky, \
			char **val, int *ap_md);
void		free_env(t_env *env);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			is_builtin(char *cmd);
void		bult_env(t_env *env, t_command *cmd);
t_env		*get_env(char ***envp, t_env *env);
char		**env_to_envp(t_env *env);
void		bult_cd(t_command *cmd, t_env **envp);
char		**ft_envp_copy(char **envp);
void		bult_echo(t_command *cmd);
void		bult_pwd(t_command *cmd);
t_env		*find_env(t_env *env, const char *key);
void		bult_exit(t_command *cmd);
void		bult_unset(t_command *cmd, t_env **env);
void		bult_export(t_command *cmd, t_env **env);
int			is_valid_variable_name(char *key);
void		add_env(t_env **env, char *key, char *value);
void		ft_remove_quotes(char **str);
void		update_envp(t_env **envp, char *key, char *value);
void		update_environment(t_env **env, char *key, char *value);
void		print_export(t_env *env);
int			her(t_command *cmd, char **envp);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		sigint_handler(int s);
void		signal_handler_heredoc(int signal);
char		*manage_exit_status(int status, int set_flag);
void		wrerror(char *str);
char		**process_command(char *input, char **envp);

#endif
