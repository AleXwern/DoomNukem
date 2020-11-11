/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libax.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:12:37 by AleXwern          #+#    #+#             */
/*   Updated: 2020/11/11 12:47:46 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBAX_H
# define LIBAX_H

/*
** LIBAX, selfmade barebones network libary for HIVE Helsinki projects.
** More specifically the libary uses TCP protocol aka constantly alive
** connection. The reason for TCP is just that I happened to pick it and it
** started working so there's that.
** Libraries used technically not allowed but I will defend them with my life!
** Basically just a small fun project to see what it would require to do some
** kind of Network library in C. As it turns out it started working and I
** integrated it into the current HIVE project DoomNukem as both Network and
** Multiplayer bonuses.
*/

/*
** INCLUDES
** 2 types of includes: Windows and UNIX. Both are there as I often work
** from home and need the entire thing to work on my Windows PC.
** --WIN64--
** winsock2 and ws2tcpip are included for WIN network stuff and latter for
** TCP realted stuff.
** iphlpapi is included for resolving IP from given const char* and keep outlook
** same no matter on what OS the code is viewed.
** Pragma comments include the needed libaries.
** Windows also likes to be a different child so WSAEINTR is defined to EINTR
** to better keep compatability between systems.
** --UNIX--
** sys/socket is included for the basic network functions.
** sys/types is included for variables that other functions need.
** netinet/tcp is included for TCP variables
** errno is included to break recv under certain conditions.
** arpa/inet is defined for 'struct sockaddr_in' and IPPROTO_TCP.
** sys/fcntl is used to open and close the filehandling related to
** rending/receiving information
** INVALID_SOCKET and SOCKET_ERROR are defined on Windows and as the appropprate
** functions return -1 on UNIX we haave defined then as such
** Windows closes sockets with socketclose while UNIX with good 'ol close
** we "redirect" closesocket to close
*/

# include "../libft/libft.h"
# if _WIN64
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  pragma comment (lib, "Ws2_32.lib")
#  pragma comment (lib, "Mswsock.lib")
#  pragma comment (lib, "AdvApi32.lib")
#  include <iphlpapi.h>
#  define EINTR				WSAEINTR
# else
#  include <sys/socket.h>
#  include <sys/types.h>
#  include <netinet/tcp.h>
#  include <errno.h>
#  include <arpa/inet.h>
#  include <sys/fcntl.h>
#  define INVALID_SOCKET	-1
#  define SOCKET_ERROR		-1
#  define closesocket		close //change closesocket to close for final version
# endif
# include <stdio.h> //remove

/*
** Define few basic IP defines if they are not already defined.
** TCP_NODELAY to make ax_open return NULL if it's not defined
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

/*
** Self explanatory IP and port
** host is 32-bit integer that can store any IP
** host is 16-bit short integer that can store any port.
*/
typedef struct			s_ip
{
	t_uint32			host;
	t_uint16			port;
}						t_ip;

/*
** TCP socket
*/
typedef struct			s_socket
{
	int					channel;
	t_ip				remote;
	int					server;
}						t_socket;

# if _WIN64
typedef struct			s_libax
{
	short				id;
	int					dm;
	unsigned long		mode;
	int					accepted;
	WORD				ver;
	WSADATA				wsa;
}						t_libax;
# elif __APPLE__
typedef struct			s_libax
{
	short				id;
	int					dm;
	unsigned long		mode;
	int					accepted;
	void				(*handler)(int);
	int					flag;
}						t_libax;
# endif

t_libax		*ax_init(void);
t_socket	*ax_accept(t_socket *srv, t_libax *ax);
t_socket	*ax_open(t_ip *ip, t_libax *ax);
int			ax_recv(t_socket *sock, void *data, int max);
int			ax_resolvehost(t_ip *ip, const char *host, t_uint16 port);
int			ax_send(t_socket *sock, const void *data, int len);
void		*ax_close(t_socket *sock);
void		ax_printip(t_ip ip);
void		ax_printipln(t_ip ip);
void		ax_shutdown(t_libax *ax);
#endif
