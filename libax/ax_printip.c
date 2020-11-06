/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_printip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:52:23 by anystrom          #+#    #+#             */
/*   Updated: 2020/11/04 13:05:25 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

void	ax_printip(t_ip ip)
{
	ft_putnbr(ip.host & 0xff);
	write(1, ".", 1);
	ft_putnbr((ip.host >> 8) & 0xff);
	write(1, ".", 1);
	ft_putnbr((ip.host >> 16) & 0xff);
	write(1, ".", 1);
	ft_putnbr((ip.host >> 24) & 0xff);
	write(1, ":", 1);
	ft_putnbr(((ip.port >> 8) | (ip.port << 8)) & 0xffff);
}

void	ax_printipln(t_ip ip)
{
	ax_printip(ip);
	write(1, "\n", 1);
}
