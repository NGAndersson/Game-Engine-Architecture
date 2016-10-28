#include "Display.h"
#include "Game.h"
#include "Decompressor.h"

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(int(NULL));
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	//FOR DEBUGGING PURPOSE
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(158);

	//Create, initialize and START the game
	Game _Game;
	WPARAM test = _Game.MainLoop(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
}