/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:20:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/12/18 10:19:20 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

t_sprite		fill_spriteinfo(void)
{
	t_sprite	spr;

	ft_bzero(&spr, sizeof(t_sprite));
	spr.gfx = 19;
	spr.dead = 0;
	spr.hp = 1;
	spr.pos.z = 15 / 10;
	spr.pos.y = 125 / 10;
	spr.pos.x = 129 / 10;
	spr.respawn = 1800;
	spr.size = 1;
	return (spr);
}

t_sprite		fill_objectinfo(void)
{
	t_sprite	spr;

	ft_bzero(&spr, sizeof(t_sprite));
	spr.gfx = 34;
	spr.dead = 0;
	spr.hp = 0;
	spr.pos.z = 19 / 10;
	spr.pos.y = 30 / 10;
	spr.pos.x = 215 / 10;
	spr.respawn = 0;
	spr.size = 1;
	return (spr);
}

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
	return (spr);
}

void			comp_sprite(t_doom *dm, int i, int fd)
{
	char		*gnl;
	int			sprdone;
	int			objdone;

	sprdone = 0;
	objdone = 0;
	if (dm->datareadtype == SPRITE)
		read_spriteinfo(dm, -1, fd, &sprdone);
	if (dm->datareadtype == OBJECT)
		read_objectinfo(dm, -1, fd, &objdone);
	else if (get_next_line(fd, &gnl) == 1)
	{
		datatype_check(dm, &gnl);
		free(gnl);
		if (dm->datareadtype == OBJECT)
			read_objectinfo(dm, -1, fd, &objdone);
	}
	if (!(sprdone))
		while (++i < SPR)
			dm->spr[i] = fill_spriteinfo();
	i = -1;
	if (!(objdone))
		while (++i < OBJ)
			dm->obj[i] = fill_objectinfo();
}
