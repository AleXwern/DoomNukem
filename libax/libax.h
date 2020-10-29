/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libax.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:12:37 by AleXwern          #+#    #+#             */
/*   Updated: 2020/10/23 19:12:37 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBAX_H
# define LIBAX_H

# include "../libft/libft.h"
# if _WIN64
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  pragma comment (lib, "Ws2_32.lib")
#  pragma comment (lib, "Mswsock.lib")
#  pragma comment (lib, "AdvApi32.lib")
#  include <iphlpapi.h>
# endif
#include <stdio.h> //remove
/*
** Define few basic IP if they are not already defined.
*/
# ifndef INADDR_ANY
#  define INADDR_ANY		0x00000000
# endif
# ifndef INADDR_NONE
#  define INADDR_NONE		0xFFFFFFFF
# endif
# ifndef INADDR_LOOPBACK
#  define INADDR_LOOPBACK	0x7f000001
# endif
# ifndef INADDR_BROADCAST
#  define INADDR_BROADCAST	0xFFFFFFFF
# endif
# ifndef TCP_NODELAY
#  define TCP_NODELAY	0
# endif
# define	AXID			0x4297


# if _WIN64
#  define ENV64BIT
# endif
# if __x86_64__ || __ppc64__
#  define ENV64BIT
# endif

# ifdef ENV64BIT
typedef unsigned int	t_uint32;
typedef unsigned short	t_uint16;
typedef unsigned char	t_uint8;
# else
#  error "System bit odd architechture. Stuff would break anyway."
# endif

typedef struct			s_ip
{
	t_uint32			host;
	t_uint16			port;
}						t_ip;

typedef struct			s_socket
{
	int					ready;
	int					channel;
	t_ip				remote;
	t_ip				local;
	int					flag;
}						t_socket;

typedef struct			s_libax
{
	short				id;
	int					dm;
	unsigned long		mode;
# if _WIN64
	WORD				ver;
	WSADATA				wsa;
# elif __APPLE__
	void				(*handler)(int)
# endif
}						t_libax;
#endif

t_libax		*ax_init(void);
t_socket	*ax_accept(t_socket* srv, t_libax* ax);
t_socket	*ax_open(t_ip *ip, t_libax *ax);
int			ax_recv(t_socket *sock, void *data, int max, size_t maxattempt);
int			ax_resolvehost(t_ip *ip, const char *host, t_uint16 port);
int			ax_send(t_socket *sock, const void *data, int len);
void		*ax_close(t_socket *sock);
void		ax_shutdown(t_libax *ax);