/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:28:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/06 17:39:05 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verif_path(char **path, char *str, t_tool *data)
{
	char	*s;

	s = ft_strjoin(*path, str);
	free(*path);
	if (!s)
		return (NULL);
	if (access(s, X_OK))
		return (free(s), NULL);
	memory_add(s, data);
		return (s);
}

char	*true_path(char *str)
{
	if (ft_strchr(str, '/'))
	{
		if (access(str, X_OK))
		{
			error("Minishell: ", str, ": commande not found");
			//error("Minishell: la commande '", str, "' est introuvable");
			return (NULL);
		}
		else
			return (str);
	}
	error("Minishell: ", str, ": commande not found");
	//error("Minishell: la commande '", str, "' est introuvable");
	return (NULL);
}

char	*get_path(char *str, char *line, t_tool *data)
{
	int		i;
	char	**tb;
	char	*path;
	char	*s;
	
	i = 0;
	if (line == NULL || ft_strchr(str, '/'))
		return (true_path(str));
	if (str[0] == '\0')
		return (NULL);
	tb = ft_split(line, ':'); // utiliser un split qui utilise ft_calloc
	if (!tb)
		return (free_garbage(data), NULL);
	i = 0;
	while (tb[i])
	{
		path = ft_strjoin(tb[i], "/");
		if (!path)
			return (cleartb(tb), free_garbage(data), NULL);
		s = verif_path(&path, str, data);
		if (s)
			return (cleartb(tb), s);
		i++;
	}
	return (error("Minishell: ", str, ": commande not found"),
	//return (error("Minishell: la commande '", str, "' est introuvable"),
		cleartb(tb), NULL);
}

char	*get_line(t_list *env)
{
	while (env)
	{
		if (!strncmp((char *)env->content, "PATH", 4))
			return ((char *)env->content);
		env = env->next;
	}
	return (NULL);
}

void	*set_builtin(char *s)
{
	if (!ft_strncmp(s, "echo", 5))
		return (&echo);
	if (!ft_strncmp(s, "cd", 3))
		return (&cd);
	if (!ft_strncmp(s, "pwd", 4))
		return (&pwd);
	if (!ft_strncmp(s, "export", 7))
		return (&export);
	if (!ft_strncmp(s, "unset", 6))
		return (&unset);
	if (!ft_strncmp(s, "env", 4))
		return (&env);
	if (!ft_strncmp(s, "exit", 5))
		return (&ft_exit);
	return (NULL);
	
}

void	check_path(t_cmds **commande, t_list *env, t_tool *data)
{
	char	*path;
	t_cmds	*node;

	node = *commande;
	path = get_line(env);
	while (*commande != NULL)
	{
		if ((*commande)->str && (*commande)->str[0])
		{
			(*commande)->builtin = set_builtin((*commande)->str[0]);
			if (!(*commande)->builtin)
				(*commande)->str[0] = get_path((*commande)->str[0],\
				path, data);
		}
		
		if (data->garbage_collector == NULL)
			break ;
		(*commande) = (*commande)->next;
	}
	*commande = node;
}
