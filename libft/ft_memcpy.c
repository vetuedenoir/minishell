/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:41:51 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:25:31 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_memcpy
** -----------------------------
** Description :
** Cette fonction copie les 'n' premiers octets du bloc de mémoire source
** 'src' vers le bloc de mémoire de destination 'dest'. Les blocs ne doivent
** pas se chevaucher.
**
** Paramètres :
** - dest : le pointeur vers le bloc de mémoire de destination.
** - src : le pointeur vers le bloc de mémoire source.
** - n : le nombre d'octets à copier.
**
** Retourne :
** - Un pointeur vers le bloc de mémoire de destination 'dest'.
**
** Notes :
** - Si 'n' vaut zéro ou si les pointeurs 'dest' et 'src' sont égaux, cette
** fonction ne fait rien et retourne 'dest'.
** - Les blocs de mémoire source et de destination doivent être alloués et
** avoir une taille suffisante pour éviter les erreurs de segmentation.
** - Cette fonction ne prend pas en charge le chevauchement des blocs de
** mémoire source et de destination. Dans ce cas, il est recommandé
** d'utiliser la fonction ft_memmove().
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*bufd;
	const char	*bufs;

	bufd = (char *)dest;
	bufs = (char *)src;
	i = 0;
	if (!n || dest == src)
		return (dest);
	while (i < n)
	{
		bufd[i] = bufs[i];
		i++;
	}
	return (dest);
}
