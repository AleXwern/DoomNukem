/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:03:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/17 15:23:45 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	options_menu(t_wolf *wlf)
{
	wlf->img = init_image(wlf, WINX, WINY);
	draw_gfx(wlf, wlf->gfx[9], 0, 0);
	mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->img.img, 0, 0);
}