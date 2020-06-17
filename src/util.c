/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:28:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/17 15:26:58 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

int		color_shift(int color, double shift, t_wolf *wlf)
{
	int		ret;
	int		r;
	int		g;
	int		b;

	ret = (int)(shift * wlf->shift);
	if (ret > 10 * wlf->shift)
		ret = 10 * wlf->shift;
	if (ret < 1)
		return (color);
	r = color / (256 * 256);
	g = (color / 256 - r * 256);
	b = (color - g * 256 - r * 256 * 256);
	ret = ((r / ret) * 256 * 256) + ((g / ret) * 256) + (b / ret);
	return (ret);
}

int		arr_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i][0] != '\0')
		i++;
	return (i);
}

void	free_map(t_wolf *wlf, int f, int y)
{
	while (++f < wlf->mxflr)
	{
		y = -1;
		while (++y < wlf->height)
		{
			if (wlf->map[f][y])
				free(wlf->map[f][y]);
		}
		if (wlf->map[f])
			free(wlf->map[f]);
	}
}
