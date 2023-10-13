/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:27:43 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/13 13:48:55 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **arg, t_list **env, t_tool *data)
{
	int	i;
	int	code;

	code = 0;
	i = 0;
	if (arg && arg[0])
	{
		if (arg[1])
			return ((void)printf("Minishell: exit: too many argument\n"), 1);
		if (arg[0][0] != '-' && arg[0][0] != '+' && !ft_isdigit(arg[0][0]))
			return ((void)printf("Minishel: exit: numeric argument required\n"), 1);
		if (arg[0][0] == '-' || arg[0][0] == '+')
			i = 1;
		while (arg[0][i])
		{
			if (!ft_isdigit(arg[0][i++]))
				return ((void)printf("Minishel: exit:numeric argument required\n"), 1);
		}
		code = ft_atoi(arg[0]);
	}
	printf("exit\n");
	ft_lstclear(env, free);
	rl_clear_history();
	free_garbage(data);
	exit(code);
}

/*Pour cd utiliser opendir, readdir et closedir , chdir getcwd*/

int	pwd(char **arg, t_list **env, t_tool *data)
{
	char	*pwd;

	(void)arg;
	(void)env;
	(void)data;
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
int	cd(char **arg, t_list **env, t_tool *data)
{
	char	*pwd[2];
	char	*str;
	char	*old[2];
	
	(void)env;
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
	export(old, env, data);
	str = NULL;
	str = getcwd(str, 0);
	pwd[0] = ft_strjoin("PWD=", str);
	free(str);
	export(pwd, env, data);
	free(pwd[0]);
	return (0);
}
