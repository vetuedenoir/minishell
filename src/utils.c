/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:54:21 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/02 17:41:30 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell"

t_lexer	*ft_lstnewl(char *str)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void    ft_add_back_lexer(t_lexer **lst, t_lexer *new)
{
    t_lexer    *temp;

    if (!lst || !new)
        return ;
    temp = *lst;
    if (lst && (*lst))
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
    else
    *lst = new;
}

void	cleartb(char **tb)
{
	int	i;

	i = 0;
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
		free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
}

