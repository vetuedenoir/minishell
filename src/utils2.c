/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:15:09 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/29 13:09:50 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back_cmds(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if (!new)
		return ;
	tmp = *lst;
	if (lst && (*lst))
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*lst = new;
}

void	printlex(t_lexer *lex)
{
	while (lex)
	{
		printf("lexer str -> %s et token = %d \n", lex->str, lex->token);
		lex = lex->next;
	}
	write(1, "\n", 1);
}

void	print_cmd(t_cmds *cmd)
{
	int	i;
	t_lexer	*tmp;
	
	while (cmd)
	{
		i = -1;
		while (cmd->str[++i])
			printf("cmd str[%d]  %s \n", i, cmd->str[i]);
		printf("builtin = %c\n", cmd->builtin);
		printf("num_redirections = %d\n", cmd->num_redirections);
		while (cmd->redirection)
		{
			tmp = cmd->redirection->next;
			printf("redirection : %s token = %d \n", cmd->redirection->str, cmd->redirection->token);
			if (cmd->redirection->str)
				free(cmd->redirection->str);
			free(cmd->redirection);
			cmd->redirection = tmp;
		}
		printf(" \n\n");
		if (cmd->next)
			printf("PIPE \n\n");
		cmd = cmd->next;
	}
}

void	clear_cmd(t_cmds **cmd)
{
	t_cmds	*tmp;
	t_lexer	*t;

	if (!cmd)
		return ;
	printf("\nclear_cmd\n");
	while (*cmd)
	{
		tmp = (*cmd)->next;
		cleartb((*cmd)->str);
		while ((*cmd)->redirection)
		{
			printf("cmd->redirection = %s\n", (*cmd)->redirection->str);
			t = (*cmd)->redirection->next;
			if ((*cmd)->redirection->str)
				free((*cmd)->redirection->str);
			free((*cmd)->redirection);
			(*cmd)->redirection = t;
		}
		//ft_lstclearl(&(*cmd)->redirection);
		printf("freecmd\n");
		free(*cmd);
		*cmd = tmp;
	}
}

void	erreur_bin(t_cmds **cmd, t_lexer **lex, char *str)
{
	t_lexer	*lex_prev;
	//t_cmds	*cmd_prev;

	printf("\nerreur_bin\n");
	if (lex && *lex)
	{
		lex_prev = (*lex)->prev;
		ft_lstclearl(lex);
		(*lex) = lex_prev;
		while (*lex)
		{
			lex_prev = (*lex)->prev;
			if ((*lex)->str)
			{
				printf("	bin lex->str = %s\n", (*lex)->str);
				free((*lex)->str);
			}
			free(*lex);
			*lex = lex_prev;
		}
	}
	if (cmd && *cmd)
	{
		//cmd_prev = (*cmd)->prev;
		clear_cmd(cmd);
		/*cmd = cmd_prev;
		while (*cmd)
		{
			cmd_prev = (*cmd)->prev;
			cleartb((*cmd)->str);
			ft_lstclearl(&(*cmd)->redirection);
			free(*cmd);
			*cmd = cmd_prev;
		}*/
	}
	if (str)
		printf("%s\n", str);
}


