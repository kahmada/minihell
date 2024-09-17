/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:51:23 by chourri           #+#    #+#             */
/*   Updated: 2024/09/17 12:53:11 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <sys/stat.h>
#define NON_PRINTABLE_CHAR '\x7F'
// #define NON_PRINTABLE_CHAR '@'

int sig_received;
// extern int	sig_received;
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
	char	*data;
	t_type	type;
	int		in_quotes;
	int		flag;
	int		sig_flag;
	char	*exit_status;
	struct s_token	*next;
	struct s_token	*previous;
	// int fd_her;
}			t_token;



typedef struct s_command
{
	char	**args;
	t_type	type;
	struct s_command	*next;
	int fd_in;
	char	*infile;
	char	*outfile;
	char **envp;
	int pipe_fd[2];
}			t_command;

typedef struct s_redirect_fds
{
    int input_fd;
    int output_fd;
} t_redirect_fds;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;


//split struct

typedef struct s_var
{
	char	**array;
	int		i;
	int		num;
	size_t	len;
}	t_var;

//itoa struct
typedef struct s_v
{
	char			*str;
	long			number;
	unsigned int	len;
}	t_v;
//
int	g_sig_received;

//mydata struct for expanding :

typedef struct s_data
{
	size_t	exp_len;
	char	*start;
	size_t	var_len;
	char	*exp;
	char	*var;
	char	*ptr;
	char	*value;
	int		i;
	char	*ex;
	char	*var_name;
	char	*expanded;
	//remove_quotes
	int		j;
	int		k;
	char	*new_arg;
	char	quote_char;
	int		in_quotes;
	//build_cmd
	t_command	*cmd;
	t_command	*head;
	t_command	*prev;
	//build_new_token_pipe
	t_token	*new;
	char	*combined;
}			t_data;


//parsing :
//add_npc_to_input
void handle_quotes(char *input, char **new, int *i);
void handle_dollar_sign(char *input, char **new, int *i);
void handle_heredoc_append(char *input, char **new, int *i);
void handle_pipe_in_out_redirections(char *input, char **new, int *i);
void handle_exit_status(char *input, char **new, int *i);
void handle_space_tab(char *input, char **new, int *i);
void handle_star(char *input, char **new, int *i);
int calculate_len(char *input);
void add_npc_to_cmd(char *input, char **new_input);

//parse_error_syntax
int	redirection_symbols(int type_symbol);
int	ft_linked_list_search_redirect_symbols(t_token *lst);
void handle_child_error(const char *limiter, t_token *lst);

void	parse_error(char *msg);
int handle_heredoc(t_token *current, t_token *lst);
int redirect_in_parsing(t_token *lst);
int	redirect_out_parsing(t_token *lst);
int	redirect_append(t_token *lst);
int	parse_quotes(char *s);

//build_token_list
t_token* build_token_list(char *output);
int is_combined(char **tokens, int i);
void update_last_token_quotes(t_token *lst, int in_quotes);
void handle_combined_tokens(t_token **lst, char **tokens, int *i);
t_type determine_redirect_or_special(char *token);
t_type determine_quote_type(char *token, int *in_quotes);
int parsing(t_token *lst);

//expanding tools6
int	is_alnum(char c);
int	is_digit(char c);
char	*ft_strndup(const char *s1, size_t n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	check_heredoc_presence(t_token *token);
//expanding
size_t expanded_len(char *data, char **envp);
char *expand_variable(char *data, char **envp);
void	handle_token_expansion(t_token *token, char **envp);

//build_cmd_tools
char	*ft_strjoin_space(char const *s1, char const *s2);
int	is_redirection_symbol(int type);
void ft_lstadd_back_new(t_token **lst, t_type type, const char *data);
t_token *free_list(t_token *list);
void	free_command_list(t_command *cmd_list);

//build_cmd
t_token *build_new_tokens_pipe(t_token *token);
t_command	*build_cmd(t_token *new_token);
void	remove_quotes_end(t_command *cmd);


















char **f_update_envp(char **envp, char **last_envp);
void free_2d_array(char **array);
void print_command(t_command *cmd);
// char	**ft_split(char *str);
char	**ft_split_tokens(char const *s, char c);
char	**ft_split_cmd(char const *s);
char	**ft_split_cmd_quote(char const *s);
void	free_word_array(char **array);

t_token* build_token_list(char *output);
void print_list(t_token *lst);
void free_token_list(t_token *lst);
//old
// void ft_lstadd_back(t_token **lst, t_type type, char *data);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstnew(char *data, t_type type);

// int	ft_strcmp(char *s1, char *s2);
// t_token	*ft_lstlast(t_token *lst);
t_token	*last_token(t_token *head);
int	parse_quotes(char *input);
// int parsing(t_token *lst, char **envp);

int	is_alphabet(char c);
void    print_env(char **envp);
// void handle_dollar(t_token *tokens, char **envp);
//libft
int	ft_isalnum(int c);
int	ft_isalpha(int c);
int ft_isdigit(int c);
long	ft_atoi(char *s);
char	*ft_strchr(const char *s, int c);
int	ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_itoa(int n);
char *ft_strcpy(char *dest, const char *src);
char *ft_strcat(char *dest, const char *src);
//execution
char **execute_cmd(t_command *cmd, char **envp);
char	*find_commande(char *cmd, char **envp);
char	**ft_split_lib(char const *s, char c);
//reidrect
void handle_redirect_append(char *filename);
void handle_redirect_out(char *filename);
void handle_redirect_in(char *filename);

void handle_redirects(t_command *cmd);
void handle_here_doc_and_execute(t_command *cmd, char **envp);
void	setup_fork_procs(t_command *proc1_info, t_command *proc2_info, int pipefd[]);
void	child_proc2(char **cmd_arg, int pi_fd[], char *envp[], const char *outf);
void handle_process(const char *limiter, int fd, char *file_name, t_command *cmd, char **envp);
void handle_here_doc_redirect(t_command *cmd);
// int handle_heredoc_N(t_token *tokens);
void	error(void);
void	cleanup_2darray(char **cmd_args1, char **cmd_args2);
char **handle_builtin(t_command *cmd, char **envp);
//env
char **ft_envp_copy(char **envp);
//bultin
int is_builtin(char *cmd);
void bult_env(t_env *env);
t_env *get_env(char ***envp, t_env *env);
char **env_to_envp(t_env *env);
void bult_cd(t_command *cmd, t_env **envp);
char **ft_envp_copy(char **envp);
void bult_echo(t_command *cmd);
void bult_pwd(void);
t_env	*find_env(t_env *env, const char *key);
void	bult_exit(t_command *cmd);
void bult_unset(t_command *cmd, t_env **env);
void bult_export(t_command *cmd, t_env **env);
int is_valid_variable_name(char *key);
void add_env(t_env **env, char *key, char *value);
void ft_remove_quotes(char **str);
// char	*manage_exit_status(int status, int set_flag);
void	update_envp(t_env **envp, char *key, char *value);
void	update_environment(t_env **env, char *key, char *value, int append_mode);
void	print_export(t_env *env);
//
int her(t_command *cmd, char **envp);
void handle_child(const char *limiter, int tmp_fd, char **envp);
//signals
void	sigint_handler(int s);
void signal_handler_heredoc(int signal);

// void	SIGQUIT_handler(int signal);

//try
// void	handle_signal(int sig);
// void	setup_sig_handlers(void);
//try

// void	SIGINT_HEREDOC_handler(int signal);

//expanding
void ft_expand(t_token *token, char **envp);

char *expand_variable(char *data, char **envp);
void remove_quotes_END(t_command *cmd);
void free_token_newlist(t_token *lst);
char	*manage_exit_status(int status, int set_flag);
// char *expand_variable(const char *str, char **envp);
void	free_command_list(t_command *cmd_list);


#endif
