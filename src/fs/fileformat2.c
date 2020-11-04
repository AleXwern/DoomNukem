/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileformat2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:54:21 by tbergkul          #+#    #+#             */
/*   Updated: 2020/11/04 12:06:03 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	validate_flr(t_doom *dm, int y, int x, t_block blk)
{
	while (++y < dm->height)
	{
		x = -1;
		while (++x < dm->width)
			dm->area[MXFLR - 1][y][x] = blk;
	}
}

void	validate_map(t_doom *dm, int i, int a, t_block blk)
{
	while (++a < MXFLR)
	{
		i = -1;
		while (++i < dm->width)
		{
			dm->area[a][0][i] = blk;
			dm->area[a][dm->height - 1][i] = blk;
		}
		i = -1;
		while (++i < dm->height)
		{
			dm->area[a][i][0] = blk;
			dm->area[a][i][dm->width - 1] = blk;
		}
	}
	validate_flr(dm, -1, -1, blk);
}

int		templen(char **temp)
{
	int		i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}
