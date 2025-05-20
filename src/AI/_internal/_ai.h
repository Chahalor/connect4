// Big Header

#ifndef _AI_H
# define _AI_H

# pragma once

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
# include <unistd.h>
# include <stdlib.h>

/* -----| Internal |----- */
# include "AI.h"

/* -----| Modules  |----- */
# include "Core.h"

/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

/* -----| Types   |----- */
	//...

/* -----| Enums   |----- */
typedef enum e_req_ai	t_req_ai;	/* The AI request enum */

/* -----| Structs |----- */
typedef struct _s_ai	_t_ai;		/* The AI struct interface */

/* ************************************************************************** */
/*                                 Enums                                      */
/* ************************************************************************** */

enum e_req_ai
{
	ai_req_evaluate = 0,
	ai_req_play,
	ai_req_destroy,
	ai_req_init
};

enum e_ai_cost
{
	near_win = 100000,	/* placing a pawn here is a win */
	near_3 = 1000,		/* placing a pawn here makes an alignment of 3 */
	near_2 = 100,		/* placing a pawn here makes an alignment of 2 */
	near_1 = 10,		/* placing a pawn here makes an alignment of 1 */
	alone = 1,			/* placing a pawn here is alone */
	block_1 = 10,		/* block one pawn of the player */
	block_2 = 100,		/* block two pawns of the player */
	block_3 = 1000,		/* block three pawns of the player */
	block_win = 10000,	/* block the player to win */
};

/* ************************************************************************** */
/*                                 Structs                                    */
/* ************************************************************************** */

struct _s_ai
{
	int		**grid;		/* The status of the grid   */
	int		width;		/* the width of the grid   */
	int		height;		/* the height of the grid */
	int		best_move;	/* the best move found   */
};

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

// _evaluate.c

extern int	_evaluate(
	_t_ai *_ai
);

extern int	_play(
	_t_ai *_ai
);

// _ai.c

int	_AI(
	int access,
	void *data
);

#endif // _AI_H