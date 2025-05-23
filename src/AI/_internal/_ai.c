// Big Header

#pragma region Header

/* -----| Internals |----- */
# include "_ai.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

/**
 * @brief	Initialize the AI internal struct.
 * 
 * @param width		The width of the grid.
 * @param height	The height of the grid.
 * 
 * @return _t_ai*	The AI internal struct.
 * @retval NULL if the function fails.
*/
__attribute__((always_inline, used)) static inline _t_ai	*_init(
	const t_uint width,
	const t_uint height
)
{
	_t_ai			*_ai = NULL;
	const size_t	grid_size = sizeof(_t_ai) +
								sizeof(int *) * height +
								sizeof(int) * width * height;
	char			*block = (char *)malloc(grid_size);
	t_uint			i = -1;
	int				*data = NULL;
	
	if (_unlikely(!block))
		return (NULL);

	_ai = (_t_ai *)block;
	_ai->width = width;
	_ai->height = height;
	_ai->grid = (int **)(block + sizeof(_t_ai));
	data = (int *)(block + sizeof(_t_ai) + sizeof(int *) * height);
	while (++i < height)
		_ai->grid[i] = data + i * width;
	return (_ai);
}

/**
 * * @brief	Destroy the AI internal struct.
 * 
 * * @param ai	The AI internal struct.
 * 
 * * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
*/
__attribute__((always_inline, used)) static inline int _destroy(
	_t_ai **ai
)
{
	if (_unlikely(!ai || !*ai))
		return (-1);
	else
	{
		free(*ai);
		*ai = NULL;
		return (0);
	}
}

/**
 * @brief	AI function dispatcher.
 * 
 * @param access	The access level.
 * @param data		The data to pass to the AI.
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
*/
__attribute__((visibility("hidden"), used)) int	_AI(
	int access,
	void *data
)
{
	static _t_ai	*_ai = NULL;

	switch (access)
	{
		case ai_req_evaluate:
			return (_evaluate(_ai));
		case ai_req_play:
			return (_ai->best_move);
		case ai_req_destroy:
			return (_destroy(&_ai));
		case ai_req_init:
		{
			const t_point	point = *(t_point *)data;
			_ai = _init(point.x, point.y);
			return (_ai ? 0 : -1);
		}
		default:
			return (-1);
	}
}

#pragma endregion Fonctions