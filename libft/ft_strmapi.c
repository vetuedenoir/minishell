/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:49:17 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 15:14:56 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strmapi
** -------------------------------
** Description :
** Cette fonction applique la fonction f sur chaque caractère de la chaîne s
** pour créer une nouvelle chaîne de caractères résultante.
** La chaîne résultante est allouée dynamiquement et
** doit être libérée par l'appelant.
**
** Paramètres :
** - s : la chaîne de caractères à traiter.
** - f : la fonction à appliquer à chaque caractère de la chaîne s.
**
** Retourne :
** - La nouvelle chaîne de caractères résultante ou NULL
**   si l'allocation dynamique de mémoire échoue.
**
** Notes :
** - La fonction f doit avoir la signature suivante :
**   char (*f)(unsigned int, char).
** - La fonction crée une nouvelle chaîne de caractères allouée dynamiquement et
**   doit être libérée par l'appelant.
** - Si la chaîne s est NULL, la fonction retourne NULL.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				t;
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	i = 0;
	t = ft_strlen(s);
	str = malloc(sizeof(char) * (t + 1));
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}	
