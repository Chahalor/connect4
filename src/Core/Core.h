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
# include "global.h"

/* -----| Internal |----- */
	//...

/* -----| Modules  |----- */
# include "Parseur.h"

/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

/* -----| Types   |----- */

typedef unsigned int	t_uint;				/**/
typedef unsigned char	t_uchar;			/**/
typedef t_config		t_args;				/**/

/* -----| Enums    |----- */

typedef enum e_Core_order	t_Core_order;	/* */

/* -----| Structs  |----- */

typedef struct s_Core		t_Core;			/**/
typedef struct t_point	t_point;			/**/

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
	int	(*add_pawn)(const t_uint cols);
	int	(*get_grid)(char ***grid);
	int	(*destroy)(t_Core **core);
	int	width;			// the width of the grid
	int	height;			// the height of the grid
};

struct t_point
{
	int	x;	// x coordinate
	int	y;	// y coordinate
};


/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_Core	*Core_init(
	const t_args *const restrict args
);

#endif // CORE_H