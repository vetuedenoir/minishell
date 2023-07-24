/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:46:10 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/24 16:43:15 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*memory_add(void *pointeur)
{
	t_list	*node;
	t_list	*tmp;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = pointeur;
	node->next = NULL;
	if (g_garbage_collector == NULL)
		g_garbage_collector = node;
	else
	{
		tmp = g_garbage_collector;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (pointeur);
}

void	*ft_malloc(size_t size)
{
	void	*pointeur;

	pointeur = malloc(size);
	if (!pointeur)
		return (NULL);
	if (!memory_add(pointeur))
		return (free(pointeur), NULL);
	return (pointeur);
}

void	free_garbage(void)
{
	t_list	*tmp;
	t_list	*node;

	node = g_garbage_collector;
	while (node)
	{
		tmp = node->next;
		if (node->content)
			free(node->content);
		free(node);
		node = tmp;
	}
	g_garbage_collector = NULL;
}
