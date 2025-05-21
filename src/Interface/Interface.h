// Big Header

#ifndef INTERFACE_H
# define INTERFACE_H

# pragma once

#include "Core.h"
#include "CLI.h"

int display_grid(
	char **grid,
	const t_uint height,
	const t_uint width
);

int display_game(
	t_Core *const restrict Core
);

#endif /* INTERFACE_H */