/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:43:58 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/06 16:45:22 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	options_menu_create2(t_doom *dm)
{
	dm->options[6] = &dm->shift;
	dm->maxvalue[6] = 15.0;
	dm->optext[6] = "lighting";
	dm->options[7] = &dm->ismenu;
	dm->maxvalue[7] = 1.0;
	dm->optext[7] = "options menu";
	dm->options[8] = &dm->tile;
	dm->maxvalue[8] = 6.0;
	dm->optext[8] = "texturepack";
	dm->options[9] = &dm->volume;
	dm->maxvalue[9] = 128;
	dm->optext[9] = "volume";
	dm->options[10] = &dm->hp;
	dm->maxvalue[10] = 5;
	dm->optext[10] = "health";
	dm->options[11] = &dm->netstat;
	dm->maxvalue[11] = 1;
	dm->optext[11] = "connect";
	dm->options[12] = &dm->person;
	dm->maxvalue[12] = 6;
	dm->optext[12] = "avatar";
}

void	options_menu_create(t_doom *dm)
{
	dm->options[0] = &dm->isfpscap;
	dm->maxvalue[0] = 1.0;
	dm->optext[0] = "fps cap";
	dm->options[1] = &dm->fpscap;
	dm->maxvalue[1] = 180.0;
	dm->optext[1] = "fps cap amount";
	dm->options[2] = &dm->isoutline;
	dm->maxvalue[2] = 1.0;
	dm->optext[2] = "outlines";
	dm->options[3] = &dm->buffer;
	dm->maxvalue[3] = 100.0;
	dm->optext[3] = "framebuffer";
	dm->options[4] = &dm->texbool;
	dm->maxvalue[4] = 1.0;
	dm->optext[4] = "textures";
	dm->options[5] = &dm->isgravity;
	dm->maxvalue[5] = 1.0;
	dm->optext[5] = "gravity";
	options_menu_create2(dm);
}
