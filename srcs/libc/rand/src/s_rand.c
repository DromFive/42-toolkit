/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qperez <qperez42@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/05 11:48:32 by qperez            #+#    #+#             */
/*   Updated: 2015/04/09 15:27:41 by qperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** <This file contains rand method>
** < init, destroy, generate >
** Copyright (C) <2013>  Quentin Perez <qperez42@gmail.com>
** This file is part of 42-toolkit.
** 42-toolkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <rand/s_rand.h>
#include <f_error/m_error.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

bool	f_rand_init(t_rand *v_this, t_type_rand style)
{
	v_this->v_fd = -1;
	if (style >= e_rand_max)
		return (M_ERROR(false, "style value is out of range"));
	v_this->v_style = style;
	if (style == e_rand_std)
		srand((unsigned int)time(NULL));
	else
	{
		errno = 0;
		if ((v_this->v_fd = open("/dev/urandom", O_RDONLY)) == -1)
		{
			M_INFOS("open: %s, we will use libc", strerror(errno));
			srand((unsigned int)time(NULL));
			v_this->v_style = e_rand_std;
		}
	}
	return (true);
}

bool	f_rand_change_seed(t_rand *v_this, unsigned int seed)
{
	if (v_this->v_style == e_rand_file)
		return (M_ERROR(false, "You could't change seed of /dev/urandom"));
	srand(seed);
	return (true);
}

ssize_t	f_rand_generate(t_rand *v_this)
{
	ssize_t value;

	if (v_this->v_style == e_rand_file)
	{
		errno = 0;
		if (read(v_this->v_fd, &value, sizeof(value)) != sizeof(value))
			M_INFOS("read: %s", strerror(errno));
	}
	else
		value = (ssize_t)rand();
	return (value);
}

void	f_rand_destroy(t_rand *v_this)
{
	if (v_this->v_style == e_rand_file)
		close(v_this->v_fd);
}
