/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:15:09 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/14 18:39:39 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back_cmds(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if (!new)
		return ;
	tmp = *lst;
	if (lst && (*lst))
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*lst = new;

}


