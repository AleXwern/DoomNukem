/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_chunck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:34:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/20 14:46:16 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

t_gfx		memcpy_gfx(t_gfx chunk, int *pos, int *size)
{
	t_gfx	gfx;
	int		i;

	gfx.wid = size[1];
	gfx.hgt = size[0];
	gfx.bpp = 32;
	gfx.pitch = gfx.wid * (gfx.bpp / 8);
	gfx.data = (Uint32*)ft_memalloc(gfx.pitch * gfx.hgt);
	i = 0;
	while (i < gfx.hgt)
	{
		ft_memcpy(gfx.data + (gfx.wid * i),
			chunk.data + (chunk.wid * (i + pos[0]) + pos[1]),
			gfx.pitch);
		i++;
	}
	return (gfx);
}