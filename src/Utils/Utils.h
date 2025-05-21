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

extern int	ft_atoi(char *str);

#endif /* UTILS_H */