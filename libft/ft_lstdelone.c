/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:05:02 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:36:34 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstdelone
** -------------------------------
** Description :
**  Cette fonction supprime un élément d'une liste chaînée en libérant la mémoire
**  allouée pour son contenu à l'aide d'une fonction de suppression fournie par
**  l'utilisateur.
**
** Paramètres :
**  - lst : l'élément de la liste à supprimer.
**  - del : un pointeur vers la fonction de suppression à utiliser pour libérer
**          la mémoire allouée pour le contenu de l'élément.
**
** Retourne :
**  - Rien.
**
** Remarques :
**  - Si l'élément est le dernier de la liste, le pointeur sur la liste doit être
**    mis à NULL.
**  - Si l'élément est NULL, la fonction ne fait rien.
*/

void	ft_lstdelone(t_list *lst, void (*del) (void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}
