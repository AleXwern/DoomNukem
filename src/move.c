/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:01:53 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/21 14:43:15 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>//

void	set_yroation(t_doom *dm)
{
	if (dm->dir.y > 0)
		dm->rotation = 180 - (dm->dir.x + 1) * 90;
	else
		dm->rotation = 360 - fabs(dm->dir.x - 1) * 90;


}

void	set_reverse(t_doom *dm)
{
	t_vector	test;

	if (dm->rotation < 180)
		test.x = (double)(-dm->rotation / 90.0) + 1.0;
	else
		test.x = fabs((double)(-dm->rotation / 90.0)) - 3.0;
	if (dm->rotation < 180)
		test.y = (fabs((fabs(dm->rotation - 90.0) / 90.0) - 1));
	else
		test.y = fabs((double)(-(dm->rotation - 90) / 90.0)) - 3.0;
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

void	cam_udy(t_doom *dm)
{
	t_vector	oldplane;
	t_vector	olddir;

	oldplane = dm->plane;
	olddir = dm->dir;
	if (dm->key.w)
	{
		if (dm->dir.z > -0.6)
			dm->dir.z -= 0.05;
	}
	if (dm->key.s)
	{
		if (dm->dir.z < 0.6)
			dm->dir.z += 0.05;
	}
	dm->camshift = 1.0 - (dm->dir.z * 2);
}

void	move_l(t_doom *dm, t_vector olddir, t_vector oldplane)
{
	double	rota;

	oldplane = dm->plane;
	olddir = dm->dir;
	rota = dm->rotsp * ((30.0 / dm->buffer) / dm->prefps);
	if (dm->key.right)
	{
		dm->dir.x = olddir.x * cos(rota) - olddir.y * sin(rota);
		dm->dir.y = olddir.x * sin(rota) + olddir.y * cos(rota);
		dm->plane.x = oldplane.x * cos(rota) - oldplane.y * sin(rota);
		dm->plane.y = oldplane.x * sin(rota) + oldplane.y * cos(rota);
		dm->sbox -= (dm->winw / 64.0) * (rota / dm->rotsp);
	}
}

int		move_lr(t_doom *dm)
{
	t_vector	olddir;
	t_vector	oldplane;
	double		rota;

	oldplane = dm->plane;
	olddir = dm->dir;
	rota = -dm->rotsp * ((30.0 / dm->buffer) / dm->prefps);
	if (dm->key.left)
	{
		dm->dir.x = olddir.x * cos(rota) - olddir.y * sin(rota);
		dm->dir.y = olddir.x * sin(rota) + olddir.y * cos(rota);
		dm->plane.x = oldplane.x * cos(rota) - oldplane.y * sin(rota);
		dm->plane.y = oldplane.x * sin(rota) + oldplane.y * cos(rota);
		dm->sbox -= (dm->winw / 64) * (rota / dm->rotsp);
	}
	set_yroation(dm);
	set_reverse(dm);
	if (dm->key.right)
		move_l(dm, olddir, oldplane);
	if (dm->sbox < 0)
		dm->sbox += dm->winw;
	if (dm->sbox > dm->winw)
		dm->sbox -= dm->winw;
	return (0);
}

int		diffcheck_y(t_doom *dm, double mov)
{
	double	cpos;
	double	tarpos;

	cpos = ceil(dm->pos.z) - dm->pos.z - 0.6;
	if (dm->key.up)
	{
		if (dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->dir.y * mov)][(int)dm->pos.x].pt == 2)
			tarpos = (dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->dir.y * mov)][(int)dm->pos.x].pln / 15.0);
		else
			tarpos = 1;
	}
	printf("pos %f %f\n", cpos, tarpos);
	if (dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->dir.y * mov)][(int)dm->pos.x].b <= 1)
		return (1);
	if (fabs(cpos - tarpos) < 0.5)
	{
		dm->pos.z = (int)dm->pos.z + 0.6 + (dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->dir.y * mov)][(int)dm->pos.x].pln / 15.0);
		return (1);
	}
	return(0);
}

