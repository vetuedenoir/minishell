/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:48:39 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 11:23:17 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_memcmp
** ------------------------------
** Description :
** Cette fonction compare les n premiers octets de s1 et s2. Elle renvoie un
** entier inférieur, égal ou supérieur à zéro si les n premiers octets de s1
** sont respectivement inférieurs, égaux ou supérieurs aux n premiers octets
** de s2.
**
** Paramètres :
** - s1 : un pointeur vers le premier bloc de mémoire à comparer.
** - s2 : un pointeur vers le deuxième bloc de mémoire à comparer.
** - n : le nombre d'octets à comparer.
**
** Retourne :
** - Un entier inférieur, égal ou supérieur à zéro si les n premiers octets
** de s1 sont respectivement inférieurs, égaux ou supérieurs aux n premiers
** octets de s2.
**
** Remarques :
** - Cette fonction ne modifie pas les blocs de mémoire pointés par s1 et s2.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*buf1;
	const unsigned char	*buf2;

	buf1 = s1;
	buf2 = s2;
	if (n == 0)
		return (0);
	i = 0;
	while (buf1[i] == buf2[i] && --n)
		i++;
	return (buf1[i] - buf2[i]);
}
