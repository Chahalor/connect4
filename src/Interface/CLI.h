#ifndef CLI_H
# define CLI_H

# pragma once

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
# include <unistd.h>
# include <stdlib.h>

/* -----| Internal |----- */
# include "_internal/_interface.h"

/* -----| Modules  |----- */
# include "Core.h"

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

extern WINDOW	*init_interface(void);

int	interface_main_menu(
	t_Core *const restrict Core
);

int	interface_game(
	void *data
);

int	interface_endgame(
	void *data
);

#endif /* CLI_H */