/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:27:43 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/21 13:47:36 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **arg, t_list **env)
{
	int	i;
	int	code;

	code = 0;
	i = 0;
	if (arg && arg[0])
	{
		if (arg[1])
			return ((void)printf("too many argument\n"));
		if (arg[0][0] != '-' && arg[0][0] != '+' && !ft_isdigit(arg[0][0]))
			return ((void)printf("numeric argument required\n"));
		if (arg[0][0] == '-' || arg[0][0] == '+')
			i = 1;
		while (arg[0][i])
		{
			if (!ft_isdigit(arg[0][i++]))
				return ((void)printf("numeric argument required\n"));
		}
		code = ft_atoi(arg[0]);
	}
	ft_lstclear(env, free);
	rl_clear_history();
	free_garbage();
	exit(code);
}

/*Pour cd utiliser opendir, readdir et closedir , chdir getcwd*/

void	pwd(char **arg, t_list **env)
{
	char	*pwd;

	(void)arg;
	(void)env;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", pwd);
}

/* modifier la variable PWd et OLDPWD*/
void	cd(char **arg, t_list **env)
{
	char	*pwd;
	char	*str;
	char	*old;
	
	(void)env;
	if (chdir(arg[0]))
	{
		perror("cd");
		return ;
	}
	pwd = get_var("PWD", *env);
	old = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	export(&old, env);
	str = NULL;
	str = getcwd(str, 0);
	pwd = ft_strjoin("PWD=", str);
	free(str);
	export(&pwd, env);
	free(pwd);
}
