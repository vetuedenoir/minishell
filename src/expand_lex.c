/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:03:51 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 16:03:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand(t_tool *data)
{
	t_cmds	*tmp;

	tmp = data->cmds;
	while (data->cmds)
	{
		if (data->cmds->str)
			data->cmds->str = handle_arg(data->cmds->str, data);
		if (data->cmds->redirection)
			data->cmds->redirection = \
			handle_redirection(data->cmds->redirection, data);
		data->cmds = data->cmds->next;
	}
	data->cmds = tmp;
}

t_lexer	*ft_lexer(t_tool *data)
{
	char	**tab;
	char	*arg;
	int		i;
	t_lexer	*lex;
	t_lexer	*new;

	lex = NULL;
	tab = NULL;
	if (ft_verif_quote(data->line))
		return (NULL);
	arg = add_space(data->line, data);
	if (!arg)
		return (NULL);
	tab = ft_decoup(arg, tab, ' ', data);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new = check_word(tab[i++], data);
		if (!new)
			return (free_garbage(data), NULL);
		ft_add_back_lexer(&lex, new);
	}
	return (lex);
}
