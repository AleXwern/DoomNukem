/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:15:14 by vkeinane          #+#    #+#             */
/*   Updated: 2020/12/18 10:30:25 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	comp_block(t_doom *dm, char **temp, int x, int y)
{
	if (is_block_info_present(temp))
		fill_block(dm, x, y);
	else
	{
		if (*temp[0] < '0' || *temp[0] > '9')
			dm->area[dm->flr][y][x].b = 2;
		else
			dm->area[dm->flr][y][x].b = ft_atoi(temp[0]);
		dm->area[dm->flr][y][x].lgt = ft_atoi(temp[1]);
		dm->area[dm->flr][y][x].pt = ft_atoi(temp[2]);
		dm->area[dm->flr][y][x].pln = ft_atoi(temp[3]);
		dm->area[dm->flr][y][x].meta = ft_atoi(temp[4]);
	}
	if (dm->area[dm->flr][y][x].b == 7)
	{
		dm->spw.x = x + 0.51;
		dm->spw.y = y + 0.51;
		dm->spw.z = dm->flr + 0.35;
		dm->area[dm->flr][y][x].b = 1;
	}
	force_validate_block(dm, x, y);
	free_memory(temp);
}

void	fill_floor(t_doom *dm, int y)
{
	while (++y < 25)
		fill_area(dm, y, 0);
}

void	fill_block(t_doom *dm, int x, int y)
{
	dm->area[dm->flr][y][x].b = 2;
	dm->area[dm->flr][y][x].lgt = 15;
	dm->area[dm->flr][y][x].pt = 0;
	dm->area[dm->flr][y][x].pln = 15;
	dm->area[dm->flr][y][x].meta = 0;
}

int		is_block_info_present(char **tmp)
{
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
{
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
