/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:51:11 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/17 20:30:09 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signo)
{
	//static unsigned char mem;
	
	if (G_ExitCode == 0 || G_ExitCode == 130)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	//printf(" G = %d ", (unsigned int)G_ExitCode);
	if (G_ExitCode != 200)
		G_ExitCode = 128 + signo;   
}

void	sigint_heredoc(int signo)
{
	G_ExitCode = 128 + signo;
}
