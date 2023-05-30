/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:41:19 by kscordel          #+#    #+#             */
/*   Updated: 2022/12/02 12:48:38 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Nom de la fonction : ft_strjoin
** ------------------------------
** Description :
** Cette fonction alloue et retourne une nouvelle chaîne de caractères
** résultant de la concaténation de s1 et s2. La nouvelle chaîne est
** terminée par un caractère nul.
**
** Paramètres :
** - s1 : la chaîne de caractères à placer en premier dans la concaténation.
** - s2 : la chaîne de caractères à placer en deuxième dans la concaténation.
**
** Retourne :
** - La nouvelle chaîne de caractères obtenue à partir de la concaténation
** de s1 et s2, ou NULL si l'allocation de mémoire a échoué.
**
** Notes :
** - Si s1 ou s2 est NULL, la fonction renvoie NULL.
** - La mémoire allouée par cette fonction doit être libérée par l'appelant
** à l'aide de la fonction free.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		t;
	int		i;
	int		p;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	p = 0;
	t = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (t + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[p])
	{
		str[i + p] = s2[p];
		p++;
	}
	str[i + p] = '\0';
	return (str);
}
