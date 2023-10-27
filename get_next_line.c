/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:59:29 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/27 01:48:17 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	needed_size;
	void	*ptr;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	needed_size = count * size;
	ptr = malloc(needed_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, needed_size);
	return (ptr);
}

static char	*ft_extract_line(t_queue *queue)
{
	char	*temp;
	int		i;
	int		newline_found;
	char	*line;
	char	*rtrn;

	newline_found = 0;
	line = (char *)malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	i = 0;
	temp = ft_unqueue(queue);
	while (temp != NULL && i < BUFFER_SIZE && newline_found == 0)
	{
		line[i] = *temp;
		free(temp);
		if (line[i] == '\n')
			newline_found = 1;
		else
			i++;
	}
	line[i] = '\0';
	rtrn = line;
	free(line);
	return (rtrn);
}

static void	read_and_enqueue(int fd, t_queue *remainder, int *bytes_read)
{
	char	*c;
	int		index;
	char	*buffer;

	index = 0;
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (index < *bytes_read)
	{
		c = (char *)malloc(sizeof(char));
		*c = buffer[index++];
		ft_enqueue(remainder, c);
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static t_queue	*remainder;
	int				bytes_read;
	char			*buffer;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (fd < 0 || !(buffer))
		return (NULL);
	if (!remainder)
		remainder = ft_init_queue();
	read_and_enqueue(fd, remainder, &bytes_read);
	while (bytes_read > 0)
	{
		if (ft_newline_exists(remainder))
			return (ft_extract_line(remainder));
		read_and_enqueue(fd, remainder, &bytes_read);
	}
	if (bytes_read <= 0)
	{
		ft_free_queue(remainder);
		remainder = NULL;
	}
	return (NULL);
}

// int main() {
// 	int fd;
// 	char *str;

// 	fd = open("test", O_RDONLY);
// 	printf("fd = %d\n", fd);
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("s = %s\n", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	printf("s = %s\n", str);
// 	free(str);
// 	return (0);
// }

// memalloc for buffer and check for errors
// read file, update remainder until newline
// check for eof
//
// char	*get_next_line(int fd)
// {
// 	static char	*remainder;
// 	char		*buffer;
// 	int			bytes_read;
// 	char		*temp;
// 	int			newline_check;
// 	int			n1_index;

// 	if (fd < 0)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	while (bytes_read > 0 && !newline_check)
// 	{
// 		buffer[bytes_read] = '\0';
// 		if (!remainder)
// 			remainder = ft_strdup(buffer);
// 		else
// 		{
// 			temp = ft_strjoin(remainder, buffer);
// 			ft_strdelete(&remainder);
// 			remainder = temp;
// 		}
// 		if (find_newline(remainder) >= 0)
// 			newline_check = 1;
// 	}
// 	if ((bytes_read < 0) || (bytes_read == 0 && !remainder))
// 		return (NULL);
// 	n1_index = find_newline(remainder);
// }
