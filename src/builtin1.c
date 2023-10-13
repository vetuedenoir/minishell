/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:38:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/13 16:22:15 by kscordel         ###   ########.fr       */
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
	if (ft_isdigit(str[i]) || !expand_token(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!expand_token(str[i]))
			return (0);
		i++;
	}
	if (ft_isdigit(str[i - 1]))
		return (0);
	return (i);
}

int	export(char **arg, t_list **env, t_tool *data)
{
	t_list	*node;
	char	*s;
	int		x;

	(void) arg;
	(void)data;
	x = -1;
	if (!env || !arg || !arg[0])
		return (1);
	while (arg[++x])
	{
		if (!valide_identifier(arg[x]))
		{
			error("minishell: export: '", arg[x], "': invalide identifier\n");
			return (1);
		}
		if (ft_strchr(arg[x], '='))
		{
			if (!search_replace(arg[x], env))
			{
				s = ft_strdup(arg[x]);
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
	t_list *first;

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

int	unset(char **arg, t_list **env, t_tool *data)
{
	int	x;

	(void)data;
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

int    opt_echo(char **arg)
{
    int x;
    int    i;
    
    x = 0;
    i = 0;
    while (arg[x] && !ft_strncmp(arg[x], "-n", 2))
    {
        i = 1;
        while (arg[x][i] != '\0')
        {
            if (arg[x][i++] != 'n')
            {
                return (x - 1);
            }
        }
        x++;
    }
    return (x - 1);
}

int    echo(char **arg, t_list **env, t_tool *data)
{
    int    opt;
    int    i;
    int    w;

    w = 0;
    (void)env;
    (void)data;
    if (!arg || !arg[0])
        return (1);
    opt = opt_echo(arg);

    i = opt + 1;
    while (arg[i] && arg[i + 1])
    {
		if (arg[i][0] || (!arg[i][0] && i == 0))
			w += printf("%s ", arg[i]);
			//ft_putstr_fd(arg[i], STDOUT_FILENO);
		i++;
	}
		
    if (arg[i])
        w += printf("%s", arg[i]);
		//ft_putstr_fd(arg[i], STDOUT_FILENO);
    if (opt == -1)
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
