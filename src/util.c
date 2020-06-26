/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:28:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/26 13:07:54 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

int		fps_capper(void* ptr)
{
	t_doom	*wlf;

	wlf = (t_doom*)ptr;
	if (wlf->isfpscap)
		SDL_Delay(1000 / wlf->fpscap / 6);
	return (1);
}

int		fps_counter(void* ptr)
{
	t_doom	*wlf;

	wlf = (t_doom*)ptr;
	while (!wlf->killthread)
	{
		SDL_Delay(1000);
		printf("FPS: %d\n", wlf->fps);
		wlf->prefps = wlf->fps;
		wlf->fps = 0;
	}
	return (1);
}

Uint32	color_shift(Uint32 color, double shift, t_doom *wlf, Uint32 ret)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;

	ret = (int)(shift * wlf->shift);
	if (ret > 10 * wlf->shift)
		ret = 10 * wlf->shift;
	if (ret < 1)
		return (color);
	SDL_GetRGB(color, wlf->img.tex->format, &r, &b, &g);
	r /= ret;
	g /= ret;
	b /= ret;
	ret = SDL_MapRGB(wlf->img.tex->format, r, b, g);
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

void	free_map(t_doom *wlf, int f, int y)
{
	while (++f < wlf->mxflr)
	{
		y = -1;
		while (++y < wlf->height)
		{
			free(wlf->map[f][y]);
		}
		free(wlf->map[f]);
	}
}
