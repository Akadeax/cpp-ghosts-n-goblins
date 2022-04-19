#include "pch.h"

#include "Core.h"
#include <ctime>
#include "GhostsAndGoblins.h"
#include "Entity.h"
#include "EntityKeeper.h"

void StartHeapControl();
void DumpMemoryLeaks();

int main( int argc, char *argv[] )
{
	srand(static_cast<unsigned int>(time(nullptr)));

	StartHeapControl();

	Window window = Window{ "Ghosts n' Goblins", 900, 600 };
	Core* pCore{ new Core{ window } };
	GhostsAndGoblins* game = new GhostsAndGoblins(window);
	pCore->Run(game);
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


