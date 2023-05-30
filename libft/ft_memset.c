/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:34:27 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:32:18 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_memset
** ------------------------------
** Description :
** Cette fonction remplit les n premiers octets de la zone mémoire pointée par s
** avec l'octet c (interprété comme un unsigned char).
**
** Paramètres :
** - s : un pointeur vers la zone mémoire à remplir.
** - c : la valeur à copier dans la zone mémoire.
** - n : le nombre d'octets à remplir.
**
** Retourne :
** - Un pointeur vers la zone mémoire s.
**
** Notes :
** - Cette fonction remplit la zone mémoire s avec la valeur c en utilisant un
** type char pour accéder à chaque octet individuellement.
** - L'octet c est automatiquement converti en unsigned char avant d'être copié
** dans la zone mémoire.
*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*buffer;

	buffer = s;
	i = 0;
	while (i < n)
	{
		buffer[i] = c;
		i++;
	}
	return (s);
}
