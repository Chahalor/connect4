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
# include "_ai.h"

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
	int	(*evaluate)(t_AI *ai, t_Core *core);	/* Function to evaluate the grid */
	int	(*play)(t_AI *ai, t_Core *core);		/* Function to play the AI */
	int	(*destroy)(t_AI **ai);					/* Function to destroy the AI */
};

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_AI	*AI_create(
	const t_uint width,
	const t_uint height
);

#endif // AI_H