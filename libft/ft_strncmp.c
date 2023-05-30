/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:39:52 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 15:19:58 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strncmp
** -------------------------------
** Description :
** Cette fonction compare les n premiers caractères de deux chaînes de caractères
** s1 et s2. Elle retourne un entier négatif, nul ou positif si s1 est
** respectivement inférieure, égale ou supérieure à s2.
**
** Paramètres :
** - s1 : une chaîne de caractères à comparer.
** - s2 : une chaîne de caractères à comparer.
** - n : le nombre de caractères à comparer.
**
** Retourne :
** - Un entier négatif si s1 est inférieure à s2.
** - Zéro si s1 est égale à s2.
** - Un entier positif si s1 est supérieure à s2.
**
** Notes :
** - Si les deux chaînes sont égales jusqu'au caractère nul mais que la taille n
** a été atteinte, alors la fonction retourne zéro.
** - Les caractères sont comparés selon leur code ASCII.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && --n && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
