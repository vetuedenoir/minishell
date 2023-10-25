/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:10 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 19:14:29 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/types.h>
# include <limits.h>
# include <sys/wait.h>
# include <stdbool.h>

# define PROMPT		"\033[38;2;0;128;255mminishell 🌊 \x1b[0m"
# define COULEUR	"\033[38;2;0;128;255m"
# define RESET		"\x1b[0m"

typedef enum s_token
{
	fleched = 1,
	flecheg,
	fleched2,
	flecheg2,
	Pipe,
}		t_token;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}		t_lexer;

typedef struct s_cmds
{
	char			**str;
	void			*builtin;
	int				num_redirections;
	char			*file_name;
	t_lexer			*redirection;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}		t_cmds;

typedef struct s_tool
{
	char	*line;
	t_cmds	*cmds;
	t_list	*var_env;
	t_list	*garbage_collector;
	int		flag;
	int		base_fd[2];
	pid_t	*pid;
}	t_tool;

extern unsigned int	g_exitcode;

//initshell
t_tool	*init_shell(char **envp, t_tool *data);

//signal
void	sigint_handler(int signo);
void	sigint_heredoc(int signo);

//lexer
char	**ft_decoup(char *arg, char **tab, char c, t_tool *data);
int		ft_verif_quote(char *s);
t_lexer	*check_word(char *str, t_tool *data);
char	*add_space(char *str, t_tool *data);
char	*copy_with_space(char *str, char *s);
int		quote_space(char *str, char **s, int *y);
int		new_size(char *str);

//expand_lex
t_lexer	*ft_lexer(t_tool *data);
void	expand(t_tool *data);

//utils
t_lexer	*ft_lstnewl(char *str, t_tool *data);
void	ft_add_back_lexer(t_lexer **lst, t_lexer *new);
void	cleartb(char **tb);
char	**dup_tab(char **tb);
void	clear_lex(t_lexer **lst, int nb);

//utils2
void	add_back_cmds(t_cmds **lst, t_cmds *new);
char	**lst_to_tab(t_list *lst, t_tool *data);
void	error(char *str, char *str2, char *str3);
void	ft_perror(char *str, char *str2);
void	free_all_and_exit(int code, t_tool *data);

//parsing
t_cmds	*parser(t_lexer *lex, t_cmds *commande, t_tool *data);

//path
int		check_path(t_cmds **commande, t_list *env, t_tool *data);

// expand
char	**handle_arg(char **arg, t_tool *data);
char	*get_var(char *dvar, t_list *var_env);
int		ft_dollarsize(char *str, int *index, t_tool data);
char	*resize_arg(char *str, t_tool *data);

// handle_quote
int		ft_copy_var(char *str, char **s, int *y, t_tool *data);
int		handle_doublequote(char *str, char **s, int *y, t_tool data);
int		handle_singlequote(char *str, char **s, int *y);
char	**divide(char **s, int flag, t_tool *data);
int		zi(char *str, char **s, int *y, t_tool data);

//handle_redirection
t_lexer	*handle_redirection(t_lexer *redirection, t_tool *data);
char	*handle_dl(char *str, t_tool *data);
int		expand_token(char c, bool flag);

//garbage_collector
void	*ft_malloc(size_t size, t_tool *data);
void	*memory_add(void *pointeur, t_tool *data);
void	free_garbage(t_tool *data);
void	*ft_calloc_g(size_t nmemb, size_t size, t_tool *data);

//exec
void	ft_exec(t_tool *data);

//exec2
int		size_nb_com(t_tool *data);
void	exec_com(t_tool *data, t_cmds *cmd);
void	wait_processes(t_tool *data, int sig, int status);
int		exec_builtin(int (*builtin)(char **arg, t_list **env, \
t_tool *data, int flag), t_cmds *cmd, t_tool *data, int flag);

//heredoc
char	*heredoc_expand(char *str, t_tool *data);
void	ft_close(t_tool *data, int *pipefd);
int		erreur_here(int	*pipefd);
int		check_heredoc(t_cmds *cmd, t_tool *data, int *pipefd);

//redirection
int		check_redir(t_cmds *cmd);

//builtin
int		ft_strchr_int(char *str, char c);
int		export(char **arg, t_list **env, t_tool *data, int flag);
int		unset(char **arg, t_list **env, t_tool *data, int flag);
int		echo(char **arg, t_list **env, t_tool *data, int flag);
int		env(char **arg, t_list **env, t_tool *data, int flag);
int		ft_exit(char **arg, t_list **env, t_tool *data, int flag);
int		pwd(char **arg, t_list **env, t_tool *data, int flag);
int		cd(char **arg, t_list **env, t_tool *data, int flag);
void	*set_builtin(char *s);
void	retrive(char **arg, t_list **env);

int		valide_identifier(char *str);

#endif