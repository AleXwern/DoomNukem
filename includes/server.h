/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:39:58 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 16:02:37 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "doom.h"
# include "value.h"

typedef struct	s_server
{
	TCPsocket	server;
	TCPsocket	client[5];
	IPaddress	ip;
	IPaddress	*remoteip[5];
	t_chunk		data;
	char		alive[5];
	int			timeout[5];
	int			id;
	int			stop;
}				t_server;

#endif