/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:26:23 by vkeinane          #+#    #+#             */
/*   Updated: 2020/12/02 19:31:42 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void    sprite_validation(t_sprite *spr)
{
    if (spr->gfx > MAXGFX || spr->gfx < MINGFX)
        spr->gfx = MAXGFX;
    if (spr->dead != 1 && spr->dead != 0)
        spr->dead = 0;
    if (spr->hp > MAXHP || spr->hp < 0)
        spr->hp = 1;
    if (spr->respawn > MAXRESPAWN || spr->respawn < 0)
        spr->respawn = 0;
    if (spr->gfx == 35 && spr->size != 2)
        spr->size = 2;
    else
        spr->size = 1;
	if (spr->pos.z > 50 || spr->pos.z < 0)
        spr->pos.z = 20 / 10;
    if (spr->pos.x > 250 || spr->pos.x < 0)
        spr->pos.x = 175 / 10;
    if (spr->pos.y > 250 || spr->pos.y < 0)
        spr->pos.y = 175 / 10;
    printf("%d,%d,%d,%f,%f,%f,%d\nIn sprite validation \n", spr->gfx, spr->dead, spr->hp, spr->pos.z, spr->pos.y, spr->pos.x, spr->respawn);
}

int     datatype_check(t_doom *dm, char **tmp)
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
        printf("Got in datatypechange :  %d\n", dm->datareadtype);
    }
    if (dm->datareadtype != BLOCK)
        return(1);
    return (0);
}