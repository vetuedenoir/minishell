#include "../minishell.h"

void	ft_heredoc(t_lexer *heredoc, char *file_name, t_tool *data)
{
	int			fd;
	char		*ret;

	dprintf(2, "file = %s\n", file_name);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		dprintf(2, "pas normal fd heredoc\n");
	while (1)
	{
		ret = get_next_line(data->base_fd[0]);
		if (ft_strncmp(ret, heredoc->str, ft_strlen(heredoc->str)) == 0
			&& ft_strlen(heredoc->str) == strlen(ret) - 1)
		{
			get_next_line(-99);
			free(ret);
			close(fd);
			return ;
		}
		ft_putstr_fd(heredoc_expand(ret, data), fd);
		free(ret);
	}
}

char	*heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(".tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

void	check_heredoc(t_cmds *cmd, t_tool *data)
{
	t_lexer	*start;

	start = cmd->redirection;
	while (cmd->redirection)
	{
		if (cmd->redirection->token == 4)
		{
			dprintf(2, "OUI YA UN HEREDOC DETECTER\n");
			if (cmd->file_name)
				free(cmd->file_name);
			cmd->file_name = heredoc_filename();
			ft_heredoc(cmd->redirection->next, cmd->file_name, data);
		}
		cmd->redirection = cmd->redirection->next;
	}
	cmd->redirection = start;
}
