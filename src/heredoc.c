/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:15:12 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/26 12:36:48 by kscordel         ###   ########.fr       */
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
			return ;
		if ((ft_strncmp(ret, heredoc->str, ft_strlen(heredoc->str)) == 0
				&& ft_strlen(heredoc->str) == ft_strlen(ret)))
			return (free(ret), (void)0);
		join = ft_strjoin(ret, "\n");
		free(ret);
		if (!join)
			return (g_exitcode = 1, (void)1);
		ret = heredoc_expand(join, data);
		free(join);
		if (!ret)
			return (g_exitcode = 1, (void)1);
		ft_putstr_fd(ret, fd);
	}
}

int	ft_heredoc(t_lexer *heredoc, char *file_name, t_tool *data, int *pipefd)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
		return (ft_perror("minishell: heredoc", NULL), -1);
	if (pid == 0)
	{
		ft_close(data, pipefd);
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
		{
			close(data->base_fd[0]);
			ft_perror("minishell: heredoc", NULL);
			free_all_and_exit(1, data);
		}
		read_heredoc(heredoc, fd, data);
		close(data->base_fd[0]);
		close(fd);
		free_all_and_exit(g_exitcode, data);
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
			pid = ft_heredoc(cmd->redirection->next, cmd->file_name,
					data, pipefd);
			if (pid == -1)
				break ;
			waitpid(pid, &status, 0);
			g_exitcode = status % 255;
			if (g_exitcode > 0)
				return (erreur_here(pipefd));
		}
		cmd->redirection = cmd->redirection->next;
	}
	cmd->redirection = start;
	return (0);
}
