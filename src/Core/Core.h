// Big Header

#ifndef CORE_H
# define CORE_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
	//...

/* -----| Global   |----- */
# include "config.h"

/* -----| Internal |----- */
	//...

/* -----| Modules  |----- */
# include "Parser.h"

/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

/* -----| Types   |----- */

typedef unsigned int	t_uint;				/* Unsigned int   */
typedef unsigned char	t_uchar;			/* Unsigned char */
typedef t_config		t_args;				/* tkt          */

/* -----| Enums    |----- */

typedef enum e_Core_order	t_Core_order;	/* All Order from the _Core */

/* -----| Structs  |----- */

typedef struct s_Core		t_Core;			/* The Core struct interface */
typedef struct s_point		t_point;		/**/

/* ************************************************************************** */
/*                                 Enums                                      */
/* ************************************************************************** */
enum e_Core_order
{
	core_ord_player,		/* This is the Turn of the player            */
	core_ord_ai,			/* This is the turn of the AI               */
	core_ord_display,		/* The Core want an update of the display  */
	core_ord_start,			/* The game start                         */
	core_ord_win_AI,		/* The AI won the game                   */
	core_ord_win_player,	/* The palyer won the game              */
	core_ord_draw,			/* No one won the game                 */
	core_ord_stop,			/* The game should stop               */
	core_ord_wrong_place,	/* The coord targeted does not exist */
};

/* ************************************************************************** */
/*                                 Structs                                    */
/* ************************************************************************** */

struct s_Core
{
	int		(*add_pawn)(const t_uint cols);	/* Add a apwn to the cols colon */
	int		(*get_grid)(char ***grid);		/* Request the grid            */
	int		(*destroy)(t_Core **core);		/* The Core destroyer         */
	t_uint	width;							/* The grid width            */
	t_uint	height;							/* The Grid heigth          */
};

struct s_point
{
	t_uint	x;	/* x coordinate */
	t_uint	y;	/* y coordinate */
};


/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_Core	*Core_init(
	const t_args *const restrict args
);

#endif // CORE_H