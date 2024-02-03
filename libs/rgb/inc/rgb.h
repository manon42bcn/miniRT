/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:00:05 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/25 10:48:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# define RGB_MASK	255
# include "../../lib/inc/libft.h"

typedef enum e_rgb_indx
{
	R_I=0,
	G_I=1,
	B_I=2
}	t_rgb_indx;

typedef int		t_rgb;
typedef double	t_dec;

t_rgb	ft_rgb_dot(t_rgb color, double alpha);
t_rgb	ft_rgb_add(t_rgb ca, t_rgb cb);
t_rgb	ft_rgb_light(t_rgb color, double rgb[3]);
t_rgb	ft_rgb_diff(t_rgb ca, t_rgb cb);
t_rgb	ft_rgb_avg(t_rgb ca, t_rgb cb);
t_rgb	ft_rgb_balance(t_rgb *rgb);
t_rgb	ft_invert_color(t_rgb original);
t_rgb	ft_rgb_get(t_rgb color[3]);

#endif
