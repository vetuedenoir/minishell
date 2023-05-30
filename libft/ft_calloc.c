/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:27:39 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 18:55:59 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_calloc
** ------------------------------
** Description :
**  Cette fonction alloue de la mémoire pour un tableau de nmemb éléments,
**  chacun de taille size octets, et renvoie un pointeur vers la zone mémoire
**  allouée. La zone mémoire est initialisée avec des zéros.
**
** Paramètres :
**  - nmemb : nombre d'éléments dans le tableau à allouer.
**  - size : taille en octets de chaque élément dans le tableau à allouer.
**
** Retourne :
**  - Un pointeur vers la zone mémoire allouée, ou NULL si l'allocation échoue.
**
** Remarques :
**  - La zone mémoire allouée par cette fonction doit être libérée
**    avec la fonction free().
**  - Le comportement est indéfini si nmemb ou size valent zéro,
**    ou si l'allocation échoue.
**  - Le comportement est indéfini si le produit nmemb * size
**    dépasse la capacité de size_t.
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}
