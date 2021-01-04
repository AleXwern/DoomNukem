/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:16:19 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/04 13:24:02 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

t_libax		*ax_init(void)
{
	t_libax	*ax;

	if (!(ax = (t_libax*)ft_memalloc(sizeof(t_libax))))
		return (NULL);
	ax->handler = signal(SIGPIPE, SIG_IGN);
	if (ax->handler != SIG_DFL)
		signal(SIGPIPE, ax->handler);
	ax->id = AXID;
	ax->dm = 1;
	return (ax);
}

void		ax_shutdown(t_libax *ax)
{
	if (ax == NULL)
		return ;
	else if (ax->id != AXID)
		return ;
	ax->handler = signal(SIGPIPE, SIG_DFL);
	if (ax->handler != SIG_IGN)
		signal(SIGPIPE, ax->handler);
	free(ax);
}
