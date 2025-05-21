// Big Header

#pragma region Header

/* -----| Systems   |----- */
	//...

/* -----| Internals |----- */
# include "Core.h"
# include "_core.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

t_Core	*CORE = NULL;

/** */
__attribute__((visibility("hidden"), used)) int	_add_pawn(
	const t_uint col
)
{
	return (_Core(core_req_add_pown, (void *)&col, NULL));
}

/** */
__attribute__((visibility("hidden"), used)) int	_get_grid(
	char ***grid
)
{
	return (_Core(core_req_get_grid, NULL, grid));
}

/** */
__attribute__((visibility("hidden"), used)) int	_destroy(void)
{
	if (_unlikely(!CORE))
		return (-1);
	else if (_Core(core_req_destroy, (void *)CORE, NULL) < 0)
		return (-1);
	else
	{
		free(CORE);
		CORE = NULL;
		return (0);
	}
}

/** */
__attribute__((visibility("hidden"), used)) int	_next_turn(void)
{
	return (_Core(core_req_next_turn, (void *)CORE, NULL));
}

/** */
__attribute__((cold, unused)) t_Core	*Core_init(
	const t_args *const restrict args
)
{
	if (_unlikely(!args))
		return (NULL);
	else if (_unlikely(_Core(core_req_init, (void *)args, (void *)CORE) < 0))
		return (NULL);
	else
	{
		CORE = (t_Core *)malloc(sizeof(t_Core));
		if (_unlikely(!CORE))
			return (NULL);
		else
			*CORE = (t_Core){
				.add_pawn = _add_pawn,
				.get_grid = _get_grid,
				.next_turn = _next_turn,
				.destroy = _destroy,
				.width = args->columns,
				.height = args->rows,
			};
		return (CORE);
	}
}

#pragma endregion Fonctions