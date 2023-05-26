/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsenses <hsenses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:43:44 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 14:43:45 by hsenses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}
