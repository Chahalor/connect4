// Big Header

#ifndef CONFIG_H
# define CONFIG_H

# pragma once

/* ************************************************************************** */
/*                                 Config                                     */
/* ************************************************************************** */

# define PLAYER_PAWN		'X'	/* Player pawn   */
# define AI_PAWN			'O'	/* AI pawn      */
# define EMPTY_PAWN			' '	/* Empty pawn  */

# define _unlikely(cond)	__builtin_expect(cond, 0)	/* This condition is not expected to be true */
# define _likely(cond)		__builtin_expect(cond, 1)	/* This condition is expected to be True    */

# ifndef DEBUG
#  define DEBUG	0	/* 0: debug disable, 1: debug enable */
# endif // DEBUG

#endif // CONFIG_H