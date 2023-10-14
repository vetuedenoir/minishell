/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:27:43 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/14 13:43:08 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **arg, t_list **env, t_tool *data, int flag)
{
	int	i;
	int	code;

	code = 0;
	i = 0;
	if (arg && arg[0])
	{
		if (arg[1])
			return (error("Minishell: exit: too many argument", NULL, NULL), 1);
		if (arg[0][0] != '-' && arg[0][0] != '+' && !ft_isdigit(arg[0][0]))
			return (error("Minishell: exit: numeric argument required", NULL, NULL), 1);
		if (arg[0][0] == '-' || arg[0][0] == '+')
			i = 1;
		while (arg[0][i])
		{
			if (!ft_isdigit(arg[0][i++]))
				return (error("Minishell: exit: numeric argument required", NULL, NULL), 1);
		}
		code = ft_atoi(arg[0]);
	}
	if (!flag)
		printf("exit\n");
	ft_lstclear(env, free);
	rl_clear_history();
	free_garbage(data);
	exit(code);
}

int	pwd(char **arg, t_list **env, t_tool *data, int flag)
{
	char	*pwd;

	(void)arg;
	(void)env;
	(void)data;
	(void)flag;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	return (0);
}

/* modifier la variable PWd et OLDPWD*/
int	cd(char **arg, t_list **env, t_tool *data, int flag)
{
	char	*pwd[2];
	char	*str;
	char	*old[2];
	
	(void)env;
	(void)flag;
	old[1] = NULL;
	pwd[1] = NULL;
	if (chdir(arg[0]))
	{
		perror("cd");
		return (1);
	}
	pwd[0] = get_var("PWD", *env);
	old[0] = ft_strjoin("OLDPWD=", pwd[0]);
	free(pwd[0]);
	export(old, env, data, 0);
	str = NULL;
	str = getcwd(str, 0);
	pwd[0] = ft_strjoin("PWD=", str);
	free(str);
	export(pwd, env, data, 0);
	free(pwd[0]);
	return (0);
}
