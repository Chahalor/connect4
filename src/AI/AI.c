// Big Header

#pragma region Header

/* -----| Internals |----- */
# include "_ai.h"

/* -----| Modules   |----- */
#include "Utils.h"
#include "ft_printf.h"

#pragma endregion Header
#pragma region Fonctions

t_AI			*AI = NULL;
extern t_Core	*CORE;

/** */
__attribute__((visibility("hidden"), used)) int	_Evaluate(void)
{
	if (_unlikely(!AI || !CORE))
		return (-1);
	return (0);
}

/** */
__attribute__((visibility("hidden"), used)) int	_Play(void)
{
	t_uint pos = 0;
	int		ord = 0;

	if (_unlikely(!AI || !CORE))
		return (-1);
	AI->evaluate();
	pos = _AI(ai_req_play, NULL);
	ord = CORE->add_pawn(pos);
	while (ord == core_ord_wrong_place)
	{
		pos = randint(0, CORE->width - 1);
		ord = CORE->add_pawn(pos);
	}
	ft_printf(">> AI played at the column number %d\n", pos);
	return (ord);
}

/** */
__attribute__((visibility("hidden"), used)) int	_AI_Destroy(void)
{
	if (_unlikely(!AI))
		return (-1);
	free(AI);
	AI = NULL;
	return (0);
}

/** */
__attribute__((cold)) t_AI	*AI_create(
	const t_uint width,
	const t_uint height
)
{
	AI = (t_AI *)malloc(sizeof(t_AI));
	if (_unlikely(!AI))
		return (NULL);
	*AI = (t_AI){
		.evaluate = _Evaluate,
		.play = _Play,
		.destroy = _AI_Destroy,
	};
	if (_unlikely(_AI(ai_req_init, &(t_point){.x = width, .y = height}) < 0))
		return (free(AI), NULL);
	else
		return (AI);
}

#pragma region Functions