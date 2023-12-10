#include "Game.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <assert.h>
#include <stdio.h>

Game::Game()
{
	window = nullptr;
	gameState = GameState::PLAY;
}

Game::~Game()
{
}

void Game::InitGame()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 400, SDL_WINDOW_OPENGL);
	assert(window);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	assert(glContext);

	assert(!glewInit());

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(1.f, 0, 0, 1.f);
}

void Game::ProcessInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) 
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;

			case SDL_MOUSEMOTION:
				break;

			default:
				break;
		}
	}
}

void Game::GameLoop()
{
	while (gameState != GameState::EXIT)
	{
		ProcessInput();
		DrawGame();
	}
}

void Game::DrawGame()
{
	glClearDepth(1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	SDL_GL_SwapWindow(window);
}

void Game::Run()
{
	InitGame();
	GameLoop();
}
