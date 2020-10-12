/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_editor_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:34:11 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/06 15:38:29 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int	draw_screen_more(t_editor *le, t_doom *dm, int x, int y)
{
	if (y >= dm->height || x >= dm->width)
		return (1);
	if (y < 0 || x < 0)
		return (1);
	if (le->blk == 7)
	{
		dm->area[(int)dm->spw.z][(int)dm->spw.y][(int)dm->spw.x].b = 1;
		dm->spw.x = x + 0.51;
		dm->spw.y = y + 0.51;
		dm->spw.z = le->options[0] + 0.5;
	}
	if (dm->area[le->options[0]][y][x].b != 7)
	{
		dm->area[le->options[0]][y][x].b = le->blk;
		dm->area[le->options[0]][y][x].lgt = le->options[1];
		dm->area[le->options[0]][y][x].pt = le->options[2];
		if (le->blk == 1 || le->blk == 7)
			dm->area[le->options[0]][y][x].pt = 0;
		else
			dm->area[le->options[0]][y][x].pln = le->options[3];
		dm->area[le->options[0]][y][x].meta = le->options[4];
	}
	return (0);
}
