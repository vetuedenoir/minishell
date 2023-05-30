/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:03:16 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:29:48 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstadd_back
** -----------------------------------
** Description :
** Cette fonction ajoute un élément à la fin d'une liste chaînée.
** Si la liste est vide, elle devient le nouvel élément de tête.
**
** Paramètres :
** - lst : l'adresse de pointeur de la liste chaînée.
** - new : le nouvel élément à ajouter.
**
** Retourne :
** Rien.
**
** Remarques :
** - Cette fonction ne crée pas de nouvelle liste chaînée.
** - Cette fonction est utile pour ajouter un nouvel élément à une liste chaînée
** dont la fin n'est pas connue à l'avance.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
