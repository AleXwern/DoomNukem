/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:01:53 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 13:28:13 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	cam_udy(t_doom *dm)
{
	t_vector	oldplane;
	t_vector	olddir;

	oldplane = dm->plane;
	olddir = dm->dir;
	if (dm->key.up)
	{
		if (dm->dir.z > -0.5)
			dm->dir.z -= 0.05 * ((30.0 / dm->buffer) / dm->prefps);
	}
	if (dm->key.down)
	{
		if (dm->dir.z < 0.5)
			dm->dir.z += 0.05 * ((30.0 / dm->buffer) / dm->prefps);
	}
	if (dm->key.left || dm->key.right)
		move_lr(dm);
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
	}
	if (dm->key.right)
		move_l(dm, olddir, oldplane);
	return (0);
}
