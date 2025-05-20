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
__attribute__((visibility("hidden"), used)) int	_destroy(
	t_Core **core
)
{
	if (_unlikely(!core || !*core))
		return (-1);
	else if (_Core(core_req_destroy, (void *)core, NULL) < 0)
		return (-1);
	else
	{
		free(*core);
		*core = NULL;
		return (0);
	}
}

/** */
__attribute__((cold, unused)) t_Core	*Core_init(
	const t_args *const restrict args
)
{
	t_Core	*Core = NULL;

	if (_unlikely(!args))
		return (NULL);
	else if (_unlikely(_Core(core_req_init, (void *)args, (void *)&Core) < 0))
		return (NULL);
	else
	{
		Core = (t_Core *)malloc(sizeof(t_Core));
		if (_unlikely(!Core))
			return (NULL);
		else
			*Core = (t_Core){
				.add_pawn = _add_pawn,
				.get_grid = _get_grid,
				.destroy = _destroy,
				.width = args->columns,
				.height = args->rows,
			};
		return (Core);
	}
}

#pragma endregion Fonctions