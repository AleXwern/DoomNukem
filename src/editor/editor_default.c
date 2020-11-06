/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:41:12 by anystrom          #+#    #+#             */
/*   Updated: 2020/11/06 01:54:41 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

/*
**	full zu zd yn ys xw xe nd nu su sd wd wu eu ed cnw csw cse cne
*/

void	opt_text(t_editor *le)
{
	le->opt[1] = "lighting        ";
	le->opt[2] = "plane type      ";
	le->opt[3] = "block thickness ";
	le->opt[4] = "meta            ";
	le->opt[6] = "lighter to the right";
	le->opt[7] = "full  z   y   x\n     u d n s w e";
	le->opt[8] = "thicker to the right";
	le->opt[9] = "paintings";
	le->opt[10] = "1 w  2 n  3 e  4 s  5 keyr  6 keyg  7 heal  8 kill";
	le->opt[11] = "nd  sd  ed  wd  nu  su  eu  wu  cnw  csw  cse  cne";
}

void	spr_text(t_editor *le)
{
	le->opt[1] = "graphics        ";
	le->opt[2] = "respawn         ";
	le->opt[3] = "health          ";
	le->opt[4] = "do not spawn    ";
	le->opt[6] = "outlook of sprite";
	le->opt[7] = "timer until enemy respawns";
	le->opt[8] = "maximun health of enemy";
	le->opt[9] = "1 if enemy spawns dead";
	le->opt[10] = "0 respawn means enemy doesnt respawn";
	le->opt[11] = "0 means enemy doesnt respawn";
}

/*
** 0 - floor
** 1 - gfx
** 2 - hp
** 3 - respawn?
** 4 - blank
*/

void	check_borders(t_editor *le)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		if (le->options[i] > le->maxval[i])
			le->options[i] = le->maxval[i];
		if (le->options[i] < le->minval[i])
			le->options[i] = le->minval[i];
	}
}

void	tab_change(t_editor *le)
{
	if (!le->tab)
	{
		le->maxval[1] = 15.0;
		le->maxval[2] = 18.0;
		le->maxval[3] = 15.0;
		le->maxval[4] = 8.0;
		le->minval[1] = 0;
		le->minval[2] = 0;
		le->minval[3] = 1;
		le->minval[4] = 0;
		opt_text(le);
	}
	else
	{
		le->maxval[1] = 6.0;
		le->maxval[2] = 30.0;
		le->maxval[3] = 5.0;
		le->maxval[4] = 1.0;
		le->minval[1] = 0;
		le->minval[2] = 0;
		le->minval[3] = 1;
		le->minval[4] = 0;
		spr_text(le);
	}
	check_borders(le);
}

void	editor_defaults(t_editor *le, t_doom *dm)
{
	ft_bzero(le, sizeof(t_editor));
	dm->area[(int)dm->spw.z][(int)dm->spw.y][(int)dm->spw.x].b = 7;
	le->blk = 2;
	le->options[0] = 2;
	le->maxval[0] = MXFLR - 1;
	le->minval[0] = 0;
	le->options[1] = 15;
	le->options[2] = 0;
	le->spr = 4;
	le->opt[0] = "floor           ";
	le->opt[5] = "lower floor to the right";
	tab_change(le);
}
