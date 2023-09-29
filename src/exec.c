/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:33:53 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/29 13:29:16 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(void (*builtin)(char **arg, t_list **env, t_tool *data), t_cmds *cmd, t_tool *data)
{   
	builtin(&cmd->str[1], &data->var_env, data);	
}

void	exec_com(t_tool *data, t_cmds *cmd)
{
	close(data->base_fd[0]);
	close(data->base_fd[1]);
	//dprintf(2, "EXEC_COM\n");
	if (cmd->num_redirections != 0)
	{
		check_redir(cmd);
	}
	if (cmd->builtin)
	{
		exec_builtin(cmd->builtin, cmd, data);
	}
	else if (!cmd->str || cmd->str[0] == NULL)
		exit(1);
	else if (!access(cmd->str[0], X_OK))
		execve(cmd->str[0], cmd->str, lst_to_tab(data->var_env, data));
	
}


void	simp_com(t_tool *data, t_cmds *cmd)
{
	pid_t	pid;
	int		status;

	check_heredoc(cmd, data);
	if (cmd->builtin)
	{
		if (!ft_strncmp(cmd->str[0], "exit", 4))
		{
			//dprintf(2, "builin est egal a exit\n");
			close(data->base_fd[0]);
			close(data->base_fd[1]);
		}   
		exec_builtin(cmd->builtin, cmd, data);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		exec_com(data, cmd);
	}
	waitpid(pid, &status, 0);
}
void    ft_fork(t_tool *data, int fd[2], int infile, t_cmds *cmd, int i)
{
  
	data->pid[i] = fork();
	if (data->pid[i] == 0)
	{
		close(data->base_fd[0]);
		close(data->base_fd[1]);
		if (cmd->prev && cmd->next && dup2(infile, STDIN_FILENO) == -1)
		   ft_putstr_fd("ERREUR fonction dup2 stin\n", 2);
		close(fd[0]);
		if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
			ft_putstr_fd("ERREUR fonction dup2 stdout\n", 2);
		close(fd[1]);
		if (cmd->prev)
			close(infile);
		exec_com(data, data->cmds);
	}
	else
	{
		if (close(fd[1]) == -1 || dup2(fd[0], 0) == -1
			|| close(fd[0]) == -1)
			exit(1);
	}
}

void    size_nb_com(t_tool *data)
{
	t_cmds  *start;
	int j;

	j = 0;
	start= data->cmds;
	while(data->cmds != NULL)
	{
		data->cmds = data->cmds->next;
		j++;
	}
	data->pid = malloc(j * sizeof(pid_t));
	data->cmds = start;
	// printf("size malloc pid = %d\n", j);
}
int    child(t_tool *data, t_cmds *cmds, int i, int infile)
{   
	int     fd[2];

	//dprintf(2, "i = %d et cmd = %s\n", i, cmds->str[0]);
	if (pipe(fd) == -1)
		exit(1);
	check_heredoc(cmds, data);
	ft_fork(data, fd, infile, cmds, i);
	close(fd[1]);
	if (cmds->prev)
		close(infile);
	if (cmds->file_name)
	{
		close(fd[0]);
		infile = open(cmds->file_name, O_RDONLY);
	}
	else
		infile = fd[0];
	data->cmds = data->cmds->next;
	return (infile);
}

void    multi_com(t_tool *data)
{
	int     infile;
	//t_cmds  *start;
	t_cmds  *tmp;
	int i;

	i = 0;
	//start = data->cmds;
	tmp = data->cmds;
	//infile = STDIN_FILENO;
	size_nb_com(data);
	while(data->cmds != NULL)
	{
		infile = child(data, tmp, i++, infile);
		tmp= tmp->next;
	}
	close(infile);
	int j;
	j = 0;
	while (j < i)
	{
		waitpid(data->pid[j], NULL, 0);
		j++;
	}
	//data->cmds = start;
	free(data->pid);
}
void    ft_exec(t_tool *data)
{
	t_cmds *cmd;

	cmd = data->cmds;
	printf("debut de ft_exec\n");
	if (cmd->next == NULL)
		simp_com(data, cmd);
	else
		multi_com(data);
	while(cmd)
	{
		if (cmd->file_name)
		{
			unlink(cmd->file_name);
			free(cmd->file_name);
		}
		cmd= cmd->next;
	}
	// if (cmd->file_name)
	// {
	// 	unlink(cmd->file_name);
	// }
	dprintf(2, "NORMALEMENT jsuis bien\n");
}