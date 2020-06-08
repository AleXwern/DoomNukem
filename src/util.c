/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:28:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/08 15:17:18 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

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
