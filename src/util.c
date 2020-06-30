/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:28:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/30 16:47:09 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

int		tex_check(t_doom *wlf)
{
	double	wdistdiff;
	
	//printf("X%d Y%d\n", wlf->x, wlf->y);
	if (wlf->x > 0)
	{
		//printf("X%d\n", wlf->x);
		if (wlf->maparr[wlf->winw * wlf->y + wlf->x - 1] != wlf->maparr[wlf->winw * wlf->y + wlf->x])
			return (1);
		wdistdiff = fabs(wlf->wallarr[wlf->winw * wlf->y + wlf->x - 1] - wlf->wallarr[wlf->winw * wlf->y + wlf->x]);
		if (wdistdiff > 0.8)
			return (1);
	}
	/*if (wlf->x < wlf->winw - 1)
	{
		//printf("X%d\n", wlf->x);
		if (wlf->maparr[wlf->winw * wlf->y + wlf->x + 1] != wlf->maparr[wlf->winw * wlf->y + wlf->x])
			return (1);
		wdistdiff = fabs(wlf->wallarr[wlf->winw * wlf->y + wlf->x + 1] - wlf->wallarr[wlf->winw * wlf->y + wlf->x]);
		if (wdistdiff > 0.14)
			return (1);
	}*/
	if (wlf->y > 0)
	{
		//printf("Y%d\n", wlf->y);
		if (wlf->maparr[wlf->winw * (wlf->y - 1) + wlf->x] != wlf->maparr[wlf->winw * wlf->y + wlf->x])
			return (1);
		wdistdiff = fabs(wlf->wallarr[wlf->winw * (wlf->y - 1) + wlf->x] - wlf->wallarr[wlf->winw * wlf->y + wlf->x]);
		if (wdistdiff > 0.8)
			return (1);
	}
	/*if (wlf->y < wlf->winh - 1)
	{
		//printf("Y%d\n", wlf->y);
		if (wlf->maparr[wlf->winw * (wlf->y + 1) + wlf->x] != wlf->maparr[wlf->winw * wlf->y + wlf->x])
			return (1);
		wdistdiff = fabs(wlf->wallarr[wlf->winw * (wlf->y + 1) + wlf->x] - wlf->wallarr[wlf->winw * wlf->y + wlf->x]);
		if (wdistdiff > 0.14)
			return (1);
	}*/
	return (0);
}

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
		if (wlf->fps > 0)
			wlf->prefps = wlf->fps;
		wlf->fallsp.z = (0.65 * (30.0 / BUFFER / wlf->prefps)) / wlf->prefps / (BUFFER / 5.0);
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
