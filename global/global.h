// Big HEader

#ifndef GLOBAL_H
# define GLOBAL_H

# pragma once

# include <stdio.h> //rm

/* ************************************************************************** */
/*                                 Global                                     */
/* ************************************************************************** */

# define PLAYER_PAWN		'X'
# define AI_PAWN			'O'
# define EMPTY_PAWN			' '

# define _unlikely(cond)	__builtin_expect(!!cond, 0)	/* This condition is not expected to be true */
# define _likely(cond)		__builtin_expect(!!cond, 1)	/* This condition is expected to be True    */

#endif /* GLOBAL_H */