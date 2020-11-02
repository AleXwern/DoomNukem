/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:15:14 by vkeinane          #+#    #+#             */
/*   Updated: 2020/11/02 16:06:42 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

 void	fill_block(t_doom *dm, int x, int y)
{
		dm->area[dm->flr][y][x].b = 2;
		dm->area[dm->flr][y][x].lgt = 15;
		dm->area[dm->flr][y][x].pt = 0;
		dm->area[dm->flr][y][x].pln = 15;
		dm->area[dm->flr][y][x].meta = 0;
}

int		is_block_info_present(char **tmp)
{// This may change the block to nomrmalized stats if some stat is 0
// 	I tried to look in the null variable but im not sure yet
	int	i;

	i = 0;
	while (i < 5)
		if (tmp[i++] == NULL)
			return (1);
	return (0);
}

/*
** Check if block values are in acceptable limits and change them if not
*/

void	force_validate_block(t_doom *dm, int x, int y)
{//Keep track if there comes more block types or anything different
// because otherwise these rules will suffocate different blocks
// Good idea would be defines to easily change limits to blocks
//	Defines created as MAX[variablename] and MINPLN as that's the only one that needs to be at least 1
	if (dm->area[dm->flr][y][x].b < 0 ||
		dm->area[dm->flr][y][x].b > MAXBLK)
		dm->area[dm->flr][y][x].b = 2;
	if (dm->area[dm->flr][y][x].lgt < 0 ||
		dm->area[dm->flr][y][x].lgt > MAXLGT)
		dm->area[dm->flr][y][x].lgt = MAXLGT;
	if (dm->area[dm->flr][y][x].pt < 0 ||
		dm->area[dm->flr][y][x].pt > MAXPT)
		dm->area[dm->flr][y][x].pt = 0;
	if (dm->area[dm->flr][y][x].pln < MINPLN ||
		dm->area[dm->flr][y][x].pln > MAXPLN)
		dm->area[dm->flr][y][x].pln = MAXPLN;
	if (dm->area[dm->flr][y][x].meta < 0 ||
		dm->area[dm->flr][y][x].meta > MAXMETA)
		dm->area[dm->flr][y][x].meta = 0;
}