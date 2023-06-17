/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:15:09 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/17 16:31:42 by kscordel         ###   ########.fr       */
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
	while (cmd)
	{
		i = -1;
		while (cmd->str[++i])
			printf("cmd str[%d]  %s \n", i, cmd->str[i]);
		printf("num_redirections = %d\n", cmd->num_redirections);
		while (cmd->redirection)
		{
			printf("redirection : %s token = %d \n", cmd->redirection->str, cmd->redirection->token);
				cmd->redirection = cmd->redirection->next;
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

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		cleartb((*cmd)->str);
		ft_lstclearl(&(*cmd)->redirection);
		free(*cmd);
		*cmd = tmp;
	}
}

void	erreur_bin(t_cmds **cmd, t_lexer **lex, char *str)
{
	t_lexer	*lex_prev;
	t_cmds	*cmd_prev;

	if (lex && *lex)
	{
		lex_prev = (*lex)->prev;
		ft_lstclearl(lex);
		*lex = lex_prev;
		while (*lex)
		{
			lex_prev = (*lex)->prev;
			if ((*lex)->str)
				free((*lex)->str);
			free(*lex);
			*lex = lex_prev;
		}
	}
	if (cmd && *cmd)
	{
		cmd_prev = (*cmd)->prev;
		clear_cmd(cmd);
		*cmd = cmd_prev;
		while (*cmd)
		{
			cmd_prev = (*cmd)->prev;
			cleartb((*cmd)->str);
			ft_lstclearl(&(*cmd)->redirection);
			free(*cmd);
			*cmd = cmd_prev;
		}
	}
	if (str)
		printf("%s\n", str);
}


