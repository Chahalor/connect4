// Big Header

#ifndef AI_H
# define AI_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
# include <unistd.h>
# include <stdlib.h>

/* -----| Internal |----- */
# include "_internal/_ai.h"

/* -----| Modules  |----- */
# include "Core.h"

/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

/* -----| Types   |----- */
	//...

/* -----| Enums   |----- */
	//...

/* -----| Structs |----- */
typedef struct s_AI		t_AI;			/* The AI struct interface */

/* ************************************************************************** */
/*                                 Structs                                    */
/* ************************************************************************** */

struct s_AI
{
	int		(*evaluate)(void);	/* Function to evaluate the grid */
	int		(*play)(void);		/* Function to play the AI */
	int		(*destroy)(void);	/* Function to destroy the AI */
	t_point	last_move;			/* The last move of the player */
};

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_AI	*AI_create(
	const t_uint width,
	const t_uint height
);

#endif // AI_H