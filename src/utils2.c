/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:15:09 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 14:25:58 by kscordel         ###   ########.fr       */
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

char	**lst_to_tab(t_list *lst, t_tool *data)
{
	int		t;
	int		i;
	char	**tab;

	t = ft_lstsize(lst);
	tab = ft_malloc(sizeof(char *) * (t + 1), data);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < t && lst)
	{
		tab[i] = (char *)lst->content;
		i++;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	error(char *str, char *str2, char *str3)
{
	if (!str)
		return ;
	ft_putstr_fd("\x1b[31m", 2);
	if (str && !str2)
	{
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
	}
	else if (str && str2 && !str3)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(str2, 2);
		write(2, "\n", 1);
	}
	else if (str && str2 && str3)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(str2, 2);
		ft_putstr_fd(str3, 2);
		write(2, "\n", 1);
	}
	ft_putstr_fd("\x1b[0m", 2);
}

void	free_all_and_exit(int code, t_tool *data)
{
	ft_lstclear(&data->var_env, free);
	rl_clear_history();
	free_garbage(data);
	exit(code);
}

void	ft_perror(char *str, char *str2)
{
	ft_putstr_fd("\x1b[31m", 2);
	if (!str2)
		perror(str);
	else
	{
		ft_putstr_fd(str, 2);
		perror(str2);
	}
	ft_putstr_fd("\x1b[0m", 2);
}
