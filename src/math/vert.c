/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:25:57 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/07 16:25:57 by AleXwern         ###   ########.fr       */
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
<<<<<<< HEAD
}

t_vector	oper_vect(t_vector v, t_vector u, char o)
{
	t_vector	res;

	if (o == 0)
	{
		res.x = v.x - u.x;
		res.y = v.y - u.y;
		res.z = v.z - u.z;
	}
	else if (o == 1)
	{
		res.x = v.x + u.x;
		res.y = v.y + u.y;
		res.z = v.z + u.z;
	}
	else
	{
		res.x = v.x * u.x;
		res.y = v.y * u.y;
		res.z = v.z * u.z;
	}
	return (res);
}
=======
}
>>>>>>> 77ea6ad2e0b5882fb4a9a4f913d2964cbba964ae
