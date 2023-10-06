/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:10 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/06 14:37:25 by kscordel         ###   ########.fr       */
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

# define PROMPT		"\033[38;2;0;128;255mminishell 🌊 \x1b[0m"
/*# define PROMPT		"minishell -> "*/
# define COULEUR	"\033[38;2;0;128;255m"
# define RESET		"\x1b[0m"


typedef enum	s_token
{
	fleched = 1,	// >
	flecheg,		// <
	fleched2,		// >>
	flecheg2,		// <<
	Pipe,			// |
}		t_token;

typedef struct	s_lexer
{
	char			*str;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev; 
}		t_lexer;

typedef struct	s_cmds
{
	char			**str;
	void			*f;		// un pointeur sur fonction builtin
	int				num_redirections;
	char			*file_name;
	void			*builtin;	// si y a un bultin = b sinon = 0
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
	pid_t		*pid;
	//int		outfile;
	//int		infile;
}	t_tool;

t_lexer	*ft_lexer(t_tool *data);
char	**ft_decoup(char *arg, char **tab, char c, t_tool *data);
int		ft_verif_quote(char *s);

//utils
t_lexer	*ft_lstnewl(char *str, t_tool *data);
void    ft_add_back_lexer(t_lexer **lst, t_lexer *new);
void	cleartb(char **tb);
char	**dup_tab(char **tb);
void	ft_lstclearl(t_lexer **lst);
void	clear_lex(t_lexer **lst, int nb);

//utils2
void	add_back_cmds(t_cmds **lst, t_cmds *new);
void	printlex(t_lexer *lex);
void	print_cmd(t_cmds *cmd);
void	clear_cmd(t_cmds **cmd);
char	**lst_to_tab(t_list *lst, t_tool *data);
void	error(char *str, char *str2, char *str3);

//parsing
t_cmds *parser(t_lexer *lex, t_cmds *commande, t_tool *data);

//path
void	check_path(t_cmds **commande, t_list *env, t_tool *data);

// expand
void	expand(t_tool *data);
char	*get_var(char *dvar, t_list *var_env);
int		ft_dollarsize(char *str, int *index, t_tool data);
char	*resize_arg(char *str, t_tool *data);

// handle_quote
int		ft_copy_var(char *str, char **s, int *y, t_tool *data);
int		handle_doublequote(char *str, char **s, int *y, t_tool data);
int		handle_singlequote(char *str, char **s, int *y);
char	**divide(char **s, int flag, t_tool *data);

//handle_redirection
t_lexer *handle_redirection(t_lexer *redirection, t_tool *data);
char	*handle_dl(char *str, t_tool *data);

//garbage_collector
void	*ft_malloc(size_t size, t_tool *data);
void	*memory_add(void *pointeur, t_tool *data);
void	free_garbage(t_tool *data);
void	*ft_calloc_g(size_t nmemb, size_t size, t_tool *data);

//exec
void	ft_exec(t_tool *data);
//heredoc
void    check_heredoc(t_cmds *cmd, t_tool *data);
char	*heredoc_expand(char *str, t_tool *data);
//redirection
void	check_redir(t_cmds *cmd);
int		expand_token(char c);

//builtin
int	export(char **arg, t_list **env, t_tool *data);
int	unset(char **arg, t_list **env, t_tool *data);
int	echo(char **arg, t_list **env, t_tool *data);
int	env(char **arg, t_list **env, t_tool *data);
int	ft_exit(char **arg, t_list **env, t_tool *data);
int	pwd(char **arg, t_list **env, t_tool *data);
int	cd(char **arg, t_list **env, t_tool *data);

int	valide_identifier(char *str);
#endif

