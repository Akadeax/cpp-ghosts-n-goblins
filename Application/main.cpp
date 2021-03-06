#include "pch.h"

#include "Core.h"
#include <ctime>
#include "GhostsAndGoblins.h"
#include "Entity.h"
#include "EntityKeeper.h"
#include "constants.hpp"

void StartHeapControl();
void DumpMemoryLeaks();

int main( int argc, char *argv[] )
{
	srand(static_cast<unsigned int>(time(nullptr)));

	StartHeapControl();
	Core* pCore{ new Core("Ghosts n' Goblins", constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT) };
	pCore->Run(new GhostsAndGoblins());
	delete pCore;

	DumpMemoryLeaks();
	return 0;
}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}


