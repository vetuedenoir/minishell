/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:20:56 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:29:56 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_memmove
** -------------------------------
** Description :
** Cette fonction copie les n premiers octets de la zone mémoire
** src vers la zone mémoire dest, en prenant en compte le chevauchement possible
** des deux zones.
** La copie est effectuée de manière non destructive.
**
** Paramètres :
** - dest : un pointeur vers la zone mémoire destination.
** - src : un pointeur vers la zone mémoire source.
** - n : le nombre d'octets à copier.
**
** Retourne :
** - Un pointeur vers la zone mémoire destination.
**
** Notes :
** - Cette fonction prend en compte le cas où les zones mémoire
**   source et destination se chevauchent partiellement ou totalement.
** - Dans le cas où les zones mémoire se chevauchent et que la zone destination
**   est avant la zone source, la copie est effectuée en utilisant
**   la fonction ft_memcpy pour éviter les erreurs de chevauchement.
** - Cette fonction est similaire à la fonction memcpy,
**   mais elle garantit que la copie est effectuée de manière non destructive
**   en prenant en compte les chevauchements possibles.
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*bufd;
	const char	*bufs;

	bufd = dest;
	bufs = src;
	if (bufd <= bufs)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n--)
			bufd[n] = bufs[n];
	}
	return (dest);
}
