/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:50:54 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/01 15:01:37 by tbergkul         ###   ########.fr       */
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
				//printf("killed enemy\n");
				ft_bzero(&dm->prj[i], sizeof(t_sprite));
				ft_bzero(&dm->spr[x], sizeof(t_sprite));
				return ;
			}
			else if (dm->spr[x].hp > 1)
			{
				dm->spr[x].hp -= 1;
				//printf("hit enemy\n");
				ft_bzero(&dm->prj[i], sizeof(t_sprite));
				Mix_PlayChannel(-1, dm->ishit, 0);
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
			//printf("hit wall\n");
			ft_bzero(&dm->prj[i], sizeof(t_sprite));
			return ;
		}
	}
}

/*
** Second parameter is which projectile to handle
** Third parameter is which sprite that's firing the projectile
*/
void	ai_shooting(t_doom *dm, int i)
{
	if (dm->spr[i].move == 's' && dm->spr[i].frame == 0)
	{
		dm->prj[i].gfx = 24;
		dm->prj[i].mov = (t_vector){.z = dm->spr[i].dir.z * -0.2,
			.y = dm->spr[i].dir.y * -0.2, .x = dm->spr[i].dir.x * -0.2};
		dm->prj[i].pos.z = dm->spr[i].pos.z + (dm->prj[i].mov.z * 2);
		dm->prj[i].pos.y = dm->spr[i].pos.y + (dm->prj[i].mov.y * 2);
		dm->prj[i].pos.x = dm->spr[i].pos.x + (dm->prj[i].mov.x * 2);
		dm->prj[i].dir = dm->spr[i].dir;
		dm->prj[i].size = 5;
		dm->prj[i].move = 'm';
	}
	if (dm->prj[i].move == 'm')
	{
		dm->prj[i].pos.z += dm->prj[i].mov.z;
		dm->prj[i].pos.y += dm->prj[i].mov.y;
		dm->prj[i].pos.x += dm->prj[i].mov.x;
	}
	if (dm->prj[i].move == 'm' && dm->prj[i].dist < 0.6)
	{
		if (!dm->iframe && dm->invincible != 4)
		{
			dm->hp -= 1;
			dm->iframe = 50;
		}
		ft_bzero(&dm->prj[i], sizeof(t_sprite));
	}
	if (dm->prj[i].move == 'm' && dm->area[(int)dm->prj[i].pos.z][(int)dm->prj[i].pos.y][(int)dm->prj[i].pos.x].b > 1)
		ft_bzero(&dm->prj[i], sizeof(t_sprite));
}
