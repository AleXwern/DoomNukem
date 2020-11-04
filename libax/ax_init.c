/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:16:19 by AleXwern          #+#    #+#             */
/*   Updated: 2020/11/04 14:26:15 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

t_libax		*ax_init(void)
{
	t_libax	*ax;

	if (!(ax = (t_libax*)ft_memalloc(sizeof(t_libax))))
		return (NULL);
#ifdef _WIN64
	ax->ver = MAKEWORD(2, 2);
	if (WSAStartup(MAKEWORD(2, 2), &ax->wsa))
		return (NULL);
#else
	ax->handler = signal(SIGPIPE, SIG_IGN);
	if (ax->handler != SIG_DFL)
		signal(SIGPIPE, ax->handler);
#endif
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
#ifdef _WIN64
	if (WSACleanup() == SOCKET_ERROR)
		if (WSAGetLastError() == WSAEINPROGRESS)
			WSACleanup();
#else
	ax->handler = signal(SIGPIPE, SIG_DFL);
	if (ax->handler != SIG_IGN)
		signal(SIGPIPE, ax->handler);
#endif
	free(ax);
}
