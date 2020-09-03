/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:48:35 by tbergkul          #+#    #+#             */
/*   Updated: 2020/09/03 16:38:44 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_hud(t_doom *dm)
{
	draw_hp(dm);
	draw_gfx(dm, dm->gfx[29], 0, dm->winh - 110);//inventory
	if (dm->keycard)
		draw_pgfx_sc(dm, dm->gfx[30], (int[6]){(dm->winh - 78), 125, 140, 200, 0, 0}, 0.35);//keycard
	if (dm->gun)
	{
		draw_pgfx_sc(dm, dm->gfx[36], (int[6]){(dm->winh - 78), 20, 272, 380, 0, 0}, 0.2);//pistol in inventory
		draw_gun(dm);
		draw_ammo(dm);
		draw_gfx(dm, dm->gfx[25], (WINX / 2) - 25, (WINY / 2) - 25);//crosshair
	}
}

void	draw_gun(t_doom *dm)
{
	if (!dm->reloading)
	{
		dm->gfx[27].x = 160 * dm->ani;
		draw_pgfx_sc(dm, dm->gfx[27], (int[6]){(dm->winh - 320), ((dm->winw / 2) - 16), 160, 160, 0, 0}, 2);
		if (dm->shooting)
		{
			dm->frm++;
			if (dm->ani == 1 && dm->frm == 2)
			{
				Mix_PlayChannel(-1, dm->gunshot, 0);
				/*if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b == 1)//if enemy hit, make a soundeffect. Now just testing with block instead of enemy.
				{
					Mix_PlayChannel(-1, dm->gettingHit, 0);
					//printf("\n\n\nblock hit = %hhu\n\n\n", dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b);
				}*/
			}
			if (dm->frm == 4)
			{
				if (dm->ani == 5)
				{
					dm->ani = 0;
					dm->shooting = 0;
					dm->magazine--;
				}
				else
					dm->ani++;
				dm->frm = 0;
			}
		}
	}
	if (dm->reloading)
		reloading_gun(dm);
}

void	reloading_gun(t_doom *dm)
{
	dm->gfx[27].x = 160 * dm->ani + 960;
	draw_pgfx_sc(dm, dm->gfx[27], (int[6]){(dm->winh - 320), ((dm->winw / 2) - 16), 160, 160, 0, 0}, 2);
	dm->frm++;
	if (dm->ani == 2 && dm->frm == 2)
		Mix_PlayChannel(-1, dm->reload, 0);
	if (dm->frm == 6)
	{
		if (dm->ani == 11)
		{
			dm->ani = 0;
			dm->reloading = 0;
			dm->magazine = 10;
		}
		else
			dm->ani++;
		dm->frm = 0;
	}
}

void	draw_ammo(t_doom *dm)
{
	if (dm->magazine == 10)
	{
		dm->gfx[31].x = 50;
		draw_pgfx_sc(dm, dm->gfx[31], (int[6]){(dm->winh - 60), (dm->winw - 85), 50, 50, 0, 0}, 1);
		dm->gfx[31].x = 0;
		draw_pgfx_sc(dm, dm->gfx[31], (int[6]){(dm->winh - 60), (dm->winw - 60), 50, 50, 0, 0}, 1);
	}
	else
	{
		dm->gfx[31].x = 50 * dm->magazine;
		draw_pgfx_sc(dm, dm->gfx[31], (int[6]){(dm->winh - 60), (dm->winw - 60), 50, 50, 0, 0}, 1);
	}
}

void	draw_hp(t_doom *dm)
{
	int	healthBar;

	if (dm->hp == 100)
		healthBar = 0;
	else if (dm->hp == 80)
		healthBar = 1;
	else if (dm->hp == 60)
		healthBar = 2;
	else if (dm->hp == 40)
		healthBar = 3;
	else if (dm->hp == 20)
		healthBar = 4;
	else if (dm->hp == 0 || dm->hp < 0)
		healthBar = 5;
	dm->gfx[28].y = healthBar * 60;
	draw_pgfx_sc(dm, dm->gfx[28], (int[6]){10, 20, 60, 367, 0, 0}, 1);
}
