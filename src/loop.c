/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:02:44 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:34:43 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	game_loop(t_doom *dm)
{
	static Uint32	buffer;
	
	dm->keyck(dm);
	if (dm->buffer < 1)
		dm->buffer = 1;
	if (buffer > dm->buffer)
	{
		dm->cycle(dm);
		buffer = 0;
	}
	buffer++;
}