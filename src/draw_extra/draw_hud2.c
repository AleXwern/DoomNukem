/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:48:35 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/15 13:50:48 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_hud2(t_doom *dm)
{
	if (dm->money > 0)
	{
	char	*money;

	draw_pgfx_sc(dm, dm->gfx[34], (int[6]){(dm->winh - 70), 315, 103, 200,
		0, 0}, 0.35);
	money = ft_itoa(dm->money);
	set_text(dm, money, (int[3]){(dm->winh - 40), 370, 0xE71313}, 0.7);
	free(money);
	}
}
