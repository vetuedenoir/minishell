/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:38:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 14:01:04 by kscordel         ###   ########.fr       */
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

char	*search_replace(char *var, t_list **env)
{
	t_list	*first;
	t_list	*node;
	char	*s;
	int		t;

	node = NULL;
	first = *env;
	t = ft_strchr_int(var, '=');
	while (*env)
	{
		s = (char *)(*env)->content;
		if (!ft_strncmp(s, var, t) && s[t - 1] == '=')
		{
			free((*env)->content);
			(*env)->content = ft_strdup(var);
			*env = first;
			return ((*env)->content);
		}
		if (s[0] == '\0')
			node = *env;
		*env = (*env)->next;
	}
	*env = first;
	if (node)
	{
		free(node->content);
		node->content = ft_strdup(var);
		return ((*env)->content);
	}
	return (NULL);
}

int	valide_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || !expand_token(str[i], 0))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!expand_token(str[i], 0))
			return (0);
		i++;
	}
	if (ft_isdigit(str[i - 1]))
		return (0);
	return (i);
}

int	export(char **arg, t_list **env, t_tool *data, int flag)
{
	t_list	*node;
	char	*s;
	int		x;

	(void) arg;
	(void)data;
	(void)flag;
	x = -1;
	if (!env || !arg || !arg[0])
		return (1);
	while (arg[++x])
	{
		if (!valide_identifier(arg[x]))
		{
			error("minishell: export: '", arg[x], "': invalide identifier");
			return (1);
		}
		if (ft_strchr(arg[x], '='))
		{
			if (!search_replace(arg[x], env))
			{
				s = ft_strdup(arg[x]);
				if (!s)
					return (1);
				node = ft_lstnew(s);
				if (node)
					ft_lstadd_back(env, node);
				else
					return (1);
			}
		}
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
