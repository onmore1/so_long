/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:31:41 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/09 18:58:51 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
int	ft_atoi(const char *buffer)
{
	int	x;
	int	sign;
	int	result;

	x = 0;
	sign = 1;
	result = 0;
	while ((buffer[x] >= 9 && buffer[x] <= 13) || buffer[x] == ' ')
		x++;
	if ((buffer[x] == '-') || (buffer[x] == '+'))
	{
		if (buffer[x] == '-')
		{
			sign = -1;
		}
		x++;
	}
	while (buffer[x] >= '0' && buffer[x] <= '9')
	{
		result = result * 10 + (buffer[x] - '0');
		x++;
	}
	return (result * sign);
}
// int	main(void)
// {
// 	char	buffer[] = "-+42";
// 	int		number;

// 	number = ft_atoi(buffer);
// 	printf("%d", number);
// 	return (0);
// }