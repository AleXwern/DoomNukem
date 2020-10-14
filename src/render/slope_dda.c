/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_dda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:26:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/14 15:26:12 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		cross_pln(t_vector *ray, t_vector *plane, t_vector *i, double s)
{
	t_vector	u;
	t_vector	w;
	double		d;
	double		n;

	u = (t_vector){.z = ray[1].z - ray[0].z, .y = ray[1].y - ray[0].y, .x = ray[1].x - ray[0].x};
	w = (t_vector){.z = ray[0].z - plane[0].z, .y = ray[0].y - plane[0].y, .x = ray[0].x - plane[0].x};
	d = dot_prd(plane[1], u);
	n = -dot_prd(plane[1], w);
	if (fabs(d) < LIMN)
	{
        if (n == 0)
            return 2;
        else
            return 0;
    }
	s = n / d;
	if (s < 0 || s > 1)
		return (0);
	*i = (t_vector){.z = ray[0].z + s * u.z, .y = ray[0].y + s * u.y, .x = ray[0].x + s * u.x};
	return (1);
}

void	intersect(t_vector *plane, t_vector *ray, t_vector *p)
{
	double	d;
	double	t;

	d = dot_prd(plane[0], (t_vector){.z = -plane[1].z, .y = -plane[1].y, .x = -plane[1].x});
	t = -(d + dot_prd(ray[0], plane[1]) / dot_prd(ray[1], plane[1]));
	*p = (t_vector){
		.z = ray[0].z + t * ray[1].z,
		.y = ray[0].y + t * ray[1].y,
		.x = ray[0].x + t * ray[1].x,
			};
}

double	create_plane_yz(t_vector rayd, t_vector rmap, t_doom *dm, int side)
{
	t_vector	plane[2];
	t_vector	point;
	t_vector	ray[2];

	plane[0] = (t_vector){
		.z = 0, .y = 0, .x = 0
	};
	plane[1] = (t_vector){
		.z = 1, .y = -1, .x = 0
	};
	ray[0] = (t_vector){.z = rmap.z - (int)rmap.z, .y = rmap.y - (int)rmap.y, .x = rmap.x - (int)rmap.x};
	ray[1] = rayd;
	if (side == 1)
		ray[0].y = 1;
	intersect(plane, ray, &point);
	//if (dm->x == 500 && dm->y == 360)
	//	printf("Cross point %f %f %f at %d\nRMAP %f %f %f and %f\n", point.z, point.y, point.x, side, ray[0].z, ray[0].y, ray[0].x, dm->rayd.z);
	if (point.z >= 0 && point.z <= 1)
		return (point.z);
	if (dm->x == 500 && dm->y == 360)
		printf("Return def\n");
	return (1);
	/*if (cross_pln(ray, plane, &point, 0) == 1)
	{
		if (dm->x == 500 && dm->y == 360)
			printf("Cross point %f %f %f\n", point.z, point.y, point.x);
		return (point.z);
	}
	return (1);*/
}