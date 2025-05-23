// Big Header

#ifndef INTERFACE_H
# define INTERFACE_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
	//...

/* -----| Internal |----- */
	//...

/* -----| Modules  |----- */
# include "Core.h"
# include "get_next_line.h"
# include "Utils.h"
# include "formating.h"
# include "AI.h"

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

int	display_grid(
	char **grid,
	const t_uint height,
	const t_uint width
);

int	display_game(
	t_Core *const restrict Core
);

#endif /* INTERFACE_H */