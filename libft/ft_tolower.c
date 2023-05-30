/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:42:08 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 16:46:37 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_tolower
** ------------------------------
** Description :
** Cette fonction convertit le caractère c en minuscule s'il s'agit d'une lettre
** majuscule. Si c ne correspond pas à une lettre majuscule, la fonction renvoie
** simplement c inchangé.
**
** Paramètres :
** - c : le caractère à convertir.
**
** Retourne :
** - La valeur entière correspondant au caractère c en minuscule, ou c inchangé
** s'il ne s'agit pas d'une lettre majuscule.
**
** Notes :
** - Aucune vérification n'est effectuée sur le paramètre c. Il doit être
** représentable sur un octet.
*/

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}
