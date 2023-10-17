/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:15:12 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/17 20:27:55 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_heredoc(int fd, t_tool *data)
{
	char	*ret;

	while (1)
	{
		ret = get_next_line(data->base_fd[0]);
		if ((ft_strncmp(ret, heredoc->str, ft_strlen(heredoc->str)) == 0
			&& ft_strlen(heredoc->str) == ft_strlen(ret) - 1) || G_ExitCode == 130)
		{
			get_next_line(-99);
			free(ret);
			close(fd);
			free_all_and_exit(G_ExitCode, data);
		}
		ft_putstr_fd(heredoc_expand(ret, data), fd);
		free(ret);
	}
}

int ft_heredoc(t_lexer *heredoc, char *file_name, t_tool *data)
{
	pid_t	pid;
	int		fd;
	char	*ret;

	pid = fork()
	if (pid = -1)
		return (perror("minishell: heredoc"), -1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sigint_handler);
		close(data->base_fd[0]);
		close(data->base_fd[1]);
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		free(file_name);
		if (fd < 0)
		{
			perror("minishell: heredoc"), -1;
			free_all_and_exit(1, data);
		}
		read_heredoc(fd, data);
		free_all_and_exit(G_ExitCode, data);
    }
	return (pid);
}

int	check_heredoc(t_cmds *cmd, t_tool *data)
{
	t_lexer	*start;
	pid_t	pid;
	int		status;

	start = cmd->redirection;
	while (cmd->redirection)
	{
		if (cmd->redirection->token == 4)
		{
			if (cmd->file_name)
				free(cmd->file_name);
			cmd->file_name = heredoc_filename();
			pid = ft_heredoc(cmd->redirection->next, cmd->file_name, data);
			if (pid = -1)
				break ;
			waitpid(pid, status, 0);
			G_ExitCode = status;
		}
		cmd->redirection = cmd->redirection->next;
	}
	cmd->redirection = start;
}