// Big Header

#pragma region Header

/* -----| Internals |----- */
#include "_ai.h"

/* -----| Modules   |----- */
#include "AI.h"

#pragma endregion Header
#pragma region Fonctions

t_AI			*AI = NULL;
extern t_Core	*CORE;

/**
 * @brief	Request the AI to evaluate the grid.
 * 
 * @param void
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
*/
__attribute__((visibility("hidden"), used)) int	_Evaluate(void)
{
	if (_unlikely(!AI || !CORE))
		return (-1);
	else
		return (_AI(ai_req_evaluate, NULL));
}

/**
 * @brief	Request the AI to play its turn.
 * 
 * @param void
 * 
 * @return int	The order of the Core about the turn.
 * @retval core_ord_ai if the AI played its turn.
 * @retval core_ord_wrong_place if the AI played in a wrong place.
 * @retval -1 if the function fails.
*/
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
		ft_printf(">> AI played at the random column number %d\n", pos);	// rm
		ord = CORE->add_pawn(pos);
	}
	ft_printf(">> AI played at the column number %d\n", pos);
	return (ord);
}

/**
 * @brief	Ask nicely the AI to destroy itself.
 * 
 * @param void
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
 * 
 * @note The AI is destroyed by freeing the memory allocated for it.
*/
__attribute__((visibility("hidden"), used)) int	_AI_Destroy(void)
{
	if (_unlikely(!AI))
		return (-1);
	free(AI);
	AI = NULL;
	return (0);
}

/**
 * @brief	Create a new AI instance.
 * 
 * @param width	The width of the grid.
 * @param height	The height of the grid.
 * 
 * @return t_AI*	The new AI instance.
 * @retval NULL if the function fails.
*/
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
		.last_move = (t_point){.x = 0, .y = 0},
	};
	if (_unlikely(_AI(ai_req_init, &(t_point){.x = width, .y = height}) < 0))
		return (free(AI), NULL);
	else
		return (AI);
}

#pragma region Functions