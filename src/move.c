/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:01:53 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/12 16:45:54 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/value.h"
#include "../includes/wolf.h"

#include <stdio.h>//

void	set_yroation(t_wolf *wlf)
{
	if (wlf->dir.y > 0)
		wlf->rotation = 180 - (wlf->dir.x + 1) * 90;
	else
		wlf->rotation = 360 - fabs(wlf->dir.x - 1) * 90;

	
}

void	set_reverse(t_wolf *wlf)
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
	printf("Rot %f %f\n", test.x, test.y);
}

void	cam_udy(t_wolf *wlf)
{
	t_vector	oldplane;
	t_vector	olddir;
	t_vector	rotation;

	oldplane = wlf->plane;
	olddir = wlf->dir;
	rotation.y = wlf->rotsp * sin(wlf->rotation * M_PI / 180);
	rotation.x = wlf->rotsp * cos(wlf->rotation * M_PI / 180);
	if (wlf->keyw)
	{
		wlf->dir.y = olddir.y * cos(rotation.y) - olddir.z * sin(rotation.y);
		wlf->dir.z = olddir.y * sin(rotation.y) + olddir.z * cos(rotation.y);
		wlf->plane.y = oldplane.y * cos(rotation.y) - oldplane.z * sin(rotation.y);
		wlf->plane.z = oldplane.y * sin(rotation.y) + oldplane.z * cos(rotation.y);

		oldplane = wlf->plane;
		olddir = wlf->dir;
		wlf->dir.x = olddir.x * cos(rotation.x) + olddir.z * sin(rotation.x);
		wlf->dir.z = olddir.z * cos(rotation.x) - olddir.x * sin(rotation.x);
		wlf->plane.x = oldplane.x * cos(rotation.x) + oldplane.z * sin(rotation.x);
		wlf->plane.z = oldplane.z * cos(rotation.x) - oldplane.x * sin(rotation.x);

	}
	if (wlf->keys)
	{
		wlf->dir.y = olddir.y * cos(-rotation.y) - olddir.z * sin(-rotation.y);
		wlf->dir.z = olddir.y * sin(-rotation.y) + olddir.z * cos(-rotation.y);
		wlf->plane.y = oldplane.y * cos(-rotation.y) - oldplane.z * sin(-rotation.y);
		wlf->plane.z = oldplane.y * sin(-rotation.y) + oldplane.z * cos(-rotation.y);

		oldplane = wlf->plane;
		olddir = wlf->dir;
		wlf->dir.x = olddir.x * cos(-rotation.x) + olddir.z * sin(-rotation.x);
		wlf->dir.z = olddir.z * cos(-rotation.x) - olddir.x * sin(-rotation.x);
		wlf->plane.x = oldplane.x * cos(-rotation.x) + oldplane.z * sin(-rotation.x);
		wlf->plane.z = oldplane.z * cos(-rotation.x) - oldplane.x * sin(-rotation.x);
	}
	if (wlf->keya)
	{
		wlf->dir.x = olddir.x * cos(rotation.x) + olddir.z * sin(rotation.x);
		wlf->dir.z = olddir.z * cos(rotation.x) - olddir.x * sin(rotation.x);
		wlf->plane.x = oldplane.x * cos(rotation.x) + oldplane.z * sin(rotation.x);
		wlf->plane.z = oldplane.z * cos(rotation.x) - oldplane.x * sin(rotation.x);
	}
	if (wlf->keyd)
	{
		wlf->dir.x = olddir.x * cos(-rotation.x) + olddir.z * sin(-rotation.x);
		wlf->dir.z = olddir.z * cos(-rotation.x) - olddir.x * sin(-rotation.x);
		wlf->plane.x = oldplane.x * cos(-rotation.x) + oldplane.z * sin(-rotation.x);
		wlf->plane.z = oldplane.z * cos(-rotation.x) - oldplane.x * sin(-rotation.x);
	}
	printf("Matrices:\n	DIR		PLANE\nX	%f	%f\nY	%f	%f\nZ	%f	%f\n", wlf->dir.x, wlf->plane.x, wlf->dir.y, wlf->plane.y, wlf->dir.z, wlf->plane.z);
	printf("Rotation: %d\n", wlf->rotation);
}

void	move_l(t_wolf *wlf, t_vector olddir, t_vector oldplane)
{
	oldplane = wlf->plane;
	olddir = wlf->dir;
	if (wlf->keyleft)
	{
		wlf->dir.x = wlf->dir.x * cos(wlf->rotsp) - wlf->dir.y * sin(wlf->rotsp);
		wlf->dir.y = olddir.x * sin(wlf->rotsp) + wlf->dir.y * cos(wlf->rotsp);
		wlf->plane.x = wlf->plane.x * cos(wlf->rotsp) - wlf->plane.y *
				sin(wlf->rotsp);
		wlf->plane.y = oldplane.x * sin(wlf->rotsp) + wlf->plane.y *
				cos(wlf->rotsp);
	}
}

int		move_lr(t_wolf *wlf)
{
	t_vector	olddir;
	t_vector	oldplane;

	oldplane = wlf->plane;
	olddir = wlf->dir;
	if (wlf->keyright)
	{
		wlf->dir.x = wlf->dir.x * cos(-wlf->rotsp) - wlf->dir.y * sin(-wlf->rotsp);
		wlf->dir.y = olddir.x * sin(-wlf->rotsp) + wlf->dir.y * cos(-wlf->rotsp);
		wlf->plane.x = wlf->plane.x * cos(-wlf->rotsp) - wlf->plane.y *
				sin(-wlf->rotsp);
		wlf->plane.y = oldplane.x * sin(-wlf->rotsp) + wlf->plane.y *
				cos(-wlf->rotsp);
	}
	set_yroation(wlf);
	set_reverse(wlf);
	move_l(wlf, olddir, oldplane);
	printf("Matrices:\n	DIR		PLANE\nX	%f	%f\nY	%f	%f\nZ	%f	%f\n", wlf->dir.x, wlf->plane.x, wlf->dir.y, wlf->plane.y, wlf->dir.z, wlf->plane.z);
	printf("Rotation: %d\n", wlf->rotation);
	return (0);
}

int		move_fb(t_wolf *wlf)
{
	if (wlf->keyup)
	{
		if (wlf->map[(int)wlf->posz][(int)(wlf->posy + wlf->dir.y
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy += wlf->dir.y * wlf->movsp;
		if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
				+ wlf->dir.x * wlf->movsp)] <= 1)
			wlf->posx += wlf->dir.x * wlf->movsp;
	}
	if (wlf->keydown)
	{
		if (wlf->map[(int)wlf->posz][(int)(wlf->posy - wlf->dir.y
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy -= wlf->dir.y * wlf->movsp;
		if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
				- wlf->dir.x * wlf->movsp)] <= 1)
			wlf->posx -= wlf->dir.x * wlf->movsp;
	}
	return (0);
}

int		strafe(t_wolf *wlf)
{
	if (wlf->keyq)
	{
		if (wlf->map[(int)wlf->posz][(int)(wlf->posy + wlf->dir.y
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy += wlf->dir.y * wlf->movsp;
		if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
				+ wlf->dir.x * wlf->movsp)] <= 1)
			wlf->posx += wlf->dir.x * wlf->movsp;
	}
	if (wlf->keye)
	{
		if (wlf->map[(int)wlf->posz][(int)(wlf->posy - wlf->dir.y
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy -= wlf->dir.y * wlf->movsp;
		if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
				- wlf->dir.x * wlf->movsp)] <= 1)
			wlf->posx -= wlf->dir.x * wlf->movsp;
	}
	return (0);
}
