/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:26:23 by vkeinane          #+#    #+#             */
/*   Updated: 2020/11/19 15:15:28 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int datatype_check(t_doom *dm, char **tmp)
{
    int len;

    len = 0;
    len = ft_strlen(tmp[0]);
    if (len == 6)
    {
        if (!(ft_strcmp("Object", tmp[0])))
            dm->datareadtype = OBJECT;
        if (!(ft_strcmp("Sprite", tmp[0])))
            dm->datareadtype = SPRITE;
        printf("Got in datatypechange :  %d\n", dm->datareadtype);
    }
    if (dm->datareadtype != BLOCK)
        return(1);
    return (0);
}