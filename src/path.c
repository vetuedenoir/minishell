/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:28:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 20:06:36 by kscordel         ###   ########.fr       */
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
			ft_perror("minishell", str);
			return (NULL);
		}
		else
			return (str);
	}
	else
		return (error("minishell: PATH not set in environnement", \
		NULL, NULL), NULL);
	ft_perror("minishell: ", str);
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
	tb = ft_split(line, ':');
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
	return (ft_perror("minishell: ", str), cleartb(tb), NULL);
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

int	check_path(t_cmds **commande, t_list *env, t_tool *data)
{
	char	*path;

	path = get_line(env);
	if ((*commande)->str && (*commande)->str[0])
	{
		(*commande)->builtin = set_builtin((*commande)->str[0]);
		if (!(*commande)->builtin)
			(*commande)->str[0] = get_path((*commande)->str[0], \
			path, data);
		if ((*commande)->str[0] == NULL)
			return (1);
	}
	else
		return (1);
	return (0);
}
