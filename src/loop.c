/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:02:44 by anystrom          #+#    #+#             */
/*   Updated: 2020/12/29 10:18:51 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	game_loop(t_doom *dm)
{
	static int	buffer;

	dm->keyck(dm);
	if (dm->buffer < 1)
		dm->buffer = 1;
	dm->rng += (dm->pos.z + dm->pos.y + dm->pos.x) * M_PI;
	if (buffer > dm->buffer)
	{
		if (dm->netstat)
		{
			if (send_pos(dm))
				recv_pos(dm);
		}
		dm->cycle(dm);
		buffer = 0;
	}
	buffer++;
}
