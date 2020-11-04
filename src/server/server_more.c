/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:14:39 by tbergkul          #+#    #+#             */
/*   Updated: 2020/11/04 14:02:48 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	kill_extra(t_server *srv)
{
	t_socket	*ksock;

	if (!(ksock = ax_accept(srv->server, srv->ax)))
		return ;
	ft_putendl("Killed extra connection");
	ax_close(ksock);
}

void	check_args(t_server *srv, char *av)
{
	int		idle;

	idle = ft_atoi(av);
	if (idle > 0)
		srv->maxidle = idle;
}
