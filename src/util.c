/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:28:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/12/29 11:37:27 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

int		fps_capper(void *ptr)
{
	t_doom	*dm;

	dm = (t_doom*)ptr;
	dm->limit = 1;
	if (dm->fpscap < 1)
		dm->fpscap = 1;
	if (dm->isfpscap)
		SDL_Delay(1000 / dm->fpscap / 6);
	return (1);
}

void	fps_counter2(t_doom *dm, t_uint32 *i, t_uint32 *fps)
{
	if (*i >= 10)
		*i = 0;
	dm->fpschar = ft_itoa(*fps);
	if (dm->fps > 0 && !dm->ismenu)
		dm->prefps = *fps;
	dm->fallsp.z = (0.6 * (30.0 / dm->buffer / dm->prefps))
		/ dm->prefps / (dm->buffer / 5.0);
	dm->fps = 0;
}

int		fps_counter(void *ptr)
{
	t_doom		*dm;
	t_uint32	fpsarr[10];
	t_uint32	i;
	t_uint32	fps;

	dm = (t_doom*)ptr;
	i = 0;
	fps = 0;
	ft_bzero(fpsarr, 40);
	while (!dm->killthread)
	{
		SDL_Delay(100);
		if (dm->ismenu)
			continue;
		free(dm->fpschar);
		fps -= fpsarr[i];
		fpsarr[i] = dm->fps;
		fps += dm->fps;
		i++;
		fps_counter2(dm, &i, &fps);
	}
	return (1);
}

int		arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i][0] != '\0')
		i++;
	return (i);
}

void	free_map(t_doom *dm, int f, int y)
{
	while (++f < MXFLR)
	{
		y = -1;
		while (++y < dm->height)
		{
			free(dm->area[f][y]);
		}
		free(dm->area[f]);
	}
}
