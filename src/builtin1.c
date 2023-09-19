/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:38:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/19 17:21:53 by kscordel         ###   ########.fr       */
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
	t_list *first;
	t_list	*node;
	char	*s;
	int		t;
	
	node = NULL;
	first = *env;
	t = ft_strchr_int(var, '=');
	while (*env)
	{
		s = (char *)(*env)->content;
		if (!ft_strncmp(s, var, t) && s[t] == '=')
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

void	export(char **arg, t_list **env)
{
	t_list	*node;
	char	*s;

	(void) arg;
	if (!env || !arg || !arg[0])
		return ;
	if (ft_strchr(arg[0], '='))
	{
		if (!search_replace(arg[0], env))
		{
			s = ft_strdup(arg[0]);
			node = ft_lstnew(s);
			if (node)
				ft_lstadd_back(env, node);
		}
	}
}

void	unset(char **arg, t_list **env)
{
	char	*s;
	int		t; 
	t_list *first;

	(void)arg;
	if (!env || !arg || !arg[0])
		return ;
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

void	echo(char **arg, t_list **env)
{
	int	opt;
	int	i;

	opt = 0;
	i = 0;
	(void)env;
	if (!arg || !arg[0])
		return ;
	if (!ft_strncmp(arg[0], "-n", 3) && ft_strlen(arg[0]) == 2)
	{
		i = 1;
		opt = 1;
	}
	while (arg[i] && arg[i + 1])
		printf("%s ", arg[i++]);
	printf("%s", arg[i]);
	if (opt == 0)
		printf("\n");
}

void	env(char **arg, t_list **env) // a revoir
{
	(void) arg;
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
}
