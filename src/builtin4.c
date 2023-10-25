/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:48:49 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 17:48:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr_int(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

void	retrive(char **arg, t_list **env)
{
	char	*s;
	int		t;
	t_list	*first;

	t = ft_strlen(arg[0]);
	first = *env;
	while (*env)
	{
		s = (char *)(*env)->content;
		if (!ft_strncmp(arg[0], s, t) && s[t] == '=')
		{
			ft_bzero((*env)->content, ft_strlen((*env)->content));
			break ;
		}
		*env = (*env)->next;
	}
	*env = first;
}

int	unset(char **arg, t_list **env, t_tool *data, int flag)
{
	int	x;

	(void)data;
	(void)flag;
	if (!env || !arg || !arg[0])
		return (1);
	x = 0;
	while (arg[x])
	{
		retrive(&arg[x], env);
		x++;
	}
	return (0);
}
