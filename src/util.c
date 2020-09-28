/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:28:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/28 15:08:30 by AleXwern         ###   ########.fr       */
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

int		fps_counter(void *ptr)
{
	t_doom	*dm;

	dm = (t_doom*)ptr;
	while (!dm->killthread)
	{
		SDL_Delay(1000);
		free(dm->fpschar);
		dm->fpschar = ft_itoa(dm->fps);
		if (dm->fps > 0 && !dm->ismenu)
			dm->prefps = dm->fps;
		dm->fallsp.z = (0.6 * (30.0 / dm->buffer / dm->prefps))
			/ dm->prefps / (dm->buffer / 5.0);
		dm->fps = 0;
	}
	return (1);
}

int		arr_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i][0] != '\0')
		i++;
	return (i);
}

void	free_map(t_doom *dm, int f, int y)
{
	while (++f < dm->mxflr)
	{
		y = -1;
		while (++y < dm->height)
		{
			free(dm->area[f][y]);
		}
		free(dm->area[f]);
	}
}
