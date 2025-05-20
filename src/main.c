// Big Header

#pragma region Header

/* -----| Systems   |----- */
#include <stdio.h>

/* -----| Modules   |----- */
#include "Core.h"
#include "Parseur.h"

#pragma endregion Header
#pragma region Fonctions

int	main(int argc, char const *argv[])
{
	const t_config	args = check_args(argc, (char **)argv);
	t_Core			*core = Core_init(&args);

	if (_unlikely(!core))
	{
		write(2, "Error: Core_init failed\n", 24);
		return (-1);
	}



	core->destroy(&core);
	return 0;
}
