/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:28:48 by tbergkul          #+#    #+#             */
/*   Updated: 2020/09/02 14:31:25 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	set_variables(t_doom *dm)
{
	dm->shooting = 0;
	dm->reloading = 0;
	dm->ani = 0;
	dm->frm = 0;
	dm->magazine = 10;
	dm->hp = 100;
	dm->alive = 1;
}
