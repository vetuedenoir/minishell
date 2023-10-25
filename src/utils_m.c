/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:09:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/25 14:07:22 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc_g(size_t nmemb, size_t size, t_tool *data)
{
	void	*mem;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = ft_malloc(nmemb * size, data);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}

char	*ft_strdup_g(const char *s, t_tool *data)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_malloc(sizeof(char) * (ft_strlen(s) + 1), data);
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
