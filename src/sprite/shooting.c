/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:50:54 by tbergkul          #+#    #+#             */
/*   Updated: 2020/09/24 15:10:12 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
** Second parameter is which projectile to handle
*/
void	player_shooting(t_doom *dm, int i)
{
	if (dm->shooting && dm->ani == 1 && dm->frm == 2)
	{
		dm->prj[i].gfx = 24;
		dm->prj[i].dir = dm->dir;
		dm->prj[i].mov = (t_vector){.z = dm->dir.z * 0.6,
			.y = dm->dir.y * 0.6, .x = dm->dir.x * 0.60};
		dm->prj[i].pos.z = dm->pos.z + (dm->prj[i].mov.z * 5);
		dm->prj[i].pos.y = dm->pos.y + (dm->prj[i].mov.y * 5);
		dm->prj[i].pos.x = dm->pos.x + (dm->prj[i].mov.x * 5);
		dm->prj[i].size = 5;
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

void	check_hit(t_doom *dm, int i, int x)
{
	while (++x < 9)
	{
		if ((tri_pythagor(dm->prj[i].pos, dm->spr[x].pos)) < 0.7)
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
				Mix_PlayChannel(-1, dm->gettingHit, 0);
				return ;
			}
		}
		if (dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y][(int)dm->prj[i].pos.x].b > 1)
		{
			if (dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y][(int)dm->prj[i].pos.x].b == 6)
			{
				Mix_PlayChannel(-1, dm->windowbrk, 0);
				dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y][(int)dm->prj[i].pos.x].pt = 0;
				dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y][(int)dm->prj[i].pos.x].b = 1;
			}
			ft_bzero(&dm->prj[i], sizeof(t_sprite));
			return ;
		}
	}
}

/*
** Second parameter is which projectile to handle
** Third parameter is which sprite that's firing the projectile
*/
void	ai_shooting(t_doom *dm, int i, int s)// mov: + 0.12   pos.z: + 0.08 if pokemon trainer
{
	if (dm->prj[i].frame == 0 && dm->prj[i].move != 'm' && dm->spr[s].move == 's')
	{
		dm->prj[i].gfx = 24;
		dm->prj[i].mov = (t_vector){.z = (dm->spr[s].dir.z + 0.12) * -0.2,
			.y = dm->spr[s].dir.y * -0.2, .x = dm->spr[s].dir.x * -0.2};
		dm->prj[i].pos.z = (dm->spr[s].pos.z + 0.8) + (dm->prj[i].mov.z * 5);
		dm->prj[i].pos.y = dm->spr[s].pos.y + (dm->prj[i].mov.y * 5);
		dm->prj[i].pos.x = dm->spr[s].pos.x + (dm->prj[i].mov.x * 5);
		dm->prj[i].size = 5;
		dm->prj[i].move = 'm';
	}
	if (dm->prj[i].move == 'm')
	{
		dm->prj[i].pos.z += dm->prj[i].mov.z;
		dm->prj[i].pos.y += dm->prj[i].mov.y;
		dm->prj[i].pos.x += dm->prj[i].mov.x;
	}
	dm->prj[i].frame++;
	if (dm->prj[i].frame > 50)
		dm->prj[i].frame = 0;
	if (dm->prj[i].move == 'm' && dm->prj[i].dist < 0.3)
	{
		dm->hp -= 1;
		dm->iframe = 50;
		ft_bzero(&dm->prj[i], sizeof(t_sprite));
	}
	if (dm->prj[i].move == 'm' && dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y][(int)dm->prj[i].pos.x].b > 1)
		ft_bzero(&dm->prj[i], sizeof(t_sprite));
}
