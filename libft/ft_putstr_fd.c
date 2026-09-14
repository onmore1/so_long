/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:58:16 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/06 16:34:37 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	while (s[index])
	{
		write(fd, &s[index], 1);
		index++;
	}
}

/*
int	main(void)
{
	char	s[] = "Hello  123";
	int		fd = 1;

	ft_putstr_fd(s, fd);
	return (0);
}
*/
