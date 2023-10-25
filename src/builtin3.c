/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:03:24 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 16:03:26 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char **arg, t_list **env, t_tool *data, int flag)
{
	t_list	*node;
	char	*s;

	(void)arg;
	(void)data;
	node = *env;
	while (node)
	{
		s = (char *)node->content;
		if (s[0] != 0)
			flag = printf("%s\n", (char *)node->content);
		node = node->next;
	}
	if (flag == -1)
		return (ft_perror("minishell: env", NULL), 1);
	return (0);
}

int	opt_echo(char **arg)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (arg[x] && !ft_strncmp(arg[x], "-n", 2))
	{
		i = 1;
		while (arg[x][i] != '\0')
		{
			if (arg[x][i++] != 'n')
				return (x - 1);
		}
		x++;
	}
	return (x - 1);
}

int	echo(char **arg, t_list **env, t_tool *data, int flag)
{
	int	opt;
	int	i;

	(void)env;
	(void)data;
	if (!arg || !arg[0])
		return (1);
	opt = opt_echo(arg);
	i = opt + 1;
	while (arg[i] && arg[i + 1])
	{
		if (arg[i][0] || (!arg[i][0] && i == 0))
			flag = printf("%s ", arg[i]);
		i++;
	}
	if (arg[i])
		flag = printf("%s", arg[i]);
	if (opt == -1)
		flag = printf("\n");
	if (flag == -1)
		return (ft_perror("minishell: echo", NULL), 1);
	return (0);
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
