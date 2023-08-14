/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:52:11 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/05 16:52:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

int	mouse_handler(int mouse_code, int mouseX, int mouseY, t_mrt *mrt)
{
	t_hook	changes;

	(void)mouse_code;
	(void)mouseX;
	(void)mouseY;
	(void)mrt;
	if (mrt->behaviour == 0 || mrt->behaviour > 256)
		return (FALSE);
	changes = mrt->hooks[mrt->behaviour];
	if (changes)
		return (FALSE);
	return (TRUE);
}
