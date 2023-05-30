/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:10:52 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:49:33 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_lstnew
** -------------------------------
** Description :
**  Cette fonction crée un nouvel élément de liste et l'initialise avec le
**  contenu passé en argument.
**
** Paramètres :
**  - content : le contenu à stocker dans le nouvel élément.
**
** Retourne :
**  - Un pointeur sur le nouvel élément de liste créé, ou NULL en cas d'erreur.
**
** Notes :
**  - Cette fonction alloue de la mémoire pour le nouvel élément et initialise
**    son champ "next" à NULL.
**  - Le champ "content" de l'élément est initialisé avec la valeur de l'argument
**    "content". Ce champ peut contenir n'importe quel type de données grâce à
**    l'utilisation d'un pointeur void*.
**  - Il est de la responsabilité de l'appelant de libérer la mémoire allouée
**    pour le nouvel élément de liste lorsqu'il n'est plus utilisé.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
