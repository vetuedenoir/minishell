/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:54:42 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/01 19:05:16 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_isalpha
** -------------------------------
** Description :
**  Cette fonction vérifie si le caractère passé en argument est une lettre
**  alphabétique. Les lettres alphabétiques incluent les caractères en
**  minuscules (a à z) et en majuscules (A à Z).
**
** Paramètres :
**  - c : le caractère à tester.
**
** Retourne :
**  - 1 si le caractère est une lettre alphabétique.
**  - 0 sinon.
*/

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}
