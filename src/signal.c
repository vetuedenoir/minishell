/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:51:11 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/24 18:14:48 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signo)
{
	if (G_ExitCode != 2000 && G_ExitCode != 2130)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (G_ExitCode != 2130)
		G_ExitCode += 128 + signo; 
}

void	sigint_heredoc(int signo)
{
	G_ExitCode = 128 + signo;
}
