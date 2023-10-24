/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:46:10 by kscordel          #+#    #+#             */
/*   Updated: 2023/10/24 16:24:15 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*memory_add(void *pointeur, t_tool *data)
{
	t_list	*node;
	t_list	*tmp;
	t_list	*first;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = pointeur;
	node->next = NULL;
	if (data->garbage_collector == NULL)
		data->garbage_collector = node;
	else
	{
		first = data->garbage_collector;
		tmp = data->garbage_collector;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		data->garbage_collector = first;
	}
	return (pointeur);
}

void	*ft_malloc(size_t size, t_tool *data)
{
	void	*pointeur;

	pointeur = malloc(size);
	if (!pointeur)
		return (NULL);
	if (!memory_add(pointeur, data))
		return (free(pointeur), NULL);
	return (pointeur);
}

void	free_garbage(t_tool *data)
{
	t_list	*tmp;
	t_list	*node;

	node = data->garbage_collector;
	while (node)
	{
		tmp = node->next;
		if (node->content)
			free(node->content);
		free(node);
		node = tmp;
	}
	data->garbage_collector = NULL;
}
