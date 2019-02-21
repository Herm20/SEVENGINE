#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	// Set up all of the objects
}

void Game::Run()
{
	// Making it "true" for now until the rendering stuff is added then
	// we can make it go while the pointer isn't null
	while (true) {
		// Update objects, process input, draw objects to the screen
	}
}

void Game::Exit()
{
	// just using exit for now, can be changed later
	std::exit(0);
}
