/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_str_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qperez <qperez42@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/28 15:09:03 by qperez            #+#    #+#             */
/*   Updated: 2015/07/03 16:39:52 by qperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** <This file contains f_str_tools function>
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

#include <f_string/f_print_fd.h>
#include <f_string/f_str_tools.h>
#include <f_error/m_error.h>

size_t	uf_str_len(const char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (M_ERROR(0, "Pointer NULL"));
	while (str[len] != '\0')
		len = len + 1;
	return (len);
}

void	uf_print_in_base(char nbr, int fd)
{
	if (nbr < 10)
		nbr = (char)(nbr + '0');
	else
		nbr = (char)(nbr + 'a' - 10);
	uf_print_char_fd(nbr, fd);
}
