/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:28:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/24 19:35:48 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verif_path(char **path, char *str)
{
	char	*s;

	s = ft_strjoin(*path, str);
	free(*path);
	if (!s)
		return (NULL);
	if (access(s, X_OK))
		return (free(s), NULL);
	memory_add(s);
		return (s);
}

char	*true_path(char *str)
{
	if (ft_strchr(str, '/'))
	{
		if (access(str, X_OK))
		{
			printf("la commande %s est introuvable\n", str);
			return (NULL);
		}
		else
			return (str);
	}
	printf("la commande %s est introuvable\n", str);
	return (NULL);
}

char	*get_path(char *str, char *line)
{
	int		i;
	char	**tb;
	char	*path;
	char	*s;
	
	i = 0;
	if (line == NULL || ft_strchr(str, '/'))
		return (true_path(str));
	tb = ft_split(line, ':'); // utiliser un split qui utilise ft_calloc
	if (!tb)
		return (free_garbage(), NULL);
	i = 0;
	while (tb[i])
	{
		path = ft_strjoin(tb[i], "/");
		if (!path)
			return (cleartb(tb), free_garbage(), NULL);
		s = verif_path(&path, str);
		if (s)
			return (cleartb(tb), s);
		i++;
	}
	return (printf("la commande %s est introuvable\n", str),cleartb(tb), NULL);
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

void	check_path(t_cmds **commande, t_list *env)
{
	char	*s;
	char	*path;
	t_cmds	*node;

	node = *commande;
	path = get_line(env);
	while (*commande != NULL)
	{
		if ((*commande)->str && (*commande)->str[0])
		{
			s = (*commande)->str[0];
			if (!ft_strncmp(s, "echo", 5) || !ft_strncmp(s, "cd", 3) ||
				!ft_strncmp(s, "pwd", 4) || !ft_strncmp(s, "export", 7) 
				|| !ft_strncmp(s, "unset", 6) || !ft_strncmp(s, "env", 4) || 
				!ft_strncmp(s, "exit", 5))
				(*commande)->builtin = 'b';
			else
			{
				(*commande)->builtin = 0;
				(*commande)->str[0] = get_path(s, path);
			}
		}
		(*commande) = (*commande)->next;
	}
	*commande = node;
}
