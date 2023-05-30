/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:11:45 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:50:41 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstsize
** ------------------------------
** Description :
** Cette fonction compte le nombre d'éléments dans une liste chaînée.
**
** Paramètres :
** - lst : le pointeur vers le premier élément de la liste chaînée.
**
** Retourne :
** Le nombre d'éléments dans la liste chaînée.
** 0 si la liste est vide ou NULL.
*/

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
