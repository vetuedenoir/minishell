/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:51:11 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 14:15:50 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signo)
{
	if (g_exitcode != 2000 && g_exitcode != 2130)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (g_exitcode != 2130)
		g_exitcode += 128 + signo;
}

void	sigint_heredoc(int signo)
{
	g_exitcode = 128 + signo;
}
