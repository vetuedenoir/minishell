/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:38:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/18 20:54:19 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(char **arg, t_list **env)
{
	t_list	*node;

	(void) arg;
	if (!env || !arg || !arg[0])
		return ;
	if (ft_strchr(arg[0], '='))
	{
		node = ft_lstnew(arg[0]);
		if (node)
			ft_lstadd_back(env, node);
	}
}

void	unset(char **arg, t_list **env)
{
	char	*s;

	(void)arg;
	if (!env || !arg || !arg[0])
		return ;
	while (*env)
	{
		s = (char *)(*env)->content;
		if (!ft_strncmp(arg[0], s, ft_strlen(arg[0]) + 1))
		{
			free(s);
			(*env)->content = NULL;
		}
		*env = (*env)->next;
	}
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
	while (arg[i])
		printf("%s", arg[i++]);
	if (!opt)
		write(1, "\n", 1);
}

void	env(char **arg, t_list **env) // a revoir
{
	(void) arg;
	t_list *node;
	node = *env;
	while (node)
	{
		printf("%s\n", (char *)node->content);
		node = node->next;
	}
}
