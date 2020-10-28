/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:20:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/28 16:19:36 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

t_sprite		set_sprite(char **arr, int len)
{
	t_sprite	spr;

	ft_bzero(&spr, sizeof(t_sprite));
	len = templen(arr);
	if (len < 7)
	{
		spr.gfx = 16;
		return (spr);
	}
	spr.gfx = ft_atoi(arr[0]);
	spr.dead = ft_atoi(arr[1]);
	spr.hp = ft_atoi(arr[2]);
	spr.pos.z = ft_atoi(arr[3]) / 10.0;
	spr.pos.y = ft_atoi(arr[4]) / 10.0;
	spr.pos.x = ft_atoi(arr[5]) / 10.0;
	spr.respawn = ft_atoi(arr[6]);
	spr.size = 1;
	if (spr.gfx == 35)
		spr.size = 2;
	free_memory(arr);
	return (spr);
}

void			comp_sprite(t_doom *dm, int i, int fd)
{
	char		*gnl;
	char		**arr;

	while (++i < SPR)
	{
		dm->spr[i].gfx = 16;
		if (get_next_line(fd, &gnl) == 1)
		{
			arr = ft_strsplit(gnl, ',');
			dm->spr[i] = set_sprite(arr, 0);
			free(gnl);
		}
	}
	if (get_next_line(fd, &gnl) == 1)
		free(gnl);
	i = -1;
	while (++i < OBJ)
	{
		if (get_next_line(fd, &gnl) == 1)
		{
			arr = ft_strsplit(gnl, ',');
			dm->obj[i] = set_sprite(arr, 0);
			free(gnl);
		}
	}
}
