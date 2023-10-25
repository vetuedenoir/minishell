/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:54:08 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 15:53:46 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(int (*builtin)(char **arg, t_list **env, t_tool *data, int flag), t_cmds *cmd, t_tool *data, int flag)
{
	if (!ft_strncmp(cmd->str[0], "exit", 5))
	{
		close(data->base_fd[0]);
		close(data->base_fd[1]);
	}
	return (builtin(&cmd->str[1], &data->var_env, data, flag));
}

int	size_nb_com(t_tool *data)
{
	t_cmds	*start;
	int		j;

	j = 0;
	start = data->cmds;
	while (data->cmds != NULL)
	{
		data->cmds = data->cmds->next;
		j++;
	}
	data->pid = ft_calloc(sizeof(pid_t), j + 1);
	if (!data->pid)
		return (ft_perror("minishell", NULL), 1);
	data->cmds = start;
	return (0);
}

void	exec_com(t_tool *data, t_cmds *cmd)
{
	close(data->base_fd[0]);
	close(data->base_fd[1]);
	if (check_path(&cmd, data->var_env, data))
		free_all_and_exit(127, data);
	if (check_redir(cmd))
		free_all_and_exit(1, data);
	if (cmd->builtin)
		free_all_and_exit(exec_builtin(cmd->builtin, cmd, data, 1), data);
	if (execve(cmd->str[0], cmd->str, lst_to_tab(data->var_env, data)) == -1)
	{
		ft_perror("minishell", NULL);
		free_all_and_exit(127, data);
	}
}

int	ft_fork(t_tool *data, int fd[2], int infile, t_cmds *cmd, int i)
{
	data->pid[i] = fork();
	if (data->pid[i] == -1)
	{
		ft_perror("minishell", NULL);
		return (-1);
	}
	if (data->pid[i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(data->base_fd[0]);
		close(data->base_fd[1]);
		//if (cmd->prev && cmd->file_name && dup2(infile, STDIN_FILENO) == -1)
		//	ft_perror("minishell", NULL);
		close(fd[0]);
		if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
			ft_perror("minishell", NULL);
		close(fd[1]);
		if (cmd->prev)
			close(infile);
		exec_com(data, data->cmds);
	}
	else
	{
		g_exitcode = 2000;
		if (close(fd[1]) == -1 || dup2(fd[0], 0) == -1
			|| close(fd[0]) == -1)
			wait(NULL);
	}
	return (0);
}

int	child(t_tool *data, t_cmds *cmds, int i, int infile)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) == -1)
		return (ft_perror("minishell", NULL), -1);
	ret = check_heredoc(cmds, data, fd);
	if (ret < 0)
		return (ret);
	ret = ft_fork(data, fd, infile, cmds, i);
	close(fd[1]);
	if (cmds->prev)
		close(infile);
	infile = fd[0];
	if (ret == -1)
		return (ret);
	return (infile);
}

void	wait_processes(t_tool *data, int sig, int status)
{
	int	i;
	t_cmds *node;
	
	i = 0;
	node = data->cmds;
	while (data->cmds && data->pid[i])
	{
		waitpid(data->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exitcode = status % 255;
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == 2)
				g_exitcode = 130;
			if (sig == 3)
				g_exitcode = 131;
		}
		i++;
		data->cmds = data->cmds->next;
	}
	if (sig == 2)
		printf("\n");
	if (sig == 3)
		printf("Quit (core dumped)\n");
	data->cmds = node;
	free(data->pid);
}

void	nmulti_com(t_tool *data)
{
	t_cmds	*cmd;
	int		infile;
	int		i;

	cmd = data->cmds;
	if (size_nb_com(data))
		return ;
	i = 0;
	while (data->cmds != NULL)
	{
		infile = child(data, data->cmds, i++, infile);
		if (infile == -1)
		{
			g_exitcode = 1;
			break ;
		}
		else if (infile == -2)
			break ;
		data->cmds = data->cmds->next;
	}
	data->cmds = cmd;
	if (infile != -1 && infile != -2)
		close(infile);
	wait_processes(data, 0, 0);
}

void	nsimp_com(t_tool *data, t_cmds *cmd)
{
	if (check_heredoc(cmd, data, NULL) < 0)
		return ;
	if (!cmd->str)
		return ;
	if (check_path(&cmd, data->var_env, data))
		return (g_exitcode = 127, (void)0);
	if (cmd->builtin)
	{
		if (check_redir(cmd))
			return (g_exitcode = 1, (void)0);
		return (g_exitcode = exec_builtin(cmd->builtin, cmd, data, 0), (void)0);
	}
	if (size_nb_com(data))
		return ;
	data->pid[0] = fork();
	if (data->pid[0] == -1)
	{
		g_exitcode = 1;
		return ;
	}
	if (data->pid[0] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		exec_com(data, cmd);
	}
	g_exitcode = 2000;
	wait_processes(data, 0, 0);
}

void	ft_exec(t_tool *data)
{
	t_cmds	*cmd;

	cmd = data->cmds;
	if (cmd->next == NULL)
		nsimp_com(data, cmd);
	else
		nmulti_com(data);
	while (cmd)
	{
		if (cmd->file_name)
			unlink(cmd->file_name);
		cmd = cmd->next;
	}
}
