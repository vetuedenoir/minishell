/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:07:41 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:45:25 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstmap
** ------------------------------
** Description :
**  Cette fonction crée une nouvelle liste résultante de l'application de la
**  fonction `f` à chaque élément de la liste `lst`. La fonction `del` est
**  appelée pour supprimer le contenu des éléments de la nouvelle liste en cas
**  d'erreur. 
**
** Paramètres :
**  - lst : le début de la liste à parcourir.
**  - f : la fonction à appliquer à chaque élément.
**  - del : la fonction à appeler pour supprimer le contenu des éléments en cas
**    d'erreur.
**
** Retourne :
**  - Un pointeur vers la première élément de la nouvelle liste.
**  - NULL en cas d'erreur.
**
** Remarques :
**  - Il est de la responsabilité de l'appelant de supprimer la liste
**    résultante.
**  - Si la fonction `f` modifie le contenu de la liste originale, la nouvelle
**    liste pourrait contenir des données incohérentes.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del) (void*))
{
	t_list	*newlist;
	t_list	*nelem;

	newlist = NULL;
	while (lst)
	{
		nelem = ft_lstnew(f(lst->content));
		if (!nelem)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, nelem);
		lst = lst->next;
	}
	return (newlist);
}
