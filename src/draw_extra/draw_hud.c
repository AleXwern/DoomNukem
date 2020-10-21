/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:48:35 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/21 14:05:04 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_hud(t_doom *dm)
{
	draw_hp(dm);
	draw_gfx(dm, dm->gfx[29], 0, dm->winh - 110);
	if (dm->keycard)
		draw_pgfx_sc(dm, dm->gfx[30], (int[6]){(dm->winh - 78), 125, 140, 200,
			0, 0}, 0.35);
	if (dm->gun)
	{
		draw_pgfx_sc(dm, dm->gfx[36], (int[6]){(dm->winh - 78), 20, 272, 380,
			0, 0}, 0.2);
		if (!dm->reloading)
			draw_gun(dm);
		else
			reloading_gun(dm);
		draw_ammo(dm);
		draw_gfx(dm, dm->gfx[25], (int)(dm->winw * 0.5 - 25), (int)(dm->winh
			* 0.5) - 25);
	}
	if (dm->jetpack)
		draw_pgfx_sc(dm, dm->gfx[9], (int[6]){(dm->winh - 83), 230, 350, 200,
			0, 0}, 0.2);
	draw_hud2(dm);
}

void	draw_gun(t_doom *dm)
{
	dm->gfx[27].x = 160 * dm->ani;
	if (dm->winw > 1150)
		draw_pgfx_sc(dm, dm->gfx[27], (int[6]){(dm->winh - 320),
			(int)(dm->winw * 0.5 + 80), 160, 160, 0, 0}, 2);
	else
		draw_pgfx_sc(dm, dm->gfx[27], (int[6]){(dm->winh - 320),
			(int)(dm->winw * 0.5 - 10), 160, 160, 0, 0}, 2);
	if (dm->shooting)
	{
		dm->frm++;
		if (dm->ani == 1 && dm->frm == 1)
			Mix_PlayChannel(-1, dm->gunshot, 0);
		if (dm->frm >= 2)
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

void	reloading_gun(t_doom *dm)
{
	dm->gfx[27].x = 160 * dm->ani + 960;
	if (dm->winw > 1150)
		draw_pgfx_sc(dm, dm->gfx[27], (int[6]){(dm->winh - 320),
			(int)(dm->winw * 0.5 + 80), 160, 160, 0, 0}, 2);
	else
		draw_pgfx_sc(dm, dm->gfx[27], (int[6]){(dm->winh - 320),
			(int)(dm->winw * 0.5 - 16), 160, 160, 0, 0}, 2);
	dm->frm++;
	if (dm->ani == 2 && dm->frm == 2)
		Mix_PlayChannel(-1, dm->reload, 0);
	if (dm->frm >= 2)
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
	char	*ammo;

	ammo = ft_itoa(dm->magazine);
	set_text(dm, ammo, (int[3]){(dm->winh - 60), (dm->winw - 85),
		0xE71313}, 1.5);
	free(ammo);
}

void	draw_hp(t_doom *dm)
{
	int	x;
	int	i;

	x = 20;
	i = -1;
	dm->gfx[28].x = 0;
	while (++i < dm->hp)
	{
		draw_pgfx_sc(dm, dm->gfx[28], (int[6]){10, x, 60, 61, 0, 0}, 1);
		x += 61;
	}
	dm->gfx[28].x = 61;
	while (i < 5)
	{
		draw_pgfx_sc(dm, dm->gfx[28], (int[6]){10, x, 60, 61, 0, 0}, 1);
		x += 61;
		i++;
	}
}
