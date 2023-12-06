/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:04:25 by mbest             #+#    #+#             */
/*   Updated: 2023/12/04 16:07:24 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len_stash(t_list **stash, int fd)
{
	int		i;
	int		count;
	t_list	*current;

	count = 0;
	current = *stash;
	while (current)
	{
		if (current->fd == fd)
		{
			i = 0;
			while (current->content && current->content[i])
			{
				if (current->content[i] == '\n')
					return (count + 1);
				count++;
				i++;
			}
		}
		current = current->next;
	}
	return (count);
}

void	addback_stash(t_list **stash, t_list *newnode)
{
	t_list	*last;

	if (newnode == NULL)
		return ;
	if (*stash == NULL)
		*stash = newnode;
	else
	{
		last = *stash;
		while (last->next)
			last = last->next;
		last->next = newnode;
	}
}

t_list	*create_elem(int fd, char *buffer, int bytes_read)
{
	int		i;
	t_list	*new;

	i = 0;
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (new->content == NULL)
	{
		free(new);
		return (NULL);
	}
	while (buffer[i] && i < bytes_read)
	{
		new->content[i] = buffer[i];
		i++;
	}
	new->content[i] = '\0';
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void	remove_node(t_list **stash, t_list **current, t_list *previous)
{
	if (previous)
	{
		previous->next = (*current)->next;
		free((*current)->content);
		free(*current);
		*current = previous->next;
	}
	else
	{
		*stash = (*current)->next;
		free((*current)->content);
		free(*current);
		*current = *stash;
	}
}

void	free_stash(t_list **stash, int fd)
{
	t_list	*current;
	t_list	*previous;

	current = *stash;
	previous = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			remove_node(stash, &current, previous);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
