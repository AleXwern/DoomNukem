/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:50:10 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/08 14:31:40 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	editor_key_release(Uint32 key, t_editor *le)
{
	if (key == ESC)
		le->quit = 1;
	if (key == DOWN)
		le->cur++;
	if (key == UP)
		le->cur--;
	if (le->cur > 4)
		le->cur = 0;
	if (le->cur < 0)
		le->cur = 4;
}

void	editor_key_press(Uint32 key, t_editor *le)
{
	if (key == LEFT)
		le->options[le->cur]--;
	if (key == RIGHT)
		le->options[le->cur]++;
	if (le->options[le->cur] > le->maxval[le->cur])
		le->options[le->cur] = le->maxval[le->cur];
	if (le->options[le->cur] < le->minval[le->cur])
		le->options[le->cur] = le->minval[le->cur];
}