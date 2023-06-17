/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:54:21 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/17 16:21:13 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lstnewl(char *str)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void    ft_add_back_lexer(t_lexer **lst, t_lexer *new)
{
    t_lexer    *temp;

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

void	ft_lstclearl(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str != NULL)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
}

void	clear_lex(t_lexer **lst, int nb)
{
	t_lexer *tmp;
	if (!lst)
		return ;
	while (*lst && nb--)
	{
		tmp = (*lst)->next;
		if ((*lst)->str != NULL)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
}


