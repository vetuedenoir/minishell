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

char	*search_replace_end(t_list *node, char *var, t_list **env)
{
	if (node)
	{
		free(node->content);
		node->content = ft_strdup(var);
		return ((*env)->content);
	}
	return (NULL);
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
	return (search_replace_end(node, var, env));
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

int	export_egal(char *arg, t_list **env, t_list *node, char *s)
{
	if (ft_strchr(arg, '='))
	{
		if (!search_replace(arg, env))
		{
			s = ft_strdup(arg);
			if (!s)
				return (1);
			node = ft_lstnew(s);
			if (node)
				ft_lstadd_back(env, node);
			else
				return (1);
		}
	}
	return (0);
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
	s = NULL;
	node = NULL;
	while (arg[++x])
	{
		if (!valide_identifier(arg[x]))
		{
			error("minishell: export: '", arg[x], "': invalide identifier");
			return (1);
		}
		if (export_egal(arg[x], env, node, s) == 1)
			return (1);
	}	
	return (0);
}
