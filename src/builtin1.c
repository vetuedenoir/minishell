/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:38:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/26 19:54:12 by kscordel         ###   ########.fr       */
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

int	export(char **arg, t_list **env, t_tool *data)
{
	t_list	*node;
	char	*s;
	int		i;

	(void) arg;
	(void)data;
	i = 0;
	if (!env || !arg || !arg[0])
		return (1);
	while (arg[0][i] != '\0' && arg[0][i] != '=')
	{
		if (!expand_token(arg[0][i]))
		{
			error("minishell: export: '", arg[0], "': invalide identifier\n");
			return (1);
		}
		i++;
	}
	if (ft_strchr(arg[0], '='))
	{
		if (!search_replace(arg[0], env))
		{
			s = ft_strdup(arg[0]);
			node = ft_lstnew(s);
			if (node)
				ft_lstadd_back(env, node);
			else
				return (1);
		}
	}
	return (0);
}

int	unset(char **arg, t_list **env, t_tool *data)
{
	char	*s;
	int		t; 
	t_list *first;

	(void)arg;
	(void)data;
	if (!env || !arg || !arg[0])
		return (1);
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
	return (0);
}

int	echo(char **arg, t_list **env, t_tool *data)
{
	int	opt;
	int	i;
	int	w;

	opt = 0;
	i = 0;
	w = 0;
	(void)env;
	(void)data;
	if (!arg || !arg[0])
		return (1);
	if (!ft_strncmp(arg[0], "-n", 3) && ft_strlen(arg[0]) == 2)
	{
		i = 1;
		opt = 1;
	}
	while (arg[i] && arg[i + 1])
		w += printf("%s ", arg[i++]);
	w += printf("%s", arg[i]);
	if (opt == 0)
		w += printf("\n");
	if (w == -1)
		return (perror("echo: "), 1);
	return (0);
}

int	env(char **arg, t_list **env, t_tool *data) // a revoir
{
	(void) arg;
	(void)data;
	t_list *node;
	char	*s;
	
	node = *env;
	while (node)
	{
		s = (char *)node->content;
		if (s[0] != 0)
			printf("%s\n", (char *)node->content);
		node = node->next;
	}
	return (1);
}
