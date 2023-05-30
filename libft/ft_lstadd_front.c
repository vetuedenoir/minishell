/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:03:49 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:31:00 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstadd_front
** ------------------------------------
** Description :
**  Cette fonction ajoute l'élément 'new' au début de la liste 'lst'.
**
** Paramètres :
**  - lst : l'adresse du pointeur vers le premier élément de la liste.
**  - new : le pointeur vers le nouvel élément à ajouter à la liste.
**
** Retourne : void
**
** Remarques :
**  - Si 'lst' est NULL ou 'new' est NULL, la fonction ne fait rien.
**  - Le champ 'next' de l'élément 'new' est initialisé avec l'adresse du
**    premier élément de la liste 'lst', puis 'lst' est mis à jour pour
**    pointer sur 'new'.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
