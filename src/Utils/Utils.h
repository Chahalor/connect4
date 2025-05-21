// Big Header

#ifndef UTILS_H
# define UTILS_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
# include <stdlib.h>

/* -----| Internal |----- */
# include "Utils.h"

/* -----| Modules  |----- */
	//...

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

int	randint(
		const int min,
		const int max
);

extern int	ft_atoi(
	const char *const restrict str
);


extern int	is_numeric(
		const char *const restrict str
);

#endif /* UTILS_H */