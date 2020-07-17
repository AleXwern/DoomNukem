/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:01:53 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/10 15:00:34 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>//

void	set_yroation(t_doom *wlf)
{
	if (wlf->dir.y > 0)
		wlf->rotation = 180 - (wlf->dir.x + 1) * 90;
	else
		wlf->rotation = 360 - fabs(wlf->dir.x - 1) * 90;


}

void	set_reverse(t_doom *wlf)
{
	t_vector	test;

	if (wlf->rotation < 180)
		test.x = (double)(-wlf->rotation / 90.0) + 1.0;
	else
		test.x = fabs((double)(-wlf->rotation / 90.0)) - 3.0;
	if (wlf->rotation < 180)
		test.y = (fabs((fabs(wlf->rotation - 90.0) / 90.0) - 1));
	else
		test.y = fabs((double)(-(wlf->rotation - 90) / 90.0)) - 3.0;
	//printf("Rot %f %f\n", test.x, test.y);
}

int		checkrota(double dir, double plane)
{
	if (dir > 0 && plane < 0)
		return (0);
	if (dir < 0 && plane > 0)
		return (0);
	if (dir > 1.0f || dir < -1.0f)
		return (0);
	if (plane > 1.5f || plane < -1.5f)
		return (0);
	return (1);
}

void	cam_udy(t_doom *wlf)
{
	t_vector	oldplane;
	t_vector	olddir;

	oldplane = wlf->plane;
	olddir = wlf->dir;
	if (wlf->key.w)
	{
		if (wlf->dir.z > -0.6)
			wlf->dir.z -= 0.05;
	}
	if (wlf->key.s)
	{
		if (wlf->dir.z < 0.6)
			wlf->dir.z += 0.05;
	}
	wlf->camshift = 1.0 - (wlf->dir.z * 2);
}

void	move_l(t_doom *wlf, t_vector olddir, t_vector oldplane)
{
	double	rota;

	oldplane = wlf->plane;
	olddir = wlf->dir;
	rota = wlf->rotsp * ((30.0 / wlf->buffer) / wlf->prefps);
	if (wlf->key.right)
	{
		wlf->dir.x = olddir.x * cos(rota) - olddir.y * sin(rota);
		wlf->dir.y = olddir.x * sin(rota) + olddir.y * cos(rota);
		wlf->plane.x = oldplane.x * cos(rota) - oldplane.y * sin(rota);
		wlf->plane.y = oldplane.x * sin(rota) + oldplane.y * cos(rota);
		wlf->sbox -= (wlf->winw / 64.0) * (rota / wlf->rotsp);
	}
}

int		move_lr(t_doom *wlf)
{
	t_vector	olddir;
	t_vector	oldplane;
	double		rota;

	oldplane = wlf->plane;
	olddir = wlf->dir;
	rota = -wlf->rotsp * ((30.0 / wlf->buffer) / wlf->prefps);
	if (wlf->key.left)
	{
		wlf->dir.x = olddir.x * cos(rota) - olddir.y * sin(rota);
		wlf->dir.y = olddir.x * sin(rota) + olddir.y * cos(rota);
		wlf->plane.x = oldplane.x * cos(rota) - oldplane.y * sin(rota);
		wlf->plane.y = oldplane.x * sin(rota) + oldplane.y * cos(rota);
		wlf->sbox -= (wlf->winw / 64) * (rota / wlf->rotsp);
	}
	set_yroation(wlf);
	set_reverse(wlf);
	if (wlf->key.right)
		move_l(wlf, olddir, oldplane);
	if (wlf->sbox < 0)
		wlf->sbox += wlf->winw;
	if (wlf->sbox > wlf->winw)
		wlf->sbox -= wlf->winw;
	return (0);
}

