/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:16:19 by AleXwern          #+#    #+#             */
/*   Updated: 2020/10/23 20:16:19 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

t_libax		*ax_init(void)
{
	t_libax	*ax;

	ax = (t_libax*)ft_memalloc(sizeof(t_libax));
#ifdef _WIN64
		ax->ver = MAKEWORD(2, 2);
		if (WSAStartup(MAKEWORD(2, 2), &ax->wsa))
			return (NULL);
#endif
	ax->id = AXID;
	ax->dm = 1;
	return (&ax);
}

void		ax_shutdown(t_libax *ax)
{
	if (ax == NULL)
		return;
	else if (ax->id != AXID)
		return;
#ifdef _WIN64
	if (WSACleanup() == SOCKET_ERROR)
		if (WSAGetLastError() == WSAEINPROGRESS)
			WSACleanup();
#endif
	ft_bzero(ax, sizeof(t_libax));
}
