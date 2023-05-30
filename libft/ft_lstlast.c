/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:10:33 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:41:29 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstlast
** ------------------------------
** Description :
** Cette fonction prend en argument un pointeur sur le premier élément d'une
** liste chaînée et renvoie un pointeur sur le dernier élément de cette liste.
**
** Paramètres :
** - lst : le pointeur sur le premier élément de la liste chaînée.
**
** Retourne :
** - un pointeur sur le dernier élément de la liste chaînée.
** - NULL si la liste est vide (lst == NULL).
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
