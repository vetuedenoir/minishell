/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:54:21 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/26 14:11:08 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lstnewl(char *str, t_tool *data)
{
	t_lexer	*new;

	new = (t_lexer *)ft_malloc(sizeof(t_lexer), data);
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_add_back_lexer(t_lexer **lst, t_lexer *new)
{
	t_lexer		*temp;

	if (!new)
		return ;
	temp = *lst;
	if (lst && (*lst))
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	else
		*lst = new;
}

void	cleartb(char **tb)
{
	int	i;

	i = 0;
	if (!tb)
		return ;
	while (tb[i] != NULL)
	{
		free(tb[i]);
		i++;
	}
	free(tb);
}

char	**dup_tab(char **tb)
{
	int		i;
	int		t;
	char	**dup;

	if (!tb)
		return (NULL);
	i = 0;
	t = 0;
	while (tb[i++])
		t++;
	dup = malloc(sizeof(char *) * (t + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (tb[i])
	{
		dup[i] = ft_strdup(tb[i]);
		if (!dup[i])
			return (cleartb(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	clear_lex(t_lexer **lst, int nb)
{
	t_lexer	*tmp;

	if (!lst)
		return ;
	while (*lst && nb--)
	{
		tmp = (*lst)->next;
		*lst = tmp;
	}
	if (*lst)
		(*lst)->prev = NULL;
}
