/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windoom.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:23:13 by AleXwern          #+#    #+#             */
/*   Updated: 2020/09/28 13:23:13 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOOM_H
# define WINDOOM_H

/*
** READ THIS!
** This file will not be included in the version that's returned to school.
** This is just that the program can be compiled in Windows enviroiment and
** other files can be kept Norm friendly.
*/
# define main(X, Y)			wmain(X, Y)
# define close(X)			_close(X)
# define open(X, Y)			_open(X, Y)
# define write(X, Y, Z)		_write(X, Y, Z)

#endif
