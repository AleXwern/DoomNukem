/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:23:47 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/19 12:32:36 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

double		tri_pythagor(t_vector f, t_vector s)
{
	t_vector	p;
	double		res;

	p.x = (f.x - s.x) * (f.x - s.x);
	p.y = (f.y - s.y) * (f.y - s.y);
	p.z = (f.z - s.z) * (f.z - s.z);
	res = sqrt(p.x + p.y);
	res = sqrt((res * res) + p.z);
	return (res);
}

double		pythagor(t_vector f, t_vector s)
{
	t_vector	p;
	double		res;

	p.x = (f.x - s.x) * (f.x - s.x);
	p.y = (f.y - s.y) * (f.y - s.y);
	p.z = (f.z - s.z) * (f.z - s.z);
	res = sqrt(p.x + p.y);
	return (res);
}

double		dot_prd(t_vector v, t_vector u)
{
	double	res;

	res = 0;
	res += v.x * u.x;
	res += v.y * u.y;
	res += v.z * u.z;
	return (res);
}

t_vector	cross_prd(t_vector v, t_vector u)
{
	t_vector	c;

	c.x = (v.y * u.z) - (v.z * u.y);
	c.y = (v.z * u.x) - (v.x * u.z);
	c.z = (v.x * u.y) - (v.y * u.x);
	return (c);
}

void		intersect(t_vector *plane, t_vector *ray, t_vector *p)
{
	double	d;
	double	t;

	d = dot_prd(plane[0], (t_vector){.z = -plane[1].z,
		.y = -plane[1].y, .x = -plane[1].x});
	t = -(d + dot_prd(ray[0], plane[1]) / dot_prd(ray[1], plane[1]));
	*p = (t_vector){
		.z = ray[0].z + t * ray[1].z,
		.y = ray[0].y + t * ray[1].y,
		.x = ray[0].x + t * ray[1].x,
		};
}
