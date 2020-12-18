/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:26:23 by vkeinane          #+#    #+#             */
/*   Updated: 2020/12/18 10:23:09 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	pos_validation(t_sprite *spr)
{
	if (spr->gfx == 35)
		spr->size = 2;
	else
		spr->size = 1;
	if (spr->pos.z > 8.5 || spr->pos.z < 0.5)
		spr->pos.z = 1.5;
	if (spr->pos.x > 25.0 || spr->pos.x < 0)
		spr->pos.x = 17.5;
	if (spr->pos.y > 25.0 || spr->pos.y < 0)
		spr->pos.y = 17.5;
}

void	sprite_validation(t_sprite *spr, int type)
{
	if (type == OBJECT)
	{
		if (!(spr->gfx >= 34 && spr->gfx <= 37) && spr->gfx != 30 \
			&& spr->gfx != 9)
			spr->gfx = 34;
		if (spr->dead != 0)
			spr->dead = 0;
		if (spr->hp != 0)
			spr->hp = 0;
	}
	else if (type == SPRITE)
	{
		if (spr->gfx > 22 || spr->gfx < 16)
			spr->gfx = 16;
		if (spr->dead != 1 && spr->dead != 0)
			spr->dead = 0;
		if (spr->hp > MAXHP || spr->hp < 0)
			spr->hp = 1;
	}
	if (spr->respawn > MAXRESPAWN || spr->respawn < 0)
		spr->respawn = 0;
	pos_validation(spr);
}

int		datatype_check(t_doom *dm, char **tmp)
{
	int len;

	len = 0;
	len = ft_strlen(tmp[0]);
	if (len == 6)
	{
		if (!(ft_strcmp("Object", tmp[0])))
			dm->datareadtype = OBJECT;
		if (!(ft_strcmp("Sprite", tmp[0])))
			dm->datareadtype = SPRITE;
	}
	if (dm->datareadtype != BLOCK)
		return (1);
	return (0);
}

void	read_spriteinfo(t_doom *dm, int i, int fd, int *sprdone)
{
	char		*gnl;
	char		**arr;

	while (++i < SPR)
	{
		if (dm->datareadtype != SPRITE)
			dm->spr[i] = fill_spriteinfo();
		else if (get_next_line(fd, &gnl) == 1)
		{
			arr = ft_strsplit(gnl, ',');
			datatype_check(dm, arr);
			if (dm->datareadtype != SPRITE)
				dm->spr[i] = fill_spriteinfo();
			else
			{
				dm->spr[i] = set_sprite(arr, 0);
				sprite_validation(&dm->spr[i], dm->datareadtype);
			}
			free_memory(arr);
			free(gnl);
		}
		else
			dm->spr[i] = fill_spriteinfo();
	}
	*sprdone = 1;
}

void	read_objectinfo(t_doom *dm, int i, int fd, int *objdone)
{
	char		*gnl;
	char		**arr;

	while (++i < OBJ)
	{
		if (dm->datareadtype != OBJECT)
			dm->obj[i] = fill_objectinfo();
		else if (get_next_line(fd, &gnl) == 1)
		{
			arr = ft_strsplit(gnl, ',');
			datatype_check(dm, arr);
			if (dm->datareadtype != OBJECT)
				dm->obj[i] = fill_objectinfo();
			else
			{
				dm->obj[i] = set_sprite(arr, 0);
				sprite_validation(&dm->obj[i], dm->datareadtype);
			}
			free_memory(arr);
			free(gnl);
		}
		else
			dm->obj[i] = fill_objectinfo();
	}
	*objdone = 1;
}
