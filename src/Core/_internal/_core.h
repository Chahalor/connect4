// Big Header

#ifndef _CORE_H
# define _CORE_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
# include <unistd.h>
# include <stdlib.h>

/* -----| Internal |----- */
# include "Core.h"

/* -----| Modules  |----- */
# include "Parser.h"

/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

/* -----| Types   |----- */
	//...

/* -----| Enums   |----- */
typedef enum e_Core_request	t_Core_request;	/* All request to the Internal Core */

/* -----| Structs |----- */
typedef struct _s_Core		_t_Core;		/* The Internal Core struct */

/* ************************************************************************** */
/*                                 Enums                                      */
/* ************************************************************************** */

enum e_Core_request
{
	core_req_init,		/* Request the Core to init itself            */
	core_req_add_pown,	/* Request The Core to add a awn to the grid */
	core_req_get_grid,	/* Request the Core to send The Grid        */
	core_req_destroy	/* Request the Core to destroy itself      */
};


/* ************************************************************************** */
/*                                 Structs                                    */
/* ************************************************************************** */

struct _s_Core
{
	char	**grid;			// 2D array of characters representing the game grid
	t_uint	width;			// the width of the grid
	t_uint	height;			// the height of the grid
	t_uint	nb_case_left;	// number of empty cases left
	t_uchar	turn	: 1;	// 0 = player, 1 = AI
	t_uchar	display	: 1;	// 0 = no display, 1 = display
};

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

int	_Core(
		int request,
		void *data,
		void *response
);

#endif /* _CORE_H */