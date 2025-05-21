#ifndef _CLI_H
# define _CLI_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems  |----- */
# include <unistd.h>
# include <stdlib.h>

/* -----| Internal |----- */
# include "_interface.h"

/* -----| Modules  |----- */
# include "Core.h"

/* ************************************************************************** */
/*                                 Macro                                      */
/* ************************************************************************** */

# define BOARD_PADD		2

# define _t_button __attribute__((cleanup(_button_destroy))) t_button


/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

/* -----| Types   |----- */
	//...

/* -----| Enums   |----- */
	//...

/* -----| Structs |----- */
typedef struct s_button		t_button;	/* The button struct interface */

/* ************************************************************************** */
/*                                 Structs                                    */
/* ************************************************************************** */

struct s_button
{
	int		x1, y1, x2, y2;					/* Coordinates of the button                          */
	char	*label;							/* Label of the button                               */
	int		(*callback)(void *);				/* Callback function when the button is clicked     */
	int		(*is_pressed)(const t_button *const restrict btn, int x, int y);	/* Function to check if the button is pressed      */
	int		(*draw)(const t_button *const restrict btn);			/* Function to draw the button                    */
	int 	(*destroy)(t_button **btn);		/* Function to destroy the button                */
};

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_button	*button_create(
	const int x1,
	const int y1,
	const int x2,
	const int y2,
	const char *label,
	int (*callback)(void *)
);

int	_button_destroy(
	t_button **btn
);

#endif /* _CLI_H */