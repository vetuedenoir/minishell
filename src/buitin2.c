/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:27:43 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/22 19:53:17 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit(t_list **env, char **arg)
{
	int i;
	int code;

	code = 0;
	if (arg && arg[0])
	{
		if (arg[1])
			return ((void)printf("too many argument\n"));
		if (!ft_isdigit(arg[0][0]) && arg[0][0] != '-' && arg[0][0] != '+')
			return ((void)printf("numeric argument required\n"));
		i = 0;
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

/*Pour cd utiliser opendir, readdir et closedir*/