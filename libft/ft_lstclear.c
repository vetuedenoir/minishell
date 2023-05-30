/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:04:21 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:34:49 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstclear
** -------------------------------
** Description :
** Cette fonction supprime tous les éléments de la liste passée en argument
** en utilisant la fonction de suppression 'del' passée en argument
** pour libérer la mémoire allouée aux données contenues dans chaque élément.
** Enfin, elle met à jour le pointeur de début de liste sur NULL.
**
** Paramètres :
** - lst : l'adresse du pointeur de début de liste.
** - del : le pointeur de la fonction de suppression
**         à utiliser pour chaque élément.
**
** Retourne : rien.
**
** Remarques :
** - Si 'lst' est NULL, cette fonction ne fait rien.
** - 'del' ne doit pas être NULL.
** - Cette fonction libère la mémoire allouée pour chaque élément,
**   ainsi que la mémoire allouée pour le pointeur de l'élément.
** - Après l'appel de cette fonction,
**   le pointeur de début de liste est mis à NULL.
*/

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
