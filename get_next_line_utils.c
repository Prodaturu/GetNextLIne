/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:59:34 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/27 01:43:22 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_newline_exists(t_queue	*queue)
{
	t_gnl_node	*current;

	current = NULL;
	if (queue && queue->front)
		current = queue->front;
	while (current)
	{
		if (*(current->data) == '\n')
			return (1);
		current = current->next;
	}
	return (0);
}

void	ft_free_queue(t_queue *queue)
{
	t_gnl_node	*temp;

	while (queue->front)
	{
		temp = queue->front;
		queue->front = queue->front->next;
		free(temp->data);
		free(temp);
	}
	free(queue);
}

t_queue	*ft_init_queue(void)
{
	t_queue	*new_queue;

	new_queue = (t_queue *)malloc(sizeof(t_queue));
	if (!new_queue)
		return (NULL);
	new_queue->front = NULL;
	new_queue->rear = NULL;
	return (new_queue);
}

void	ft_enqueue(t_queue *queue, char *data)
{
	t_gnl_node	*new_node;

	new_node = (t_gnl_node *)malloc(sizeof(t_gnl_node));
	if (!new_node)
		return ;
	new_node->data = data;
	new_node->next = NULL;
	if (queue->rear == NULL)
	{
		queue->front = new_node;
		queue->rear = new_node;
		return ;
	}
	else
	{
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
	return ;
}

char	*ft_unqueue(t_queue *queue)
{
	t_gnl_node	*temp;
	char		*c;

	temp = queue->front;
	if (!(queue->front))
		return (NULL);
	c = temp->data;
	queue->front = queue->front->next;
	free(temp);
	return (c);
}

		// printf("c = %c\n", *(current->data));