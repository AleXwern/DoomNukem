/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:28:48 by tbergkul          #+#    #+#             */
/*   Updated: 2020/12/29 12:28:37 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

//norm error here to remove said things at the end
/*
**	remove gun and keycard in function below
*/

void	set_variables(t_doom *dm)
{
	dm->gun = 1;
	dm->keycard = 1;
	dm->creds = dm->winh;
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
