/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 12:27:40 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/27 15:23:11 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	set_text(t_doom *dm, char *str, int *xy, double size)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			dm->gfx[33].x = (str[i] - 97) * 27;
			draw_pgfx_sc(dm, dm->gfx[33], (int[6]){xy[0], xy[1], 26, 27, 0, 0}, size);
		}
		xy[1] += 29 * size;
		i++;
	}
}