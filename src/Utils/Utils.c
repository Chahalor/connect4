// Big Header

#pragma region Header

/* -----| Systems   |----- */
	//...

/* -----| Internals |----- */
#include "Utils.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((always_inline, used)) inline int	randint(
	const int min,
	const int max
)
{
	return (rand() % (max - min + 1) + min);
}

#pragma endregion Fonctions