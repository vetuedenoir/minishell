/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:28:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/27 18:20:51 by kscordel         ###   ########.fr       */
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
			return (printf("la commande %s n existe pas \n", s),NULL);
		memory_add(s);
		return (s);
}


char	*get_path(char *str, char **envp)
{
	int		i;
	char	**tb;
	char	*path;
	
	i = 0;
	while (envp[i])
	{
		if (!strncmp(env[i], "PATH", 4))
			break ;
		i++;
	}
	tb = ft_split(&env[i][5], ':'); // utiliser un split qui utilise ft_calloc
	if (!tb)
		//free_garbage();
	i = 0;
	while (tb[i])
	{
		path = ft_strjoin(tb[i], "/");
		if (!path)
			return (NULL);
		str = verif_path(path, str);
		if (str)
			break ;
	}
	return (str);
}

void	check_path(t_cmds *commande, char	**env)
{
	t_cmds	*node;
	char	*s;

	node = *commande;
	while (node)
	{
		if (node->redirection)
		{
			s = node->redirection->str;
			ft_strncmp
			if (!ft_strncmp(s, "echo", 5) || !ft_strncmp(s, "cd", 3) ||
				!ft_strncmp(s, "pwd", 4) || !ft_strncmp(s, "export", 7) 
					|| !ft_strncmp(s, "unset", 6), || !ft_strncmp(s, "env", 4) || 
						!ft_strncmp(s, "exit", 5))
				node->builtin = b;
			else
			{
				node->builtin = 0;
				node->redirection->str = get_path(node->redirections->str, env);
			}
        }
		node = node->next;
    }
    
}