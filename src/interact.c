/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:03:32 by AleXwern          #+#    #+#             */
/*   Updated: 2020/07/20 15:34:28 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	lab_move(t_doom *dm, int obj)
{
	if (obj == 3 && dm->area[(int)dm->pos.z -
			1][(int)dm->pos.y][(int)dm->pos.x] == 1)
	{
		printf("stairs\n");
		dm->pos.z -= 1;
		dm->pos.y += dm->dir.y * 0.5;
		dm->pos.x += dm->dir.x * 0.5;
	}
	else if (obj == 4 && (int)dm->pos.z > 0 && dm->area[(int)dm->pos.z -
			1][(int)dm->pos.y][(int)dm->pos.x] == 1)
		dm->pos.z += 0.5;
	else if ((obj == 3 && (int)dm->pos.z == dm->mxflr) ||
			(obj == 4 && dm->flr == 0))
		error_out(LAB_OUT, dm);
	dm->dir.x *= -1.0;
	dm->dir.y *= -1.0;
	dm->plane.x *= -1.0;
	dm->plane.y *= -1.0;
	//dm->cycle(dm);
	//mlx_put_image_to_window(dm->mlx, dm->win, dm->gfx[obj + 4].img, 0, 0);
}

int		interact(t_doom *dm)
{
	t_vector	tarpos;
	int			obj;

	tarpos.x = dm->pos.x + dm->dir.x * 0.9;
	tarpos.y = dm->pos.y + dm->dir.y * 0.9;
	obj = dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x];
	if (obj == 3 || obj == 4)
		lab_move(dm, obj);
	else if (obj == 5)
	{
		dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x] = 0;
	}
	else if (obj == 0)
	{
		dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x] = 5;
	}
	if (obj == 5 || obj == 0)
		dm->cycle(dm);
	return (0);
}
