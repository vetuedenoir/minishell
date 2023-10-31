/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:27:43 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/31 12:47:32 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_clear_exit(t_list **env, t_tool *data, int code)
{
	ft_lstclear(env, free);
	rl_clear_history();
	free_garbage(data);
	exit(code);
}

int	ft_exit(char **arg, t_list **env, t_tool *data, int flag)
{
	int	i;
	int	code;

	code = 0;
	i = 0;
	if (arg && arg[0])
	{
		if (arg[1])
			return (error("minishell: exit: too many argument", NULL, NULL), 1);
		if (arg[0][0] != '-' && arg[0][0] != '+' && !ft_isdigit(arg[0][0]))
			return (error("minishell: exit: numeric argument required", \
			NULL, NULL), 1);
		if (arg[0][0] == '-' || arg[0][0] == '+')
			i = 1;
		while (arg[0][i])
		{
			if (!ft_isdigit(arg[0][i++]))
				return (error("minishell: exit: numeric argument required", \
				NULL, NULL), 1);
		}
		code = ft_atoi(arg[0]);
	}
	if (!flag)
		printf("exit\n");
	return (ft_clear_exit(env, data, code));
}

int	pwd(char **arg, t_list **env, t_tool *data, int flag)
{
	char	*pwd;

	(void)arg;
	(void)env;
	(void)data;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		ft_perror("pwd", NULL);
		return (1);
	}
	flag = printf("%s\n", pwd);
	if (flag == -1)
		return (ft_perror("minishell: pwd", NULL), 1);
	return (0);
}

int	ft_cd_bis(char *str, char *pwd[2], t_list **env, t_tool *data)
{
	str = getcwd(str, 0);
	if (!str)
		return (ft_perror("minishell: cd", NULL), 1);
	pwd[0] = ft_strjoin("PWD=", str);
	free(str);
	if (!pwd[0])
		return (ft_perror("minishell: cd", NULL), 1);
	export(pwd, env, data, 0);
	free(pwd[0]);
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
	if (!arg[0])
		return (0);
	if (chdir(arg[0]))
		return (ft_perror("cd", NULL), 1);
	pwd[0] = get_var("PWD", *env);
	if (!pwd[0])
		return (ft_cd_bis(NULL, pwd, env, data));
	old[0] = ft_strjoin("OLDPWD=", pwd[0]);
	free(pwd[0]);
	if (!old[0])
		return (ft_perror("minishell: cd", NULL), 1);
	export(old, env, data, 0);
	str = NULL;
	return (ft_cd_bis(str, pwd, env, data));
}
