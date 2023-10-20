/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:06:31 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/20 21:48:46 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ajout_file(t_lexer *redir, int i)
{
	int fd;

	if (i == 1 || i == 3)
		fd = open(redir->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (i == 2 || i == 4)
        fd = open(redir->next->str, O_RDONLY, 0644);
	if (fd == -1)
		return (perror("minishell"), 1);
    if (dup2(fd, STDOUT_FILENO) == -1)
        return (close(fd), perror("minishell"), 1)
	close(fd);
    return (0);
}

int check_redir(t_cmds *cmd)
{
	t_lexer *start;
    int     ret;

    ret = 0;
	start = cmd->redirection;
	while (cmd->redirection != NULL)
	{
		if (cmd->redirection->token == 1)
			ret = ajout_file(cmd->redirection,1);
		else if (cmd->redirection->token == 3)
			ret = ajout_file(cmd->redirection, 3);
		else if (cmd->redirection->token == 2)
			ret = ajout_file(cmd->redirection, 2, cmd->file_name);
		else if (cmd->redirection->token == 4)
			ret = ajout_file(cmd->redirection, 4, cmd->file_name);
        if (ret == 1)
            return (1);
		cmd->redirection = cmd->redirection->next;
	}
	cmd->redirection = start;
    return (0);
}
