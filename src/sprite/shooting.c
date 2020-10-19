/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:50:54 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/19 12:20:39 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		check_hit2(t_doom *dm, int i)
{
	if (dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y]
		[(int)dm->prj[i].pos.x].b > 1)
	{
		if (dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y]
			[(int)dm->prj[i].pos.x].b == 6)
		{
			Mix_PlayChannel(-1, dm->windowbrk, 0);
			dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y]
				[(int)dm->prj[i].pos.x].pt = 0;
			dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y]
				[(int)dm->prj[i].pos.x].b = 1;
		}
		ft_bzero(&dm->prj[i], sizeof(t_sprite));
		return (1);
	}
	return (0);
}

/*
**	Second parameter is which projectile to handle
**	Third parameter is used as id for enemy sprites
*/

void	check_hit(t_doom *dm, int i, int x)
{
	while (++x < 9)
	{
		if ((tri_pythagor(dm->prj[i].pos, dm->spr[x].pos)) < 0.5)
		{
			if (dm->spr[x].hp == 1)
			{
				dm->spr[x].hp = 0;
				Mix_PlayChannel(-1, dm->mondeath, 0);
				ft_bzero(&dm->prj[i], sizeof(t_sprite));
				ft_bzero(&dm->spr[x], sizeof(t_sprite));
				return ;
			}
			else if (dm->spr[x].hp > 1)
			{
				dm->spr[x].hp -= 1;
				ft_bzero(&dm->prj[i], sizeof(t_sprite));
				Mix_PlayChannel(-1, dm->ishit, 0);
				return ;
			}
		}
		if (check_hit2(dm, i))
			return ;
	}
}

/*
** Second parameter is which projectile to handle
*/

void	player_shooting(t_doom *dm, int i)
{
	if (dm->shooting && dm->ani == 1 && dm->frm == 2)
	{
		dm->prj[i].gfx = 24;
		dm->prj[i].dir = dm->dir;
		dm->prj[i].mov = (t_vector){.z = dm->dir.z * 0.4,
			.y = dm->dir.y * 0.4, .x = dm->dir.x * 0.4};
		dm->prj[i].pos.z = dm->pos.z + (dm->prj[i].mov.z * 2);
		dm->prj[i].pos.y = dm->pos.y + (dm->prj[i].mov.y * 2);
		dm->prj[i].pos.x = dm->pos.x + (dm->prj[i].mov.x * 2);
		dm->prj[i].size = 4;
		dm->prj[i].move = 'm';
	}
	if (dm->prj[i].move == 'm')
	{
		dm->prj[i].pos.z += dm->prj[i].mov.z;
		dm->prj[i].pos.y += dm->prj[i].mov.y;
		dm->prj[i].pos.x += dm->prj[i].mov.x;
		check_hit(dm, i, -1);
	}
}

void	foe_shooting2(t_doom *dm, t_sprite *prj)
{
	if (prj->move == 'm' && prj->dist < 0.6)
	{
		if (!dm->iframe && dm->invincible != 4 && dm->alive)
		{
			dm->hp -= 1;
			dm->iframe = 50;
		}
		ft_bzero(prj, sizeof(t_sprite));
	}
}

void	foe_shooting(t_doom *dm, t_sprite *spr, t_sprite *prj)
{
	if (spr->move == 's')
	{
		prj->mov = (t_vector){.z = spr->dir.z * -0.2,
			.y = spr->dir.y * -0.2, .x = spr->dir.x * -0.2};
		prj->pos.z = spr->pos.z + (prj->mov.z * 2);
		prj->pos.y = spr->pos.y + (prj->mov.y * 2);
		prj->pos.x = spr->pos.x + (prj->mov.x * 2);
		prj->move = 'm';
	}
	if (prj->move == 'm')
	{
		if ((dm->area[(int)(prj->pos.z + prj->mov.z)][(int)prj->pos.y]
			[(int)prj->pos.x].b <= 1) && (dm->area[(int)prj->pos.z]
			[(int)(prj->pos.y + prj->mov.y)][(int)prj->pos.x].b <= 1)
			&& (dm->area[(int)prj->pos.z]
			[(int)prj->pos.y][(int)(prj->pos.x + prj->mov.x)].b <= 1))
		{
			prj->pos.z += prj->mov.z;
			prj->pos.y += prj->mov.y;
			prj->pos.x += prj->mov.x;
		}
		else
			ft_bzero(prj, sizeof(t_sprite));
	}
	foe_shooting2(dm, prj);
}
