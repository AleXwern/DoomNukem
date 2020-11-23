/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:20:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/11/23 15:07:11 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

// if all the info hasnt been filled in objects or sprites, add a condition
// to fill the rest

//chrashes with the gnl returning -1 so if no lines are in map :(


t_sprite		fill_spriteinfo(void)
{
	t_sprite	spr;

	ft_bzero(&spr, sizeof(t_sprite));
	spr.gfx = 19;
	spr.dead = 0;
	spr.hp = 0;
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
	free_memory(arr);
	return (spr);
}

void			read_spriteinfo(t_doom *dm, int i, int fd)
{
	char		*gnl;
	char		**arr;

	while (++i < SPR)
	{
		dm->spr[i].gfx = 16;
		if (dm->datareadtype != SPRITE)
			dm->spr[i] = fill_spriteinfo();
		else if (get_next_line(fd, &gnl) == 1)
		{
			printf("Got a line in sprite %s\n", gnl);
			arr = ft_strsplit(gnl, ',');
			datatype_check(dm, arr);
			if (dm->datareadtype != SPRITE)
			{
				dm->spr[i] = fill_spriteinfo();
				free_memory(arr);
			}
			else
				dm->spr[i] = set_sprite(arr, 0);
			free(gnl);
		}
		else
			dm->spr[i] = fill_spriteinfo();
	}
}

void			read_objectinfo(t_doom *dm, int i, int fd)
{
	char		*gnl;
	char		**arr;

	while (++i < OBJ)
	{
		if (dm->datareadtype != OBJECT)
		{
			dm->obj[i] = fill_objectinfo();
			printf("does it go to fill in obj\n");
		}
		else if (get_next_line(fd, &gnl) == 1)
		{
			printf("Got a line in obj %s\n", gnl);
			arr = ft_strsplit(gnl, ',');
			datatype_check(dm, arr);
			if (dm->datareadtype != OBJECT)
			{
				printf("got to fill objectinfo");
				dm->obj[i] = fill_objectinfo();
			}
			else
				dm->obj[i] = set_sprite(arr, 0);
			free(gnl);
		}
		else
			dm->obj[i] = fill_objectinfo();
	}
	
}

//more cheks needed if object comes first and then sprites
// also marker to know if sprites or objects has been added already
// also whole fill of the sprites and objects if sprites or objecst lines are not found in the map
void			comp_sprite(t_doom *dm, int fd)
{
	char		*gnl;
	int			prev_datatype;
	int			sprdone;
	int			objdone;

	if (dm->datareadtype == SPRITE)
		read_spriteinfo(dm, -1, fd);
	prev_datatype = dm->datareadtype;
	if (dm->datareadtype == OBJECT)
		read_objectinfo(dm, -1, fd);
	else if (get_next_line(fd, &gnl) == 1)
	{
		datatype_check(dm, &gnl);
		free(gnl);
		if (prev_datatype != dm->datareadtype && dm->datareadtype == OBJECT)
			read_objectinfo(dm, -1, fd);

	}
//	if (dm->datareadtype == OBJECT)
//		read_objectinfo(dm, -1, fd);
//	while (++i < SPR )
//	{
//		dm->spr[i].gfx = 16;
//		if (get_next_line(fd, &gnl) == 1)
//		{
//			printf("Got a line %s\n", gnl);
//			arr = ft_strsplit(gnl, ',');
//			dm->spr[i] = set_sprite(arr, 0);
//			free(gnl);
//		}
//	}
//	if (get_next_line(fd, &gnl) == 1)
//		free(gnl);
//	i = -1;
//	while (++i < OBJ)
//	{
//		if (get_next_line(fd, &gnl) == 1)
//		{
//			arr = ft_strsplit(gnl, ',');
//			dm->obj[i] = set_sprite(arr, 0);
//			free(gnl);
//		}
//	}
}
