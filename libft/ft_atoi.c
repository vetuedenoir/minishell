/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:33:37 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 18:47:49 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Fonction : ft_atoi
** -------------------
** Convertit une chaîne de caractères en un entier signé.
** La fonction ignore les espaces, les tabulations, les sauts de ligne et
** les retours chariots en début de chaîne.
** Elle lit ensuite un signe optionnel (+ ou -)
** suivi d'un ou plusieurs chiffres décimaux, 
** convertit la chaîne en un entier et le retourne.
**
** Paramètres :
**  - nptr : pointeur vers la chaîne de caractères à convertir en entier.
**
** Retourne :
**  - la valeur entière convertie.
**
** Remarques :
**  - si la chaîne ne contient pas de chiffres décimaux valides,
** la fonction retourne 0.
**  - si la chaîne dépasse la capacité d'un entier signé,
** le comportement est indéfini.
*/

int	ft_atoi(const char *nptr)
{
	int		i;
	int		signe;
	long	nbr;

	i = 0;
	signe = 1;
	nbr = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr * signe);
}
