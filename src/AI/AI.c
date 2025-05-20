// Big Header

#pragma region Header

/* -----| Internals |----- */
# include "_ai.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((visibility("hidden"), used)) int	_Evaluate(
	t_AI *ai,
	t_Core *core
)
{
	if (_unlikely(!ai || !core))
		return (-1);
	return (0);
}

/** */
__attribute__((visibility("hidden"), used)) int	_Play(
	t_AI *ai,
	t_Core *core
)
{
	if (_unlikely(!ai || !core))
		return (-1);
	return (0);
}

/** */
__attribute__((visibility("hidden"), used)) int	_AI_Destroy(
	t_AI **ai
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

/** */
__attribute__((cold)) t_AI	*AI_create(
	const t_uint width,
	const t_uint height
)
{
	t_AI	*ai;

	ai = (t_AI *)malloc(sizeof(t_AI));
	if (_unlikely(!ai))
		return (NULL);
	*ai = (t_AI){
		.evaluate = _Evaluate,
		.play = _Play,
		.destroy = _AI_Destroy,
	};
	return (ai);
}

#pragma region Functions