int		move_fb(t_doom *wlf)
{
	double	mov;
	
	mov = wlf->movsp * ((30.0 / wlf->buffer) / wlf->prefps);
	if (mov > 1.0)
		mov = 0.99;
	if (wlf->key.up)
	{
		if (wlf->area[(int)wlf->pos.z][(int)(wlf->pos.y + wlf->dir.y * mov)][(int)wlf->pos.x] <= 1)
			wlf->pos.y += wlf->dir.y * mov;
		if (wlf->area[(int)wlf->pos.z][(int)wlf->pos.y][(int)(wlf->pos.x + wlf->dir.x * mov)] <= 1)
			wlf->pos.x += wlf->dir.x * mov;
	}
	if (wlf->key.down)
	{
		if (wlf->area[(int)wlf->pos.z][(int)(wlf->pos.y - wlf->dir.y * mov)][(int)wlf->pos.x] <= 1)
			wlf->pos.y -= wlf->dir.y * mov;
		if (wlf->area[(int)wlf->pos.z][(int)wlf->pos.y][(int)(wlf->pos.x - wlf->dir.x * mov)] <= 1)
			wlf->pos.x -= wlf->dir.x * mov;
	}
	return (0);
}

void	strafe(t_doom *wlf, double dirxtemp, double dirytemp)
{
	double	mov;

	mov = wlf->movsp * ((30.0 / wlf->buffer) / wlf->prefps);
	if (mov > 1.0)
		mov = 0.99;
	if (wlf->key.q)
	{
		if (wlf->area[(int)wlf->pos.z][(int)(wlf->pos.y + wlf->dir.x * mov)][(int)wlf->pos.x] <= 1)
			wlf->pos.y += wlf->dir.x * mov;
		if (wlf->area[(int)wlf->pos.z][(int)wlf->pos.y][(int)(wlf->pos.x + wlf->dir.y * mov)] <= 1)
			wlf->pos.x += wlf->dir.y * mov;
	}
	if (wlf->key.e)
	{
		if (wlf->area[(int)wlf->pos.z][(int)(wlf->pos.y - wlf->dir.x * mov)][(int)wlf->pos.x] <= 1)
			wlf->pos.y -= wlf->dir.x * mov;
		if (wlf->area[(int)wlf->pos.z][(int)wlf->pos.y][(int)(wlf->pos.x - wlf->dir.y * mov)] <= 1)
			wlf->pos.x -= wlf->dir.y * mov;
	}
	return ;


	if (wlf->key.q)
	{
		if (wlf->dir.y < 0)
		{
			if (wlf->area[(int)wlf->pos.z][(int)(wlf->pos.y - wlf->dir.y
					* wlf->movsp)][(int)wlf->pos.x] <= 1)
				wlf->pos.y -= (wlf->dir.y + 1) * wlf->movsp;
		}
		else
		{
			if (wlf->area[(int)wlf->pos.z][(int)(wlf->pos.y - wlf->dir.y
					* wlf->movsp)][(int)wlf->pos.x] <= 1)
				wlf->pos.y += (wlf->dir.y - 1) * wlf->movsp;
		}
		if (wlf->dir.x < 0)
		{
			if (wlf->area[(int)wlf->pos.z][(int)wlf->pos.y][(int)(wlf->pos.x
					- wlf->dir.x * wlf->movsp)] <= 1)
				wlf->pos.x -= (wlf->dir.x + 1) * wlf->movsp;
		}
		else
		{
			if (wlf->area[(int)wlf->pos.z][(int)wlf->pos.y][(int)(wlf->pos.x
					- wlf->dir.x * wlf->movsp)] <= 1)
				wlf->pos.x += (wlf->dir.x - 1) * wlf->movsp;
		}
	}
	if (wlf->key.e)
	{
		if (wlf->dir.y >= 0)
		{
			dirxtemp = wlf->dir.x - 1;
		}
		else if (wlf->dir.y < 0)
		{
			dirxtemp = wlf->dir.x + 1;
		}
		if (wlf->dir.x >= 0)
		{
			dirytemp = wlf->dir.y - 1;
		}
		else if (wlf->dir.x < 0)
		{
			dirytemp = wlf->dir.y + 1;
		}
		wlf->pos.x += dirxtemp * wlf->movsp;
		wlf->pos.y += dirytemp * wlf->movsp;
	}
}
