/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:27:02 by mporras-          #+#    #+#             */
/*   Updated: 2022/10/27 10:06:16 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_strfloat_isprint(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\t');
}

static void	ft_strfloat_spaces(const char *str, int *i, long double *sign)
{
	while (ft_strfloat_isprint(str[*(i)]) == 1)
			*(i) += 1;
	if (str[*(i)] == '-' || str[*(i)] == '+')
	{
		if (str[*(i)] == '-')
			*(sign) *= -1.0f;
		*(i) += 1;
	}
}

static double	ft_zero_protect(long double rst[2], long double power)
{
	if (power == 0)
		power = 1;
	return ((rst[0] / power) * rst[1]);
}

long double	ft_atolf(char *str)
{
	long double	rst[3];
	long double	power;
	int			i;

	rst[0] = 0;
	rst[1] = 1;
	i = 0;
	power = 0;
	ft_strfloat_spaces(str, &i, &rst[1]);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && (str[i] != '.' && power > 0))
			return (ft_zero_protect(rst, power));
		else if (str[i] == '.' && power == 0)
			power++;
		else if (str[i] >= '0' && str[i] <= '9')
		{	
			if (power > 0)
				power *= 10;
			rst[0] = rst[0] * 10 + (str[i] - '0');
		}
		i++;
	}
	return (ft_zero_protect(rst, power));
}
