/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objsel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:29:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/28 13:21:15 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int		get_objsmallsprite(int gfx)
{
	if (gfx == 9)
		return (2);
	else if (gfx == 30)
		return (5);
	else if (gfx == 35)
		return (1);
	else if (gfx == 36)
		return (4);
	else if (gfx == 37)
		return (0);
	return (3);
}

int		set_objsmallsprite(int gfx)
{
	if (gfx == 2)
		return (9);
	else if (gfx == 5)
		return (30);
	else if (gfx == 1)
		return (35);
	else if (gfx == 4)
		return (36);
	else if (gfx == 0)
		return (37);
	return (34);
}
