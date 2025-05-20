// Big Header

#pragma region Header

/* -----| Internals |----- */
# include "_ai.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((always_inline, used)) inline int	_play(
	_t_ai *_ai
)
{
	return (_ai->best_move);
}

/** */
__attribute__((always_inline, used)) inline int	_evaluate(
	_t_ai *_ai
)
{
	register int	i = -1;
	register int	j = -1;

	if (_unlikely(!_ai))
		return (-1);

	while (++i < _ai->height)
	{
		j = -1;
		while (++j < _ai->width)
		{
			// the cost calculation
		}
	}
	return (0);
}

#pragma endregion Fonctions