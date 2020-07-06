/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:02:44 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/06 14:49:00 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	game_loop(t_doom *wlf)
{
	static Uint32	buffer;
	
	wlf->keyck(wlf);
	if (wlf->buffer < 1)
		wlf->buffer = 1;
	if (buffer > wlf->buffer)
	{
		wlf->cycle(wlf);
		buffer = 0;
	}
	buffer++;
}