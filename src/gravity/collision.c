/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 12:43:48 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/11 16:30:16 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	suffrocate(t_doom *dm, t_block blk, t_vector bpos)
{
	//bpos.z -= 0.1;
	//if (bpos.z < 0)
	//	bpos.z += 1;
	if (blk.b <= 1)
		return;
	if (blk.pt == 0)
		dm->iframe = IFRAME;
	else if (blk.pt == 1 && bpos.z > (1 - blk.pln / 15.0))
		dm->iframe = IFRAME;
	else if (blk.pt == 2 && bpos.z < blk.pln / 15.0)
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
	//printf("Pos %d %d %f %f %f\n", blk.b, blk.pt, bpos.z, bpos.y, bpos.x);
}
