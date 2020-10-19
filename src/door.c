/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:25:58 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/19 15:53:01 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	get_doortype(t_doom *dm, t_vector pos, t_vector door, t_block blk)
{
	t_vector	relative;

	if (blk.pt || blk.b != 5)
		return ;
	relative.x = round(pos.x - door.x);
	relative.y = round(pos.y - door.y);
	if (relative.y != 0 && relative.x != 0)
		return ;
	if (relative.y != 0)
		dm->area[(int)dm->pos.z][(int)door.y][(int)door.x].pt = 5;
	else
		dm->area[(int)dm->pos.z][(int)door.y][(int)door.x].pt = 3;
}

void	slide_door(t_doom *dm)
{
	if (dm->slidedoor == 'o')
	{
		dm->slideblock->pln = dm->doorani;
		dm->doorfrm++;
		if (dm->doorfrm == 2)
		{
			dm->doorani--;
			dm->doorfrm = 0;
		}
		if (dm->doorani == 1)
			dm->slidedoor = 'x';
	}
	else if (dm->slidedoor == 'c')
	{
		dm->slideblock->pln = dm->doorani;
		dm->doorfrm++;
		if (dm->doorfrm == 2)
		{
			dm->doorani++;
			dm->doorfrm = 0;
		}
		if (dm->doorani == 16)
			dm->slidedoor = 'x';
	}
}
