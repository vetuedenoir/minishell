/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:40:19 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:21:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Fonction : ft_itoa
** -------------------
** Convertit un entier en une chaîne de caractères.
** La fonction alloue de la mémoire pour la chaîne de caractères résultante.
** La chaîne de caractères est composée des chiffres décimaux de l'entier,
** suivi d'un caractère nul de fin de chaîne.
** Si l'entier est négatif, le signe "-" est ajouté au début de la chaîne.
**
** Paramètres :
** - n : l'entier à convertir en chaîne de caractères.
**
** Retourne :
** - la chaîne de caractères représentant l'entier,
**   ou NULL en cas d'erreur d'allocation.
**
** Remarques :
** - La chaîne de caractères doit être libérée par l'appelant
**   à l'aide de la fonction free().
** - Le comportement est indéfini si l'entier dépasse la capacité d'un long.
*/

static void	ft_signe(long *nb, int *signe, int *t)
{
	if (*nb < 0)
	{
		*signe = -1;
		*t = *t + 1;
		*nb = *nb * -1;
	}
	else
		*signe = 1;
}

/*
** static void ft_signe(long *nb, int *signe, int *t)
** Cette fonction détermine le signe de l'entier en entrée,
** met à jour la variable signe et incrémente la variable t
** si le nombre est négatif.
** nb est un pointeur sur un entier long contenant la valeur à analyser,
** signe est un pointeur sur un entier qui sera mis à jour
** en fonction du signe de nb et t est un pointeur sur un entier
** qui sera incrémenté si nb est négatif.
*/

static void	lennb(long nb, int *t)
{
	if (nb == 0)
		*t = *t + 1;
	else
	{
		while (nb != 0)
		{
			nb /= 10;
			*t = *t + 1;
		}
	}
}

/*
** static void lennb(long nb, int *t)
** Cette fonction calcule le nombre de chiffres dans l'entier en entrée,
** stocké dans nb, et met à jour la variable t en conséquence.
** Si nb est égal à zéro, t est incrémenté de 1.
** nb est un entier long contenant la valeur à analyser,
** et t est un pointeur sur un entier qui sera incrémenté
** en fonction du nombre de chiffres dans nb.
*/

char	*ft_itoa(int n)
{
	int		t;
	int		signe;
	long	nb;
	char	*str;

	t = 0;
	nb = n;
	ft_signe(&nb, &signe, &t);
	lennb(nb, &t);
	str = malloc(sizeof(char) * (t + 1));
	if (str == NULL)
		return (NULL);
	str[t] = '\0';
	while (t > 0)
	{
		t--;
		str[t] = nb % 10 + 48;
		nb /= 10;
	}
	if (signe == -1)
		str[t] = '-';
	return (str);
}
