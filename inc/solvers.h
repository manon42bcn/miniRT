/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:04:06 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/30 17:04:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVERS_H
# define SOLVERS_H

double			plane_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre, t_v3d plane_dir);
double			pyramid_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			sphere_solver(t_v3d origin, t_v3d dir, t_obj *sph);
double			square_solver(t_v3d origin, t_v3d dir, t_obj *sqr);
double			triangle_solver(t_v3d origin, t_v3d dir, t_obj *trg);

#endif
