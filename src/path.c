/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:28:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/29 13:07:18 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*verif_path(char *path, char *str)
{
	char	*s;

	s = ft_strjoin(path, str);
		free(path);
		if (!s)
			return (0);
		if (access(s, X_OK))
			return (NULL);
		memory_add(s);
		return (s);
}


char	*get_path(char *str, char **envp)
{
	int		i;
	char	**tb;
	char	*path;
	char	*s;
	
	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH", 4))
			break ;
		i++;
	}
	tb = ft_split(&envp[i][5], ':'); // utiliser un split qui utilise ft_calloc
	if (!tb)
		free_garbage();
	i = 0;
	while (tb[i])
	{
		path = ft_strjoin(tb[i], "/");
		if (!path)
			return (NULL);
		s = verif_path(path, str);
		if (s)
			return (s);
		i++;
	}
	return (printf("la commande %s n existe pas \n", str), NULL);
}

void	check_path(t_cmds **commande, char	**env)
{
	char	*s;
	t_cmds	*node;

	node = *commande;
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
				(*commande)->str[0] = get_path((*commande)->str[0], env);
			}
        }
		(*commande) = (*commande)->next;
    }
    *commande = node;
}