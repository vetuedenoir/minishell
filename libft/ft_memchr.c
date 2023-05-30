/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:31:20 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 20:07:29 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_memchr
** ------------------------------
** Description :
** Cette fonction recherche la première occurrence d'un octet spécifique c
** dans les n premiers octets de la zone mémoire pointée par s.
**
** Paramètres :
** - s : le pointeur vers la zone mémoire à examiner.
** - c : l'octet à chercher.
** - n : le nombre d'octets à examiner.
**
** Retourne :
** - Un pointeur vers l'octet correspondant trouvé.
** - NULL si l'octet spécifié n'a pas été trouvé dans la zone mémoire examinée.
**
** Remarques :
** - La fonction ft_memchr() ne modifie pas la zone mémoire.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*buf;

	i = 0;
	buf = s;
	while (i < n)
	{
		if (buf[i] == (unsigned char) c)
			return ((void *) &buf[i]);
		i++;
	}
	return (NULL);
}
