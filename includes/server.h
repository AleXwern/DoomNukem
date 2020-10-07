/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:39:58 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/07 15:59:03 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "doom.h"
# include "value.h"

# define MAXPLAYER 4

typedef struct	s_server
{
	TCPsocket	server;
	TCPsocket	client[MAXPLAYER];
	IPaddress	ip;
	IPaddress	*remoteip[MAXPLAYER];
	t_chunk		data;
	char		alive[MAXPLAYER];
	int			timeout[MAXPLAYER];
	int			id;
	int			stop;
}				t_server;

void			kill_extra(t_server *srv);

#endif
