/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:39:58 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/14 13:39:27 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "doom.h"
# include "value.h"

# define MAXPLAYER 4

typedef struct	s_server
{
	/*TCPsocket	server;
	TCPsocket	client[MAXPLAYER];
	IPaddress	ip;
	IPaddress	*remoteip[MAXPLAYER];*/
	t_socket	*server;
	t_socket	*client[MAXPLAYER];
	t_ip		ip;
	t_ip		*remoteip[MAXPLAYER];
	t_chunk		data;
	t_libax		*ax;
	char		alive[MAXPLAYER];
	int			timeout[MAXPLAYER];
	int			maxidle;
	int			id;
	int			stop;
}				t_server;

void			check_args(t_server *srv, char *av);
void			kill_extra(t_server *srv);

#endif
