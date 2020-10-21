/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:28:48 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/21 16:14:38 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	set_variables(t_doom *dm)
{
	dm->gun = 1;//remove in final version
	dm->keycard = 1;//remove in final version
	dm->slidedoor = 'x';
	dm->plrhight = 0.6;
	dm->moneytext = NULL;
}

void	dev_status(t_doom *dm, char *av)
{
	if (ft_strncmp("-debug", av, 6))
		return ;
	dm->dev = 1;
	dm->invincible = 4;
	dm->isgravity = 1;
	dm->jetpack = 1;
	dm->gun = 1;
	dm->keycard = 1;
}
