/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:23:17 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 14:41:30 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strlen
** -----------------------------
** Description :
** Cette fonction calcule la longueur d'une chaîne de caractères, en parcourant
** la chaîne jusqu'à rencontrer le caractère nul ('\0') qui marque la fin de
** la chaîne.
**
** Paramètres :
** - str : un pointeur vers la chaîne de caractères dont on veut calculer la
** longueur.
**
** Retourne :
** - La longueur de la chaîne de caractères passée en paramètre.
**
** Notes :
** - Cette fonction ne compte pas le caractère nul ('\0') dans le calcul de la
** longueur de la chaîne.
*/

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
