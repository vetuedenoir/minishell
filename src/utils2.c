/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:15:09 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/19 13:06:07 by kscordel         ###   ########.fr       */
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
			printf("\ncmd str[%d]  %s \n", i, cmd->str[i]);
		printf("builtin = %p\n", cmd->builtin);
		printf("num_redirections = %d\n", cmd->num_redirections);
		while (cmd->redirection)
		{
			tmp = cmd->redirection->next;
			printf("redirection : %s token = %d \n", cmd->redirection->str, cmd->redirection->token);
			cmd->redirection = tmp;
		}
		printf(" \n\n");
		if (cmd->next)
			printf("PIPE \n\n");
		cmd = cmd->next;
	}
}

char	**lst_to_tab(t_list *lst)
{
	int	t;
	int	i;
	char	**tab;
	
	t = ft_lstsize(lst);
	tab = ft_malloc(sizeof(char *) * (t + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < t && lst)
	{
		tab[i] = (char*)lst->content;
		i++;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}




