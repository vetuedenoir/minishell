/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:08:08 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 18:57:18 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_isalnum
** ------------------------------
** Description :
**  Cette fonction vérifie si le caractère passé en argument est un caractère
**  alphanumérique. Les caractères alphanumériques incluent les chiffres
**  (0 à 9) et les lettres (a à z, A à Z).
**
** Paramètres :
**  - c : le caractère à tester.
**
** Retourne :
**  - 1 si le caractère est alphanumérique.
**  - 0 sinon.
*/

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}
