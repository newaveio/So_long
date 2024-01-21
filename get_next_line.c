/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:49:30 by mbest             #+#    #+#             */
/*   Updated: 2024/01/21 19:55:08 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_extract_line(t_list_gnl **stash, char **line, int fd)
{
	int		i;
	int		j;
	int		len;
	t_list_gnl	*ptr;

	i = 0;
	len = ft_len_stash(stash, fd);
	ptr = *stash;
	while (ptr)
	{
		if (ptr->fd == fd)
		{
			j = -1;
			while (ptr->content && ptr->content[++j] && i < len)
				(*line)[i++] = ptr->content[j];
		}
		ptr = ptr->next;
	}
	(*line)[i] = '\0';
}

void	clean_and_store_remaining(t_list_gnl **stash, int fd, int index)
{
	t_list_gnl	*last;
	t_list_gnl	*clean_node;
	int		j;

	clean_node = (t_list_gnl *)malloc(sizeof(t_list_gnl));
	if (clean_node == NULL)
		return ;
	clean_node->next = NULL;
	clean_node->fd = fd;
	last = *stash;
	while (last && last->next)
		last = last->next;
	while (last && last->content[index] && last->content[index] != '\n')
		index++;
	if (last && last->content[index] == '\n')
		index++;
	clean_node->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE - index
				+ 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last && last->content[index])
		clean_node->content[j++] = last->content[index++];
	clean_node->content[j] = '\0';
	(free_stash(stash, fd), addback_stash(stash, clean_node));
}

int	found_newline(t_list_gnl *stash)
{
	int		i;
	t_list_gnl	*current;

	if (stash == NULL)
		return (0);
	current = stash;
	while (current && current->next)
		current = current->next;
	i = 0;
	while (current->content && current->content[i])
	{
		if (current->content[i++] == '\n')
			return (1);
	}
	return (0);
}

void	read_and_stash(int fd, t_list_gnl **stash)
{
	int		bytes_read;
	t_list_gnl	*new;
	char	*buffer;

	bytes_read = 1;
	while ((!found_newline(*stash) && bytes_read != 0) || !(*stash))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			free_stash(stash, fd);
		bytes_read = (int)read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			(free_stash(stash, fd), free(buffer));
			return ;
		}
		buffer[bytes_read] = '\0';
		new = create_elem(fd, buffer, bytes_read);
		(addback_stash(stash, new), free(buffer));
	}
}

char	*get_next_line(int fd)
{
	int				index;
	int				len;
	char			*line;
	static t_list_gnl	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (free_stash(&stash, fd), NULL);
	read_and_stash(fd, &stash);
	len = ft_len_stash(&stash, fd);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (free_stash(&stash, fd), NULL);
	if (stash == NULL)
		return (free(line), NULL);
	index = 0;
	(ft_extract_line(&stash, &line, fd), clean_and_store_remaining(&stash, fd,
			index));
	if (line && line[0] == '\0')
		return (free_stash(&stash, fd), free(line), NULL);
	return (line);
}

// int main(void)
// {
//     int fd1;
//     int end_of_file1;
//     char *line;

//     end_of_file1 = 0;
//     fd1 = open("example.txt", O_RDONLY);
//     if (fd1 < 0)
//     {
//         perror("Error opening file 1");
//         return (1);
//     }
//     while(end_of_file1 == 0)
//     {
//         line = get_next_line(fd1);
//         if(line == NULL)
//             end_of_file1 = 1;
//         else
//         {
//             printf("[File 1]: %s\n", line);
//             free(line);
//         }
//     }
//     close(fd1);
//     return (0);
// }