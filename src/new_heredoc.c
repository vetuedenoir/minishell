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

char	*heredoc_filename(t_tool *data)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(".tmp_heredoc_file_", num);
	memory_add(file_name, data);
	free(num);
	return (file_name);
}

void	read_heredoc(t_lexer *heredoc, int fd, t_tool *data)
{
	char	*ret;
	char	*join;

	while (1)
	{
		rl_getc_function = getc;
		ret = readline(">");
		if (!ret)
		{
			close(fd);
			return ;
			//free_all_and_exit(G_ExitCode, data);
		}
		if ((ft_strncmp(ret, heredoc->str, ft_strlen(heredoc->str)) == 0
			&& ft_strlen(heredoc->str) == ft_strlen(ret)))
		{
			free(ret);
			close(fd);
			return ;
		}
		join = ft_strjoin(ret, "\n");
		ft_putstr_fd(heredoc_expand(join, data), fd);
		free(ret);
		free(join);
	}
}

int ft_heredoc(t_lexer *heredoc, char *file_name, t_tool *data, int *pipefd)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: heredoc"), -1);
	if (pid == 0)
	{
		G_ExitCode = 0;
		if (pipefd)
		{	close(pipefd[0]);
			close(pipefd[1]);
		}
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sigint_heredoc);
		//close(data->base_fd[0]);
		close(data->base_fd[1]);
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
		{
			close(data->base_fd[0]);
			perror("minishell: heredoc");
			free_all_and_exit(1, data);
		}
		read_heredoc(heredoc, fd, data);
		close(data->base_fd[0]);
		printf("ce putin ExitCODE = %d\n", (unsigned int)G_ExitCode);
		free_all_and_exit(G_ExitCode, data);
	}
	return (pid);
}

int	check_heredoc(t_cmds *cmd, t_tool *data, int *pipefd)
{
	t_lexer	*start;
	pid_t	pid;
	int		status;

	start = cmd->redirection;
	while (cmd->redirection)
	{
		if (cmd->redirection->token == 4)
		{
			cmd->file_name = heredoc_filename(data);
			pid = ft_heredoc(cmd->redirection->next, cmd->file_name, data, pipefd);
			if (pid == -1)
				break ;
			waitpid(pid, &status, 0);
			G_ExitCode = status % 255;
			if (G_ExitCode == 130)
			{
				if (pipefd)
				{
					close(pipefd[0]);
					close(pipefd[1]);
				}	
				return (-2);
			}
		}
		cmd->redirection = cmd->redirection->next;
	}
	cmd->redirection = start;
	return (0);
}
