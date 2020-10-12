/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 12:43:48 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/07 14:23:07 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

double	get_coll_down(t_block blk)
{
	if (blk.pt <= 1)
		return (0);
	else if (blk.pt == 2)
		return (1 - blk.pln / 15.0);
	return (0);
}

void	suffrocate(t_doom *dm, t_block blk, t_vector bpos)
{
	if (blk.b <= 1)
		return ;
	if (bpos.z < LIMN)
		bpos.z++;
	if (blk.pt == 0)
		dm->iframe = IFRAME;
	else if (blk.pt == 1 && bpos.z < blk.pln / 15.0)
		dm->iframe = IFRAME;
	else if (blk.pt == 2 && bpos.z > (1 - blk.pln / 15.0))
		dm->iframe = IFRAME;
	else if (blk.pt == 3 && bpos.y < blk.pln / 15.0)
		dm->iframe = IFRAME;
	else if (blk.pt == 4 && bpos.y > (1 - blk.pln / 15.0))
		dm->iframe = IFRAME;
	else if (blk.pt == 5 && bpos.x < blk.pln / 15.0)
		dm->iframe = IFRAME;
	else if (blk.pt == 6 && bpos.x > (1 - blk.pln / 15.0))
		dm->iframe = IFRAME;
	if (dm->iframe)
		dm->hp -= 1;
}
