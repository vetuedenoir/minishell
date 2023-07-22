/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:10 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/22 16:23:03 by kscordel         ###   ########.fr       */
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
	char			builtin;	// si y a un bultin = b sinon = 0
	t_lexer			*redirection;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}		t_cmds;

typedef struct s_tool
{
	char	*line;
	t_cmds	*cmds;
	t_list	*var_env;
	char	*pwd;
	char	*old_pwd;
	int		flag;
}	t_tool;	

extern t_list	*g_garbage_collector;

t_lexer	*ft_lexer();
char	**ft_decoup(char *arg, char **tab, char c);
int	ft_verif_quote(char *s);

//utils
t_lexer	*ft_lstnewl(char *str);
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
char	**lst_to_tab(t_list *lst);


//parsing
t_cmds *parser(t_lexer *lex);

//path
void	check_path(t_cmds **commande, t_list *env);

// expand
void	expand(t_tool *data);
char	*get_var(char *dvar, t_list *var_env);
int	ft_dollarsize(char *str, int *index, t_tool data);
char	*resize_arg(char *str, t_tool data);

// handle_quote
int	ft_copy_var(char *str, char **s, int *y, t_tool *data);
int	handle_doublequote(char *str, char **s, int *y, t_tool data);
int	handle_singlequote(char *str, char **s, int *y);
char	**divide(char **s, int flag);

//handle_redirection
t_lexer *handle_redirection(t_lexer *redirection, t_tool data);
char	*handle_dl(char *str, t_tool data);

//garbage_collector
void	*ft_malloc(size_t size);
void	*memory_add(void *pointeur);
void	free_garbage(void);
void	*ft_calloc_g(size_t nmemb, size_t size);



#endif