int		diffcheck_x(t_doom *dm, double mov)
{
	double	cpos;
	double	tarpos;

	cpos = ceil(dm->pos.z) - dm->pos.z - 0.6;
	if (dm->key.up)
	{
		if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->dir.x * mov)].pt == 2)
			tarpos = (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->dir.x * mov)].pln / 15.0);
		else
			tarpos = 1;
	}
	printf("pos %f %f %f\n", cpos, tarpos, dm->pos.z);
	if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->dir.x * mov)].b <= 1)
		return (1);
	if (fabs(cpos - tarpos) < 0.5)
	{
		dm->pos.z += fabs(cpos - tarpos);
		return (1);
	}
	return(0);
}

int		move_fb(t_doom *dm)
{
	double	mov;
	
	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0 || mov < -1.0)
		mov /= fabs(mov) * 2;
	if (dm->key.up)
	{
		/*if (diffcheck_y(dm, mov))
			dm->pos.y += dm->dir.y * mov;
		if (diffcheck_x(dm, mov))
			dm->pos.x += dm->dir.x * mov;*/
		if (dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->dir.y * mov)][(int)dm->pos.x].b <= 1)
			dm->pos.y += dm->dir.y * mov;
		if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->dir.x * mov)].b <= 1)
			dm->pos.x += dm->dir.x * mov;
	}
	if (dm->key.down)
	{
		if (dm->area[(int)dm->pos.z][(int)(dm->pos.y - dm->dir.y * mov)][(int)dm->pos.x].b <= 1)
			dm->pos.y -= dm->dir.y * mov;
		if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x - dm->dir.x * mov)].b <= 1)
			dm->pos.x -= dm->dir.x * mov;
	}
	if (dm->area[(int)dm->pos.z + 1][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1)
		dm->airbrn = 1;
	return (0);
}

void	strafe(t_doom *dm, double dirxtemp, double dirytemp)
{
	double	mov;

	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0)
		mov = 0.99;
	if (dm->key.q)
	{
		if (dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->dir.x * mov)][(int)dm->pos.x].b <= 1)
			dm->pos.y += dm->dir.x * mov;
		if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->dir.y * mov)].b <= 1)
			dm->pos.x += dm->dir.y * mov;
	}
	if (dm->key.e)
	{
		if (dm->area[(int)dm->pos.z][(int)(dm->pos.y - dm->dir.x * mov)][(int)dm->pos.x].b <= 1)
			dm->pos.y -= dm->dir.x * mov;
		if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x - dm->dir.y * mov)].b <= 1)
			dm->pos.x -= dm->dir.y * mov;
	}
	return ;


	if (dm->key.q)
	{
		if (dm->dir.y < 0)
		{
			if (dm->area[(int)dm->pos.z][(int)(dm->pos.y - dm->dir.y
					* dm->movsp)][(int)dm->pos.x].b <= 1)
				dm->pos.y -= (dm->dir.y + 1) * dm->movsp;
		}
		else
		{
			if (dm->area[(int)dm->pos.z][(int)(dm->pos.y - dm->dir.y
					* dm->movsp)][(int)dm->pos.x].b <= 1)
				dm->pos.y += (dm->dir.y - 1) * dm->movsp;
		}
		if (dm->dir.x < 0)
		{
			if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x
					- dm->dir.x * dm->movsp)].b <= 1)
				dm->pos.x -= (dm->dir.x + 1) * dm->movsp;
		}
		else
		{
			if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x
					- dm->dir.x * dm->movsp)].b <= 1)
				dm->pos.x += (dm->dir.x - 1) * dm->movsp;
		}
	}
	if (dm->key.e)
	{
		if (dm->dir.y >= 0)
		{
			dirxtemp = dm->dir.x - 1;
		}
		else if (dm->dir.y < 0)
		{
			dirxtemp = dm->dir.x + 1;
		}
		if (dm->dir.x >= 0)
		{
			dirytemp = dm->dir.y - 1;
		}
		else if (dm->dir.x < 0)
		{
			dirytemp = dm->dir.y + 1;
		}
		dm->pos.x += dirxtemp * dm->movsp;
		dm->pos.y += dirytemp * dm->movsp;
	}
}
