/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_game_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:42:20 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/21 16:09:14 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		x_press(t_doom *dm)
{
	error_out(FINE, dm);
	return (0);
}

void	jetpack(t_doom *dm)
{
	if (dm->key.one)
	{
		if (dm->area[(int)(dm->pos.z + 0.5)][(int)(dm->pos.y)]
			[(int)dm->pos.x].b <= 1)
			dm->pos.z += 0.05 * (30.0 / dm->buffer / dm->prefps);
	}
	if (dm->key.two)
	{
		Mix_PlayChannel(-1, dm->jetpacksound, 0);
		if (dm->area[(int)(dm->pos.z - 0.5)][(int)(dm->pos.y)]
			[(int)dm->pos.x].b <= 1 && dm->pos.z > 1)
			dm->pos.z -= 0.05 * (30.0 / dm->buffer / dm->prefps);
	}
	dm->airbrn = 1;
}

int		mouse_move(int x, int y, t_doom *dm)
{
	t_vector	olddir;
	t_vector	oldplane;
	t_vector	rota;

	olddir = dm->dir;
	oldplane = dm->plane;
	if (x && abs(x) < dm->winw)
	{
		rota.x = (double)x / dm->winw * OSCAM;
		dm->dir.x = olddir.x * cos(rota.x) - olddir.y * sin(rota.x);
		dm->dir.y = olddir.x * sin(rota.x) + olddir.y * cos(rota.x);
		dm->plane.x = oldplane.x * cos(rota.x) - oldplane.y * sin(rota.x);
		dm->plane.y = oldplane.x * sin(rota.x) + oldplane.y * cos(rota.x);
	}
	if (y && abs(y) < dm->winh)
	{
		rota.y = (double)y / dm->winh * OSCAM;
		if (dm->dir.z + rota.y > -0.5 && dm->dir.z + rota.y < 0.5)
			dm->dir.z += rota.y;
		dm->camshift = 1.0 - (dm->dir.z * 2);
	}
	return (0);
}

int		move(t_doom *dm)
{
	if (dm->alive)
	{
		if ((dm->key.w || dm->key.s) && !dm->isoptions)
			move_fb(dm);
		if ((dm->key.a || dm->key.d) && !dm->isoptions)
			strafe(dm);
		if ((dm->key.up || dm->key.down || dm->key.left || dm->key.right)
			&& !dm->isoptions)
			cam_udy(dm);
		if ((dm->key.one || dm->key.two) && !dm->isoptions && dm->jetpack)
			jetpack(dm);
		gravity(dm);
		if ((dm->key.space) && !dm->isoptions && !dm->airbrn)
		{
			dm->airbrn = 1;
			dm->gravity.z = -0.45 * (30.0 / dm->buffer / dm->prefps);
		}
		if (!dm->airbrn && !dm->iframe)
			suffrocate(dm, dm->area[(int)(dm->pos.z - 0.1)][(int)dm->pos.y]
			[(int)dm->pos.x], (t_vector){.z = dm->pos.z - (int)dm->pos.z,
			.y = dm->pos.y - (int)dm->pos.y, .x = dm->pos.x - (int)dm->pos.x});
		if (dm->key.space > 0)
			dm->key.space--;
	}
	return (0);
}

void	jump(t_doom *dm)
{
	dm->key.space = 3;
	Mix_PlayChannel(-1, dm->jump, 0);
}
