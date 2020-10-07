/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:02:44 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/07 13:24:07 by tbergkul         ###   ########.fr       */
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
		dm->cycle(dm);
		buffer = 0;
	}
	buffer++;
}
