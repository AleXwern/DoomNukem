/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windoom.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:25:27 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/30 12:25:28 by anystrom         ###   ########.fr       */
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
//# define main				wmain
//# define close(X)			_close(X)
//# define open(X, Y)			_open(X, Y)
//# define write(X, Y, Z)		_write(X, Y, Z)
# define main			wmain
# define close			_close
# define open			_open
# define write			_write

#endif
