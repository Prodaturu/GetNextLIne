/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:59:25 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/27 01:45:34 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}				t_gnl_node;

typedef struct s_queue
{
	t_gnl_node	*front;
	t_gnl_node	*rear;
}			t_queue;

char		*get_next_line(int fd);
t_queue		*ft_init_queue(void);
void		ft_enqueue(t_queue *queue, char *c);
char		*ft_unqueue(t_queue *queue);
int			ft_newline_exists(t_queue *queue);
void		ft_free_queue(t_queue *queue);

#endif
