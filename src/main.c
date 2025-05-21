// Big Header

#pragma region Header

/* -----| Systems   |----- */
#include <stdio.h>

/* -----| Modules   |----- */
#include "Core.h"
#include "Parser.h"
#include "AI.h"
#include "Interface.h"

#pragma endregion Header
#pragma region Fonctions

extern t_Core	*CORE;

/**
 * @authors nduvoid, bcheronn, htrap
 * 
 * @brief This Project is a game of Connect 4. It is part of the Rushes of the
 * 42 School. The goal of this project is to create a game of Connect 4 with a
 *  player and an AI. The player can play only against the AI.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * 
 * @return int
 * @retval 0 if the program runs successfully.
 * @retval 1 if the program fails to initialize.
 * @retval 2 if the program fails to create the AI.
 */
int	main(int argc, char const *argv[])
{
	const t_config	args = check_args(argc, (char **)argv);

	if (_unlikely(args.error))
		return (1);
	else if (_unlikely(!Core_init(&args) || !AI_create(args.columns, args.rows)))
	{
		write(2, "Error: Init failed\n", 19);
		return (2);
	}

	display_game(CORE);

	CORE->destroy();
	return 0;
}
