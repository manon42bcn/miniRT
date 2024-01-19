/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messenger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:45:33 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/18 09:35:33 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Display an error message and exit the Mini Ray Tracer program.
 *
 * This function prints an error message to the standard error stream (stderr)
 * and then terminates the execution of the Mini Ray Tracer program with an
 * error code.
 *
 * @param message The error message to be displayed.
 */
void	msg_error_exit(char *message)
{
	ft_putstr_fd("miniRT ERROR ", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	exit(ERROR);
}

/**
 * @brief Display information about the interactive hooks and their behavior.
 *
 * This function prints a summary of interactive hooks and their corresponding
 * actions. It provides details about the behavior associated with each key when
 * in interactive mode. The displayed information includes key-to-mode mappings,
 * translation, scaling, rotation, and other actions related to the manipulation
 * of objects and lights in the Mini Ray Tracer.
 *
 * @return An integer indicating the success of the operation (SUCCESS).
 */
static inline int	help_hook(void)
{
	ft_putendl_fd("\x1b[35m------------------------------", STDOUT_FILENO);
	ft_putendl_fd("HOOKS - BEHAVIOUR", STDOUT_FILENO);
	ft_putendl_fd("------------------------------\x1b[0m", STDOUT_FILENO);
	ft_putendl_fd("KEY\tMODE", STDOUT_FILENO);
	ft_putendl_fd("S\tSelection Mode. Select an object to", STDOUT_FILENO);
	ft_putendl_fd(" \tinteract to it. After an object is", STDOUT_FILENO);
	ft_putendl_fd(" \tselected it will change of color.", STDOUT_FILENO);
	ft_putendl_fd("T\tTranslate a selected object using arrows", STDOUT_FILENO);
	ft_putendl_fd("D\tIncrease or reduce width or radius", STDOUT_FILENO);
	ft_putendl_fd(" \tof a selected object using + or - keys.", STDOUT_FILENO);
	ft_putendl_fd("H\tIncrease or reduce height of a selected", STDOUT_FILENO);
	ft_putendl_fd(" \tselected object using + or - keys.", STDOUT_FILENO);
	ft_putendl_fd("R\tRotate a selected object using move keys", STDOUT_FILENO);
	ft_putendl_fd("E\tOrbit a camera around selected object", STDOUT_FILENO);
	ft_putendl_fd(" \tusing move keys.", STDOUT_FILENO);
	ft_putendl_fd("L\tLight mode. Select a light to translate", STDOUT_FILENO);
	ft_putendl_fd(" \tusing move keys, or change bright.", STDOUT_FILENO);
	ft_putendl_fd(" \tusing B or V keys", STDOUT_FILENO);
	ft_putendl_fd("Q\tBack to normal.", STDOUT_FILENO);
	ft_putendl_fd("MOVE KEYS (up-down): move using y axis.", STDOUT_FILENO);
	ft_putendl_fd("MOVE KEYS (left-right): move using x axis.", STDOUT_FILENO);
	ft_putendl_fd("MOVE KEYS (plus-minus): move using z axis.", STDOUT_FILENO);
	ft_putendl_fd("ESC Exit miniRT.", STDOUT_FILENO);
	return (SUCCESS);
}

#ifdef BONUS

/**
 * @brief Print help information and options for Mini Ray Tracer.
 * - BONUS VERSION -
 *
 * This function displays information about the usage and options for
 * running Mini Ray Tracer.
 * It provides details on how to execute the program with a scene file
 * and directs users to check the subject or a fully documented version
 * for additional information.
 *
 * @return SUCCESS if the help information is printed successfully.
 */
int	print_help(void)
{
	ft_putendl_fd("\x1b[35m------------------------------", STDOUT_FILENO);
	ft_putendl_fd("miniRT [BONUS] - HELP/OPTIONS", STDOUT_FILENO);
	ft_putendl_fd("------------------------------\x1b[0m", STDOUT_FILENO);
	ft_putendl_fd("\e[1m\e[34mUsage:\x1b[0m", STDOUT_FILENO);
	ft_putendl_fd("./miniRT [scene]", STDOUT_FILENO);
	ft_putendl_fd("[scene]: a .rt file. For more details run:", STDOUT_FILENO);
	ft_putendl_fd("\tgit checkout feat/documented", STDOUT_FILENO);
	ft_putendl_fd("\tfor fully documented version", STDOUT_FILENO);
	ft_putendl_fd("\e[1m\e[34mSupport:\x1b[0m", STDOUT_FILENO);
	ft_putendl_fd("\tObjects: Plane, Sphere, Cylinder.", STDOUT_FILENO);
	ft_putendl_fd("\tCone, Cuboid (box), triangle, rectangle.", STDOUT_FILENO);
	ft_putendl_fd("\tObjects can include:", STDOUT_FILENO);
	ft_putendl_fd("\t\tBUMP texture, waves texture, checkboard", STDOUT_FILENO);
	ft_putendl_fd("\t\tcolor, reflexion and refraction.", STDOUT_FILENO);
	ft_putendl_fd("\tScene: Multi-Camera, Ambient Light,", STDOUT_FILENO);
	ft_putendl_fd("\tMulti colored light, resolution,", STDOUT_FILENO);
	help_hook();
	return (SUCCESS);
}

#else

/**
 * @brief Print help information and options for Mini Ray Tracer.
 * - MANDATORY VERSION -
 *
 * This function displays information about the usage and options for
 * running Mini Ray Tracer.
 * It provides details on how to execute the program with a scene file
 * and directs users to check the subject or a fully documented version
 * for additional information.
 *
 * @return SUCCESS if the help information is printed successfully.
 */
int	print_help(void)
{
	ft_putendl_fd("\x1b[35m------------------------------", STDOUT_FILENO);
	ft_putendl_fd("miniRT [MANDATORY] - HELP/OPTIONS", STDOUT_FILENO);
	ft_putendl_fd("------------------------------\x1b[0m", STDOUT_FILENO);
	ft_putendl_fd("\e[1m\e[34mUsage:\x1b[0m", STDOUT_FILENO);
	ft_putendl_fd("./miniRT [scene]", STDOUT_FILENO);
	ft_putendl_fd("[scene]: a .rt file. For further details", STDOUT_FILENO);
	ft_putendl_fd("\tcheck subject or run:", STDOUT_FILENO);
	ft_putendl_fd("\tgit checkout feat/documented", STDOUT_FILENO);
	ft_putendl_fd("\tfor fully documented version", STDOUT_FILENO);
	ft_putendl_fd("\e[1m\e[34mSupport:\x1b[0m", STDOUT_FILENO);
	ft_putendl_fd("\tObjects: Plane, Sphere, Cylinder.", STDOUT_FILENO);
	ft_putendl_fd("\tScene: Camera, Ambient Light, Light.", STDOUT_FILENO);
	help_hook();
	return (SUCCESS);
}

#endif
