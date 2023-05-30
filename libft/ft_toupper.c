/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:37:00 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 16:47:54 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_toupper
** ------------------------------
** Description :
** Cette fonction convertit un caractère en majuscule s'il est déjà en minuscule.
** Si le caractère n'est pas une lettre minuscule, il est renvoyé tel quel.
**
** Paramètres :
** - c : le caractère à convertir.
**
** Retourne :
** - Le caractère converti en majuscule s'il était en minuscule,
** ou le même caractère s'il n'était pas une lettre minuscule.
**
** Notes :
** - Cette fonction ne modifie pas la chaîne de caractères d'origine,
** elle renvoie simplement une copie du caractère modifié.
*/

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
