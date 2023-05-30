/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:06:26 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:40:44 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstiter
** -------------------------------
** Description :
**  Cette fonction applique la fonction 'f' à chaque élément de la liste 'lst'.
**
** Paramètres :
**  - lst : la liste à parcourir.
**  - f : la fonction à appliquer à chaque élément de la liste.
**
** Retourne :
**  Rien.
**
** Remarques :
**  - Cette fonction permet d'appliquer une opération à chaque élément d'une
**    liste chaînée sans avoir à écrire une boucle à chaque fois.
**  - La fonction 'f' doit impérativement modifier le contenu
**    des éléments de la liste passé en paramètre,
**    sinon cela n'aura aucun effet sur la liste originale.
*/

void	ft_lstiter(t_list *lst, void (*f) (void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
