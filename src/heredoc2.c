/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:48:57 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/26 12:22:44 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	erreur_here(int	*pipefd)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}	
	return (-2);
}

void	ft_close(t_tool *data, int *pipefd)
{
	g_exitcode = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint_heredoc);
	close(data->base_fd[1]);
	if (pipefd)
	{	
		close(pipefd[0]);
		close(pipefd[1]);
		if (dup2(data->base_fd[0], 0) == -1)
		{
			close(data->base_fd[0]);
			ft_perror("minishell: heredoc", NULL);
			free_all_and_exit(1, data);
		}
	}
}
