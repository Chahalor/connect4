
#ifndef PARSER_H
# define PARSER_H

#pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
# include <unistd.h>
# include <stdlib.h>

/* -----| Internal |----- */
// # include "Core.h"

/* -----| Modules  |----- */
# include "ft_printf.h"
# include "Utils.h"
# include "formating.h"
#include "config.h"

/* ************************************************************************** */
/*                                 Structs                                    */
/* ************************************************************************** */


typedef struct s_config
{
	int	columns;
	int	rows;
	unsigned int	interface_enabled   : 1;
	unsigned int	error         : 1;
}	t_config;

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_config	check_args(int argc, char **argv);

#endif